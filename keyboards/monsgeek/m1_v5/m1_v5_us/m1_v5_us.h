#pragma once

#include QMK_KEYBOARD_H

typedef struct kb_state_t {
    uint8_t dev;
    uint8_t status;
    uint32_t changed_at;
} kb_status_t;

typedef struct kb_dev_info_t {
    uint32_t key;
    RGB color;
} kb_dev_info_t;

kb_dev_info_t kb_dev_info[5];
struct kb_state_t kb_state;