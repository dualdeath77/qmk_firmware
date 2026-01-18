// Copyright 2024 yangzheng20003 (@yangzheng20003)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <math.h>
#include "lowpower.h"
#include "module.h"
#include "usb_main.h"
#include QMK_KEYBOARD_H
#include "usb_device_state.h"

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
    _FBL,
};

enum custom_keycodes {
    HS_BATQ = SAFE_RANGE,
    CUSTOM_CAPS,
    KEEP_AWAKE,
};

#define ______ HS_BLACK

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        CUSTOM_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LCMD,  KC_LALT,                      KC_SPC,                                 KC_RALT,  MO(_FL),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_FL] = LAYOUT( /* Function Layer */
        _______,  KC_MYCM,  KC_MAIL,  KC_WSCH,  KC_WHOM,  KC_MSEL,  KC_MPLY,  KC_MPRV,  KC_MNXT,  _______,  _______,  _______,  _______,  RGB_MOD,  _______,
        _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,  _______,  _______,
        QK_RBT,  _______,  _______,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        KC_CAPS,  _______, _______,  _______,  _______,   _______,  _______,  KEEP_AWAKE,  _______,  RGB_TOG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RGB_VAI,  _______,
        _______,   GU_TOGG,  _______,                     HS_BATQ,                                _______,  _______,  _______,  RGB_SAI,  RGB_VAD,  RGB_SAD),

    [_MBL] = LAYOUT( /* Base (Mac) */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGUP,
        CUSTOM_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,   KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
        KC_LCTL,  KC_LALT,  KC_LCMD,                      KC_SPC,                                 KC_RCMD,  MO(_MFL), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MFL] = LAYOUT( /* Function Layer (Mac) */
        _______,  KC_BRID,  KC_BRIU,  KC_MCTL,  _______,  _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,  _______,
        EE_CLR,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI,  _______,  _______,
        _______,  _______,  _______,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   KC_INS,   _______,  KC_PSCR,  _______,  _______,  _______,  _______,
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  KEEP_AWAKE,  _______,  RGB_TOG,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  KC_CALC,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  MO(_FBL), RGB_VAI,  _______,
        _______,  _______,  _______,                      HS_BATQ,                                _______,  _______,  _______,  RGB_SAI,  RGB_VAD,  RGB_SAD),
    [_FBL] = LAYOUT( /* Function + Right Shift */
        QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        EE_CLR,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                      _______,                                _______,  _______,  _______,  _______,  _______,  _______)

};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(_______, _______)},
    [2] = {ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______)},
};
#endif

// clang-format on

bool rk_bat_req_flag;

#define KEEP_AWAKE_INTERVAL 5000
uint32_t keep_awake_timer;

uint32_t keep_awake_callback(uint32_t trigger_time, void *cb_arg) {
    static bool status = false;
    report_mouse_t current_report = {};
    if (status) {
        current_report.y = 1;
    } else {
        current_report.y = -1;
    }
    host_mouse_send(&current_report);
    lpwr_update_timestamp();

    // prevent timeout
    if (*md_getp_state() == MD_STATE_CONNECTED) {
        last_matrix_activity_time();
    }

    status = !status;
    return 5000;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CUSTOM_CAPS: {
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LALT);
                unregister_code(KC_LSFT);
            }

            return false;
        } break;

        case KEEP_AWAKE: {
            static deferred_token delayed_exec = INVALID_DEFERRED_TOKEN;

            if (record->event.pressed) {
                if (keep_awake_timer) {
                    cancel_deferred_exec(delayed_exec);
                    keep_awake_timer = 0;
                    delayed_exec     = INVALID_DEFERRED_TOKEN;
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN);
                } else {
                    delayed_exec     = defer_exec(KEEP_AWAKE_INTERVAL, keep_awake_callback, NULL);
                    if (delayed_exec != INVALID_DEFERRED_TOKEN) keep_awake_timer = timer_read();
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_DIS);
                    md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_DIS);
                }
                return false;
            }

            return false;
        } break;

        case HS_BATQ: {
            rk_bat_req_flag = record->event.pressed;
            return false;
        } break;
    }

    return true;
}

void bar_sin(RGB color, uint32_t timer) {
    float diff = timer_elapsed32(timer);
    for (uint8_t i = 0; i < 14; i++) {
        float dim = 0.5f + 0.5f * (sinf(i / 2.0f + diff / 100.0f)); // range [0.5,1]
        rgb_matrix_set_color(10 + i, color.r * dim, color.g * dim, color.b * dim);
    }
}

void bar_fade(RGB color, uint32_t timer, uint32_t duration) {
    uint32_t diff = timer_elapsed32(timer);
    if (diff >= duration) return;
    float dim = (float)(duration - diff) / (float)duration;
    for (uint8_t i = 0; i < 14; i++) {
        rgb_matrix_set_color(10 + i, color.r * dim, color.g * dim, color.b * dim);
    }
}

bool rgb_matrix_indicators_user() {
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

    if (keep_awake_timer) {
        if (timer_elapsed(keep_awake_timer) / 500 % 2 == 0) {
            rgb_matrix_set_color(59, 0xFF, 0xFF, 0xFF);
        } else {
            rgb_matrix_set_color(59, 0x00, 0x00, 0x00);
        }
    }

    static RGB connecting = { 0xFC, 0xB2, 0x03 };
    static RGB pairing = { 0x00, 0x00, 0xFF };
    static RGB connected = { 0x00, 0xFF, 0x00 };

    if (kb_state.dev == DEVS_USB) {
        switch (kb_state.status) {
            case USB_ACTIVE: {
                bar_fade(connected, kb_state.changed_at, 2000);
            } break;
            case USB_SELECTED: {
                bar_sin(connected, kb_state.changed_at);
            } break;
            default: {
                bar_sin(connecting, kb_state.changed_at);
            } break;
        }
    } else {
        switch (kb_state.status) {
            case MD_STATE_CONNECTED: {
                bar_fade(connected, kb_state.changed_at, 2000);
            } break;
            case MD_STATE_PAIRING: {
                if (timer_elapsed32(kb_state.changed_at) > INDICATOR_TIMEOUT) break;
                bar_sin(pairing, kb_state.changed_at);
            } break;

            default: {
                if (timer_elapsed32(kb_state.changed_at) > INDICATOR_TIMEOUT) break;
                bar_sin(connecting, kb_state.changed_at);
            } break;
        }
    }

    return true;
}
