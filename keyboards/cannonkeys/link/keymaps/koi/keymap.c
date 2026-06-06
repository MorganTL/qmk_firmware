// Copyright 2026 Morgan Cheng
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_MUTE, KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
           KC_LALT, KC_LALT, KC_LGUI, KC_SPC, LT(2, KC_ENT),           OSL(1),  KC_SPC,  KC_RGUI, KC_RALT, KC_MPLY
),

[1] = LAYOUT(
  KC_F12,   KC_F1,   KC_F2,      KC_F3,     KC_F4,      KC_F5,                     KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
  KC_TRNS,  KC_QUOT, S(KC_COMM), S(KC_DOT), S(KC_QUOT), KC_GRV,                    S(KC_7),    KC_SCLN,    KC_LBRC,    KC_RBRC,    S(KC_5),    KC_TRNS,
  KC_TRNS,  S(KC_1), KC_PMNS,    KC_PPLS,   KC_EQL,     S(KC_3),                   S(KC_BSLS), S(KC_MINS), S(KC_9),    S(KC_0),    S(KC_SLSH), KC_TRNS,
  KC_TRNS,  S(KC_6), KC_SLSH,    S(KC_8),   KC_BSLS,    KC_SLSH, KC_TRNS, KC_TRNS, S(KC_GRV),  S(KC_4),    S(KC_LBRC), S(KC_RBRC), S(KC_2),    KC_TRNS,
            KC_TRNS, KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,                   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
),

[2] = LAYOUT(
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
  QK_BOOT, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_PSCR, KC_TRNS,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_CALC,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_VOLD,  KC_VOLU,  KC_MPLY, KC_TRNS,
           KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
)
};

// Encoder setup
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Encoder index do NOT change when kb master is switched (plugging in via a different USB port)
    if (index == 0) {
        // Left encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Right encoder
        if (clockwise) {
            tap_code(MS_WHLU);
        } else {
            tap_code(MS_WHLD);
        }
    }
    return false;
}

// OLED setup
const char PROGMEM qmk_logo[] = {
    // https://joric.github.io/qle/
    // Like C str, this MUST be null terminated
    // ASCII encoding: 0x0A = next line, 0x00 = null, >0x7F are custom bitmaps
    0x0A,
    0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x0A,
    0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0x0A,
    0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0x0A,
    0x00,
};

void user_render(void) {
    oled_write_ln_P(qmk_logo, false);

    // Layer status
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Vim"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
    oled_write_P(PSTR("\n"), false);

    // Modifier status
    oled_write_ln_P(PSTR("MOD"), false);
    uint8_t status = get_mods();
    oled_write_P(PSTR("Ctrl"), status & MOD_MASK_CTRL);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Shift"), status & MOD_MASK_SHIFT);
    oled_write_P(PSTR("Alt"), status & MOD_MASK_ALT);
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR("Super\n"), status & MOD_MASK_GUI);
}

// Normal screen
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    // The SH1107 does NOT support oled_scroll
    user_render();
    return false;
}

// Bootloader screen
void oled_render_boot(bool bootloader) {
    oled_clear();
    oled_set_cursor(0, 0);

    oled_write_ln_P(qmk_logo, false);
    if (bootloader) {
        oled_write_ln_P(PSTR("LINK ERGO"), false);
        oled_write_ln_P(PSTR("BOOTLOADER\n"), false);
        oled_write_P(PSTR("Awaiting\nnew fw..."), false);
    } else {
        oled_write_P(PSTR("Rebooting\n..."), false);
    }
    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    // false to not process kb level
    return false;
}
