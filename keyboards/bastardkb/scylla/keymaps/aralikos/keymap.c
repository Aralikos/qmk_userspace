// The layout the keyboard ran under the stock VIA firmware, dumped from its
// dynamic keymap on 2026-09-23, plus layer reporting for the desktop bar.
#include QMK_KEYBOARD_H
#include "raw_hid.h"

// TG(1)/TG(2) on layer 0; on layers 1 and 2 the same two keys are TO(0), so
// either one always lands back on the base layer.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_4x6_5(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_HOME, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                          KC_LCTL, KC_SPC,  TG(1),      TG(2),   KC_ENT,  KC_LALT,
                                   KC_LSFT, KC_LGUI,     KC_BSPC, KC_LGUI),

    [1] = LAYOUT_split_4x6_5(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, _______, _______, _______, _______, KC_LBRC,    KC_RBRC, KC_P7,   KC_P8,   KC_P9,   _______, KC_PLUS,
        _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_LPRN,    KC_RPRN, KC_P4,   KC_P5,   KC_P6,   KC_MINS, KC_PIPE,
        _______, _______, _______, _______, _______, _______,    KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_EQL,  KC_UNDS,
                          _______, _______, TO(0),      TO(0),   _______, _______,
                                   _______, _______,     _______, _______),

    [2] = LAYOUT_split_4x6_5(
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, QK_BOOT, RM_PREV, RM_TOGG, RM_NEXT, KC_LBRC,    KC_RBRC, KC_PSCR, KC_NUM,  KC_INS,  KC_SCRL, KC_MUTE,
        _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LPRN,    KC_RPRN, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLU,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, KC_VOLD,
                          _______, _______, TO(0),      TO(0),   _______, _______,
                                   _______, _______,     _______, _______),
};

// Layer reports on the VIA raw HID interface: [0xFE, layer]. Sent on every
// change, and in reply to a 0xFE request so the bar can ask on startup.
#define LAYER_REPORT 0xFE

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t report[32] = {LAYER_REPORT, get_highest_layer(state)};
    raw_hid_send(report, sizeof(report));
    return state;
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] != LAYER_REPORT) return false;
    data[1] = get_highest_layer(layer_state);
    raw_hid_send(data, length);
    return true;
}
