// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "module.h"
#include QMK_KEYBOARD_H

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

enum custom_keycodes {
    HS_BATQ = SAFE_RANGE,   //custom 64
    HS_DIR,                 //custom 65
    HS_SIRI,                //custom 66
    HS_CT_A,                //custom 67
    BT_TEST,                //custom 68
    AUTO_TOGGLE             //custom 69
};

#define ______ HS_BLACK

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LCMD,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_FL] = LAYOUT( /* Function Layer */
        _______,  AUTO_TOGGLE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_MOD,  KC_MPLY,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,  _______,  _______,
        _______,  _______,  HS_DIR,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        _______,  _______, _______,  _______,  _______,   _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RGB_VAI,  _______,
        _______,   GU_TOGG,  _______,                     HS_BATQ,                                _______,  _______,  HS_CT_A,  RGB_SAI,  RGB_VAD,  RGB_SAD),

    [_MBL] = LAYOUT( /* Base (Mac) */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LCMD,                      KC_SPC,                                 KC_RCMD,  MO(_MFL), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MFL] = LAYOUT( /* Function Layer (Mac) */
        _______,  KC_BRID,  KC_BRIU,  KC_MCTL,  HS_SIRI,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,  _______,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,  _______,  _______,
        _______,  _______,  HS_DIR,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RGB_VAI,  _______,
        _______,  _______,  _______,                      HS_BATQ,                                _______,  _______,  HS_CT_A,  RGB_SAI,  RGB_VAD,  RGB_SAD),
    [_FBL] = LAYOUT( /* ? */
        QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  BT_TEST,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                      _______,                                _______,  _______,  _______,  _______,  _______,  _______)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
};
#endif
// clang-format on

typedef union {
    uint32_t raw;
    struct {
        uint8_t wasd_act_as_directional : 1;
        uint8_t ctrl_act_as_menu : 1;
    };
} eeconfig_user_t;
eeconfig_user_t confinfo_user;

void eeconfig_init_user() {
    confinfo_user.raw = eeconfig_read_user();
    if (!confinfo_user.raw) {
        confinfo_user.wasd_act_as_directional = 0;
        confinfo_user.ctrl_act_as_menu        = 0;
    }
}

bool rk_bat_req_flag;
bool num_pad_lit;
uint8_t my_num_flag = 0;

uint32_t blink_timer;
void     m1v5_blink(void) {
    blink_timer = timer_read32();
}

// i don't know what this does
void m1v5_bt_test(void) {
    md_send_devctrl(0x62);
}

uint32_t ee_clr_callback(uint32_t trigger_time, void *cb_arg) {
    eeconfig_init();
    m1v5_blink();
    return 0;
}

uint32_t ctrl_act_as_menu_callback(uint32_t trigger_time, void *cb_arg) {
    confinfo_user.ctrl_act_as_menu = !confinfo_user.ctrl_act_as_menu;
    m1v5_blink();
    eeconfig_update_user(confinfo_user.raw);
    return 0;
}

bool led_update_user(led_t led_state) {
    if (led_state.num_lock) {
        my_num_flag = 1;
        // layer_on(_FL);
    } else {
        my_num_flag = 0;
        // layer_off(_FL);
    }
    return true;
}

char random_char(void) {
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789     "; // extra spaces for realism

    return charset[rand() % (sizeof(charset) - 1)];
}

// ─────────────────────────────
// State variables
// ─────────────────────────────
void last_matrix_activity_trigger(void);

bool auto_typing = false;

bool is_auto_typing_active(void) {
    return auto_typing;
}

uint16_t typing_count = 0;
bool is_deleting = false;
bool is_idle = false;
uint32_t idle_until = 0;

uint32_t next_action_time = 0;
uint16_t typing_interval = 100;

uint32_t hs_ct_time;

bool     process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BT_TEST: {
            if (record->event.pressed) {
                m1v5_bt_test();
            }
            return false;
        } break;

        case EE_CLR: {
            static deferred_token delayed_exec = INVALID_DEFERRED_TOKEN;

            if (record->event.pressed) {
                delayed_exec = defer_exec(5000, ee_clr_callback, NULL);
                return false;
            } else if (delayed_exec != INVALID_DEFERRED_TOKEN) {
                cancel_deferred_exec(delayed_exec);
                delayed_exec = INVALID_DEFERRED_TOKEN;
            }
        } break;

        case KC_A: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_LEFT);
                } else {
                    unregister_code16(KC_LEFT);
                }
                return false;
            }
        } break;

        case KC_S: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_DOWN);
                } else {
                    unregister_code16(KC_DOWN);
                }
                return false;
            }
        } break;

        case KC_D: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_RGHT);
                } else {
                    unregister_code16(KC_RGHT);
                }
                return false;
            }
        } break;

        case KC_W: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_UP);
                } else {
                    unregister_code16(KC_UP);
                }
                return false;
            } else {
                return true;
            }
        } break;

        case KC_LEFT: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_A);
                } else {
                    unregister_code16(KC_A);
                }
                return false;
            }
        } break;

        case KC_DOWN: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_S);
                } else {
                    unregister_code16(KC_S);
                }
                return false;
            }
        } break;

        case KC_RGHT: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_D);
                } else {
                    unregister_code16(KC_D);
                }
                return false;
            }
        } break;

        case KC_UP: {
            if (confinfo_user.wasd_act_as_directional) {
                if (record->event.pressed) {
                    register_code16(KC_W);
                } else {
                    unregister_code16(KC_W);
                }
                return false;
            }
        } break;

        case KC_RCTL: {
            if (confinfo_user.ctrl_act_as_menu) {
                if (record->event.pressed) {
                    register_code16(KC_APP);
                } else {
                    unregister_code16(KC_APP);
                }
                return false;
            } else {
                return true;
            }
        } break;

        case HS_DIR: {
            if (record->event.pressed) {
                confinfo_user.wasd_act_as_directional = !confinfo_user.wasd_act_as_directional;
                m1v5_blink();
                eeconfig_update_user(confinfo_user.raw);
            }
            return false;
        } break;

        case HS_CT_A: {
            static deferred_token delayed_exec = INVALID_DEFERRED_TOKEN;

            if (record->event.pressed) {
                delayed_exec = defer_exec(3000, ctrl_act_as_menu_callback, NULL);
                return false;
            } else if (delayed_exec != INVALID_DEFERRED_TOKEN) {
                cancel_deferred_exec(delayed_exec);
                delayed_exec = INVALID_DEFERRED_TOKEN;
            }
            return false;
        } break;

        case HS_SIRI: {
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
                wait_ms(20);
            } else {
                unregister_code(KC_SPC);
                unregister_code(KC_LCMD);
            }
            return false;
        } break;

        case KC_MCTL: {
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_UP);

            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_UP);
            }
            return false;
        } break;

        case RGB_SPI: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() >= (RGB_MATRIX_SPD_STEP * 5)) {
                    m1v5_blink();
                }
            }
        } break;
        case RGB_SPD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_speed() <= RGB_MATRIX_SPD_STEP * 2) {
                    if (rgb_matrix_get_speed() != RGB_MATRIX_SPD_STEP) m1v5_blink();
                    rgb_matrix_set_speed(RGB_MATRIX_SPD_STEP);

                    return false;
                }
                m1v5_blink();
            }
        } break;
        case RGB_VAI: {
            if (record->event.pressed) {
                rgb_matrix_enable();
                gpio_write_pin_high(LED_POWER_EN_PIN);
                if (rgb_matrix_get_val() == RGB_MATRIX_MAXIMUM_BRIGHTNESS) m1v5_blink();
            }
        } break;
        case RGB_VAD: {
            if (record->event.pressed) {
                if (rgb_matrix_get_val() <= RGB_MATRIX_VAL_STEP) {
                    gpio_write_pin_low(LED_POWER_EN_PIN);
                    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                        rgb_matrix_set_color(i, 0, 0, 0);
                    }
                }
                if (rgb_matrix_get_val() == 0) m1v5_blink();
            }
        } break;

        case HS_BATQ: {
            rk_bat_req_flag = record->event.pressed;
            return false;
        } break;

        // case MO(_FL):  {
        //     num_pad_lit = record->event.pressed;
        //     return true;
        // } break;

        case AUTO_TOGGLE: {
            if (record->event.pressed){
                auto_typing = !auto_typing;

                if (auto_typing) {
                    // reset state
                    rgb_matrix_disable_noeeprom();
                    typing_count = 0;
                    is_deleting = false;
                    next_action_time = timer_read(); 
                } else {
                    rgb_matrix_enable_noeeprom();
                }
            } return false;
        }

        case KC_ESC: {
            if (auto_typing){
                rgb_matrix_enable_noeeprom();
                auto_typing = false;
            }
            return true;
        }

        // case KC_LCMD: {
        //     if (keymap_is_mac_system()) {
        //         if (keymap_config.no_gui) {
        //             if (record->event.pressed) {
        //                 register_code16(KC_LCMD);
        //             } else {
        //                 unregister_code16(KC_LCMD);
        //             }
        //         }
        //     }

        //     return true;
        // } break;
        // case KC_RCMD: {
        //     if (keymap_is_mac_system()) {
        //         if (keymap_config.no_gui) {
        //             if (record->event.pressed) {
        //                 register_code16(KC_RCMD);
        //             } else {
        //                 unregister_code16(KC_RCMD);
        //             }
        //         }
        //     }

        //     return true;
        // } break;
    }

    return true;
}

void matrix_scan_user(void) {
    if (!auto_typing) return;

    // ───── Handle idle state ─────
    if (is_idle) {
        if (timer_elapsed32(idle_until) < 0xFFFFFFFF) {
            if (timer_read32() < idle_until) {
                return; // still idling
            }
        }
        is_idle = false; // idle finished
    }

    // ───── Randomly enter idle ─────
    if (!is_idle && (rand() % 300 == 0)) {  
        // ~1 in 300 chance each scan
        uint16_t idle_time = 1000 + (rand() % 4000); // 1–5 sec
        idle_until = timer_read32() + idle_time;
        is_idle = true;
        return;
    }

    if (timer_elapsed(next_action_time) < typing_interval) return;
    next_action_time = timer_read();

    // ───── Deleting mode ─────
    if (is_deleting) {
        typing_interval = 40 + (rand() % 120);
        tap_code(KC_BSPC);
        typing_count--;    
        if (typing_count == 0) {
            is_deleting = false;
        }     
        return;
    }

    // ───── Typing mode ─────
    // char c = random_char();
    // tap_code_delay(c, 5);

    // ───── Typing ─────
    typing_interval = 80 + (rand() % 200);

    char c = random_char();

    send_char(c);

    // if (c >= 'a' && c <= 'z') {
    //     tap_code(KC_A + (c - 'a'));
    // } else if (c >= 'A' && c <= 'Z') {
    //     register_code(KC_LSFT);
    //     tap_code(KC_A + (c - 'A'));
    //     unregister_code(KC_LSFT);
    // } else if (c >= '0' && c <= '9') {
    //     tap_code(KC_0 + (c - '0'));
    // } else if (c == ' ') {
    //     tap_code(KC_SPACE);
    // }

    typing_count++;

    // trigger deletion phase
    if (typing_count >= 20) {
        is_deleting = true;
        last_matrix_activity_trigger();
    }
}

bool rgb_matrix_indicators_user() {

    if (blink_timer) {
        if ((timer_elapsed32(blink_timer) / 250) % 2 == 0) {
            rgb_matrix_set_color_all(0xFF, 0xFF, 0xFF);
        } else {
            rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        }

        if (timer_elapsed32(blink_timer) > 1250) {
            blink_timer = 0;
        }
        return false;
    }

    if (rk_bat_req_flag) {
        rgb_matrix_set_color_all(0x00, 0x00, 0x00);
        for (uint8_t i = 0; i < 10; i++) {
            uint8_t mi_index[10] = RGB_MATRIX_BAT_INDEX_MAP;
            if ((i < (*md_getp_bat() / 10)) || (i < 1)) {
                if (*md_getp_bat() >= (IM_BAT_REQ_LEVEL1_VAL)) {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL1_COLOR);
                } else if (*md_getp_bat() >= (IM_BAT_REQ_LEVEL2_VAL)) {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL2_COLOR);
                } else {
                    rgb_matrix_set_color(mi_index[i], IM_BAT_REQ_LEVEL3_COLOR);
                }
            } else {
                rgb_matrix_set_color(mi_index[i], 0x00, 0x00, 0x00);
            }
        }

        return false;
    }

    if (host_keyboard_led_state().caps_lock) rgb_matrix_set_color_all(0x20, 0x20, 0x20);

    // if (num_pad_lit){
    //     if (my_num_flag == 1){
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_1, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_2, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_3, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_4, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_5, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_6, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_7, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_8, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_9, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_0, 0x20, 0x20, 0xFF);
    //         rgb_matrix_set_color(HS_RGB_INDEX_NUM_PRD, 0x20, 0x20, 0xFF);
    //     }
    //     return true;
    // }

    return true;
}

void keyboard_post_init_user(void) {
    srand(timer_read32());
}