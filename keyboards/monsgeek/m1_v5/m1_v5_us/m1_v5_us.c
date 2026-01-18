// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "m1_v5_us.h"

#include "module.h"

#include "wireless.h"
#include "usb_main.h"
#include "lowpower.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1; // used to make sure the eeprom has initialized at least once
        uint8_t current_dev : 3;
        uint8_t last_bt_dev : 3;
    };
} confinfo_t;
confinfo_t confinfo;

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

#define keymap_is_mac_system() ((get_highest_layer(default_layer_state) == _MBL) || (get_highest_layer(default_layer_state) == _MFL))
#define keymap_is_base_layer() ((get_highest_layer(default_layer_state) == _BL) || (get_highest_layer(default_layer_state) == _FL))

bool     charging_state    = false;
bool     battery_full_flag = false;
HSV      start_hsv;
bool     lower_sleep = false;

uint32_t keyboard_init_deferred(uint32_t trigger_time, void *cb_arg) {
    // auto switching devs
    md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
    wireless_devs_change(!confinfo.current_dev, confinfo.current_dev, false);
    return 0;
}

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif

    confinfo.raw = eeconfig_read_kb();
    if (!confinfo.raw) {
        confinfo.flag        = true;
        confinfo.last_bt_dev = 1;

        eeconfig_init_user();
        eeconfig_update_kb(confinfo.raw);
    }

    gpio_set_pin_output(LED_POWER_EN_PIN);
    gpio_write_pin_high(LED_POWER_EN_PIN);

    gpio_set_pin_output(HS_LED_BOOSTING_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);

    gpio_write_pin_low(USB_POWER_EN_PIN);
    gpio_set_pin_output(USB_POWER_EN_PIN);

    gpio_set_pin_input(HS_BAT_CABLE_PIN);

    gpio_set_pin_input_high(BAT_FULL_PIN);

    gpio_set_pin_input_high(SYSTEM_WIN_PIN);
    gpio_set_pin_input_high(SYSTEM_MAC_PIN);

    wireless_init();
    wireless_devs_change(!confinfo.current_dev, confinfo.current_dev, false);

    defer_exec(100, keyboard_init_deferred, NULL);
    keyboard_post_init_user();

    start_hsv = rgb_matrix_get_hsv();
}

void usb_power_connect(void) {
    gpio_write_pin_low(USB_POWER_EN_PIN);
}

void usb_power_disconnect(void) {
    gpio_write_pin_high(USB_POWER_EN_PIN);
}

void suspend_power_down_kb(void) {
    gpio_write_pin_low(LED_POWER_EN_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_high(LED_POWER_EN_PIN);

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
}

bool lpwr_is_allow_timeout_hook(void) {
    return wireless_get_current_devs() != DEVS_USB;
}

void wireless_post_task(void) {
}

// i don't know what this does
// void m1v5_bt_test(void) {
//     md_send_devctrl(0x62);
// }

static uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);

        } break;
        case KC_BT2: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
        } break;
        case KC_BT3: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
        } break;
        case KC_2G4: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
        } break;
        default:
            break;
    }

    return 0;
}

// processes fn + wireless keys and also holding them
static bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    static uint16_t       keycode_shadow               = 0x00;
    static deferred_token wls_process_long_press_token = INVALID_DEFERRED_TOKEN;

    keycode_shadow = keycode;

#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                          \
        do {                                                                                                                   \
            if (record->event.pressed) {                                                                                       \
                if (wireless_get_current_devs() != wls_dev) wireless_devs_change(wireless_get_current_devs(), wls_dev, false); \
                if (wls_process_long_press_token == INVALID_DEFERRED_TOKEN) {                                                  \
                    wls_process_long_press_token = defer_exec(WLS_KEYCODE_PAIR_TIME, wls_process_long_press, &keycode_shadow); \
                }                                                                                                              \
            } else {                                                                                                           \
                cancel_deferred_exec(wls_process_long_press_token);                                                            \
                wls_process_long_press_token = INVALID_DEFERRED_TOKEN;                                                         \
            }                                                                                                                  \
        } while (false)

    switch (keycode) {
        case KC_BT1: {
            WLS_KEYCODE_EXEC(DEVS_BT1);

        } break;
        case KC_BT2: {
            WLS_KEYCODE_EXEC(DEVS_BT2);
        } break;
        case KC_BT3: {
            WLS_KEYCODE_EXEC(DEVS_BT3);
        } break;
        case KC_2G4: {
            WLS_KEYCODE_EXEC(DEVS_2G4);
        } break;

        case KC_USB: {
            WLS_KEYCODE_EXEC(DEVS_USB);
        } break;
        default:
            return true;
    }

    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (process_record_user(keycode, record) != true) {
        return false;
    }

    if (process_record_wls(keycode, record) != true) {
        return false;
    }

    return true;
}

struct kb_state_t kb_state = {
    // this is so high it will surely trigger an update
    .dev = 99
};

kb_dev_info_t kb_dev_info[5] = {
    { .key = HS_RGB_BLINK_INDEX_USB, .color = { HS_LBACK_COLOR_USB } },
    { .key = HS_RGB_BLINK_INDEX_BT1, .color = { HS_LBACK_COLOR_BT1 } },
    { .key = HS_RGB_BLINK_INDEX_BT2, .color = { HS_LBACK_COLOR_BT2 } },
    { .key = HS_RGB_BLINK_INDEX_BT3, .color = { HS_LBACK_COLOR_BT3 } },
    { .key = HS_RGB_BLINK_INDEX_2G4, .color = { HS_LBACK_COLOR_2G4 } },
};

void update_kb_state(void) {
    uint8_t dev = wireless_get_current_devs();

    uint8_t status = dev == DEVS_USB ? USB_DRIVER.state : *md_getp_state();
    if (dev == kb_state.dev && status == kb_state.status) {
        return;
    }

    kb_state.dev = dev;
    kb_state.status = status;
    kb_state.changed_at = timer_read32();
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {
    update_kb_state();

    if (confinfo.current_dev != wireless_get_current_devs()) {
        confinfo.current_dev = wireless_get_current_devs();
        if (confinfo.current_dev > 0 && confinfo.current_dev < 4) confinfo.last_bt_dev = confinfo.current_dev;
        eeconfig_update_kb(confinfo.raw);
    }
}

void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    update_kb_state();
    notify_usb_device_state_change_user(usb_device_state);
}

void md_state_change_kb(void) {
    update_kb_state();
}

static void rgb_matrix_wls_indicator(void) {
    if (kb_state.dev >= 5) return; // not initialized, just in case
    kb_dev_info_t dev_info = kb_dev_info[kb_state.dev];

    if (kb_state.dev == DEVS_USB) {
        switch (kb_state.status) {
            case USB_ACTIVE: break;
            default: {
                if (timer_elapsed32(kb_state.changed_at) > INDICATOR_TIMEOUT) break;
                if ((timer_elapsed32(kb_state.changed_at) / 500) % 2 == 0) {
                    rgb_matrix_set_color(dev_info.key, dev_info.color.r, dev_info.color.g, dev_info.color.b);
                }
            } break;
        }

    } else {
        switch (kb_state.status) {
            case MD_STATE_CONNECTED: break;
            case MD_STATE_PAIRING: {
                if ((timer_elapsed32(kb_state.changed_at) / 200) % 2 == 0) {
                    rgb_matrix_set_color(dev_info.key, dev_info.color.r, dev_info.color.g, dev_info.color.b);
                }
            } break;

            default: {
                if (timer_elapsed32(kb_state.changed_at) > INDICATOR_TIMEOUT) break;
                if ((timer_elapsed32(kb_state.changed_at) / 500) % 2 == 0) {
                    rgb_matrix_set_color(dev_info.key, dev_info.color.r, dev_info.color.g, dev_info.color.b);
                }
            } break;
        }

    }
}

void housekeeping_task_kb(void) { // loop
    wireless_housekeeping_task();

    static uint32_t hs_current_time;

    charging_state    = gpio_read_pin(HS_BAT_CABLE_PIN);
    battery_full_flag = gpio_read_pin(BAT_FULL_PIN);

    if (!hs_current_time || timer_elapsed32(hs_current_time) > 1000) {
        uint8_t hs_now_mode;
        if (charging_state && battery_full_flag) {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_DONE;
        } else if (charging_state) {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING;
        } else {
            hs_now_mode = MD_SND_CMD_DEVCTRL_CHARGING_STOP;
        }

        hs_current_time = timer_read32();
        md_send_devctrl(hs_now_mode);
        md_send_devctrl(MD_SND_CMD_DEVCTRL_INQVOL);
    }

    if (charging_state) {
        gpio_write_pin(HS_LED_BOOSTING_PIN, 0);

    } else {
        gpio_write_pin(HS_LED_BOOSTING_PIN, 1);
    }

    if ((gpio_read_pin(SYSTEM_WIN_PIN) != 0) && (gpio_read_pin(SYSTEM_MAC_PIN) == 0)) { // mac system
        if (!keymap_is_mac_system()) {
            set_single_persistent_default_layer(_MBL);
            layer_move(0);
        }
    } else { // win system
        if (keymap_is_mac_system()) {
            set_single_persistent_default_layer(_BL);
            layer_move(0);
        }
    }

    // converts device low power mode after 60 seconds at 0% battery
    static uint32_t battery_process_time = 0;
    if (*md_getp_bat() <= BATTERY_CAPACITY_STOP) {
        if (!battery_process_time) {
            battery_process_time = timer_read32();
        }

        if (battery_process_time && timer_elapsed32(battery_process_time) > 60000) {
            battery_process_time = 0;
            lower_sleep          = true;
            lpwr_set_timeout_manual(true);
        }
    } else {
        battery_process_time = 0;
    }

    housekeeping_task_user();
}

bool rgb_matrix_indicators_kb() {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) rgb_matrix_set_color(HS_RGB_INDEX_CAPS, 0x20, 0x20, 0x20);
    if (!keymap_is_mac_system() && keymap_config.no_gui) rgb_matrix_set_color(HS_RGB_INDEX_WIN_LOCK, 0x20, 0x20, 0x20);

    rgb_matrix_wls_indicator();

    if (charging_state && !battery_full_flag) {
        rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0x00, 0xFF, 0x00);
    } else if (*md_getp_bat() <= BATTERY_CAPACITY_LOW) {
        static uint32_t battery_flash_timer;

        if (!battery_flash_timer || timer_elapsed32(battery_flash_timer) > 500) {
            battery_flash_timer = timer_read32();
        }

        if (timer_elapsed32(battery_flash_timer) <= 250) {
            rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0xFF, 0x00, 0x00);
        } else {
            rgb_matrix_set_color(HS_MATRIX_BLINK_INDEX_BAT, 0x00, 0x00, 0x00);
        }
    }

    return true;
}

void lpwr_wakeup_hook(void) {
    gpio_write_pin_high(LED_POWER_EN_PIN);
    gpio_write_pin_high(HS_LED_BOOSTING_PIN);
}

static ioline_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void lpwr_exti_init_hook(void) {
    if (lower_sleep) {
#if DIODE_DIRECTION == ROW2COL
        for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
            if (col_pins[i] != NO_PIN) {
                gpio_set_pin_output_push_pull(col_pins[i]);
                gpio_write_pin_high(col_pins[i]);
            }
        }
#endif
    }
    gpio_set_pin_input(HS_BAT_CABLE_PIN);
    waitInputPinDelay();
    palEnableLineEvent(HS_BAT_CABLE_PIN, PAL_EVENT_MODE_RISING_EDGE);
}

void palcallback_cb(uint8_t line) {
    switch (line) {
        case PAL_PAD(HS_BAT_CABLE_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_CABLE);
        } break;
    }
}

void lpwr_stop_hook_pre(void) {

    gpio_write_pin_low(LED_POWER_EN_PIN);
    gpio_write_pin_low(A9);
    gpio_write_pin_low(HS_LED_BOOSTING_PIN);

    if (lower_sleep) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
        wait_ms(200);
        lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_UART);
    }
}

void lpwr_stop_hook_post(void) {
    if (lower_sleep) {
        switch (lpwr_get_sleep_wakeupcd()) {
            case LPWR_WAKEUP_USB:
            case LPWR_WAKEUP_CABLE: {
                lower_sleep = false;
                lpwr_set_state(LPWR_WAKEUP);
            } break;
            default: {
                lpwr_set_state(LPWR_STOP);
            } break;
        }
    }
}