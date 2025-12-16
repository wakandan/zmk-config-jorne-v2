// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layer definitions
enum layers {
    _BASE = 0,
    _NAV,      // Layer 1: Navigation
    _NUM,      // Layer 2: Numbers & Symbols
    _SYM       // Layer 3: Symbols
};

// Shorter aliases for readability
#define KC_LTF  LT(_NAV, KC_F)    // F when tapped, Layer 1 when held
#define KC_LTJ  LT(_NUM, KC_J)    // J when tapped, Layer 2 when held
#define KC_MOSM MO(_SYM)          // Momentary Symbol layer

// Mac-specific shortcuts (Cmd+bracket for tab switching in browsers/editors)
#define KC_CBRL LGUI(KC_LBRC)     // Cmd+[ (back in browser, prev tab in some apps)
#define KC_CBRR LGUI(KC_RBRC)     // Cmd+] (forward in browser, next tab in some apps)
#define KC_STBL LSG(KC_LBRC)      // Cmd+Shift+[ (prev tab in Chrome/Safari)
#define KC_STBR LSG(KC_RBRC)      // Cmd+Shift+] (next tab in Chrome/Safari)
#define KC_CGRV LGUI(KC_GRV)      // Cmd+` (switch windows of same app on Mac)
#define KC_ABSP LALT(KC_BSPC)     // Alt+Backspace (delete word on Mac)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 
     * Base Layer: QWERTY
     * 
     * Matrix wiring (from ZMK default_transform):
     * Row 0:       (0,1) (0,2) (0,3) (0,4) (0,5) (0,6)     (0,7) (0,8) (0,9) (0,10)(0,11)(0,12)
     * Row 1: (1,0) (1,1) (1,2) (1,3) (1,4) (1,5) (1,6)     (1,7) (1,8) (1,9) (1,10)(1,11)(1,12)(1,13)
     * Row 2: (2,0) (2,1) (2,2) (2,3) (2,4) (2,5) (2,6)     (2,7) (2,8) (2,9) (2,10)(2,11)(2,12)(2,13)
     * Row 3:                         (3,4) (3,5) (3,6)     (3,7) (3,8) (3,9)
     * 
     * Physical layout:
     *        ┌──────┬──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┬──────┐
     *        │ Tab  │  Q   │  W   │  E   │  R   │  T   │                    │  Y   │  U   │  I   │  O   │  P   │  [   │
     * ┌──────┼──────┼──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┼──────┼──────┐
     * │ Esc  │ Ctrl │  A   │  S   │  D   │ F/L1 │  G   │                    │  H   │ J/L2 │  K   │  L   │  ;   │  '   │Enter │
     * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
     * │ Esc  │Shift │  Z   │  X   │  C   │  V   │  B   │                    │  N   │  M   │  ,   │  .   │  /   │Shift │  ↑   │
     * └──────┴──────┴──────┴──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┴──────┴──────┴──────┘
     *                             │MO(3) │ Alt  │ GUI  │                    │Space │ Bksp │MO(3) │
     *                             └──────┴──────┴──────┘                    └──────┴──────┴──────┘
     * 
     * Note: (0,0) is not wired. Tab and Ctrl share the same physical column.
     *       Y, H, N are in the same column on the right side.
     */
    [_BASE] = LAYOUT(
        // Row 0: Left (6 keys) then Right (6 keys)
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        // Row 1: Left (7 keys) then Right (7 keys)
        KC_ESC,  KC_RCTL, KC_A,    KC_S,    KC_D,    KC_LTF,  KC_G,
        KC_H,    KC_LTJ,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        // Row 2: Left (7 keys) then Right (7 keys)
        KC_ESC,  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        // Row 3: Left thumb (3 keys) then Right thumb (3 keys)
        KC_MOSM, KC_LALT, KC_LGUI,
        KC_SPC,  KC_BSPC, KC_MOSM
    ),

    /* 
     * Layer 1: Navigation
     */
    [_NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,
        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_MINS, _______,
        _______, _______, _______, _______, _______, _______, _______,
        KC_CBRL, KC_STBL, KC_STBR, KC_CBRR, KC_EQL,  KC_UNDS, _______,
        _______, _______, _______, _______, _______, _______, _______,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    /* 
     * Layer 2: Numbers & Symbols
     */
    [_NUM] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______
    ),

    /* 
     * Layer 3: Symbols
     */
    [_SYM] = LAYOUT(
        KC_CGRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,
        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
        _______, _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, _______,
        _______, _______, KC_GRV,  KC_GRV,  KC_GRV,  KC_TILD, KC_PIPE,
        KC_RBRC, KC_LBRC, KC_LCBR, KC_RCBR, KC_BSLS, KC_GRV,  _______,
        _______, _______, _______,
        _______, KC_ABSP, _______
    )
};

/* Encoder mappings */
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NAV]  = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_NUM]  = { ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_SYM]  = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) }
};
#endif

/* Optional: Per-key tapping term customization */
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LTF:
        case KC_LTJ:
            return 180;  // Slightly faster for frequently used layer-tap keys
        default:
            return TAPPING_TERM;
    }
}
#endif
