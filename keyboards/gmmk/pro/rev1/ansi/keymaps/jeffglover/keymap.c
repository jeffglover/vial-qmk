/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

enum custom_layers {
    _BASE,
    _FN1,
    _MO2,
    _MO3,
};

bool _isWinKeyDisabled = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(2), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, KC_HOME,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_MO2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_MO3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN1]  = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [_MO2]  = {ENCODER_CCW_CW(LCTL(KC_LEFT), LCTL(KC_RGHT))},
    [_MO3]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};

#ifdef RGB_MATRIX_ENABLE
// Capslock, Scroll lock and Numlock  indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        rgb_matrix_set_color(LED_L1, RGB_GREEN);
        rgb_matrix_set_color(LED_L2, RGB_GREEN);
    }
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // on if NUM lock is OFF
        rgb_matrix_set_color(LED_L3, RGB_MAGENTA);
        rgb_matrix_set_color(LED_L4, RGB_MAGENTA);
    }
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
        rgb_matrix_set_color(LED_L8, RGB_RED);
        rgb_matrix_set_color(LED_CAPS, RGB_RED);
    }
    if (_isWinKeyDisabled) {
        rgb_matrix_set_color(LED_LGUI, RGB_RED); // light up Win key when disabled
    }

    // Layer indicators on right side lights.
    if (layer_state_is(_FN1)) {
        rgb_matrix_set_color(LED_R1, RGB_RED);
        rgb_matrix_set_color(LED_R2, RGB_RED);
        rgb_matrix_set_color(LED_R3, RGB_RED);
        rgb_matrix_set_color(LED_R4, RGB_RED);
        rgb_matrix_set_color(LED_FN, RGB_RED);
        rgb_matrix_set_color(LED_END, RGB_RED);
    }

    switch (get_highest_layer(layer_state)) { // special handling per layer
        case _FN1:                            // on Fn layer select what the encoder does when pressed
            // Add RGB Timeout Indicator -- shows 0 to 139 using F row and num row;  larger numbers using 16bit code
            // if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_RED);
            // else if (timeout_threshold < 140) {
            //     rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[(timeout_threshold % 10)], RGB_RED);
            // } else { // >= 140 minutes, just show these 3 lights
            //     rgb_matrix_set_color(LED_LIST_NUMROW[10], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[11], RGB_RED);
            //     rgb_matrix_set_color(LED_LIST_NUMROW[12], RGB_RED);
            // }
            break;
        case _MO2: // Numpad layer
            rgb_matrix_set_color(LED_R5, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R6, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R7, RGB_MAGENTA);
            rgb_matrix_set_color(LED_R8, RGB_MAGENTA);
            break;
        case _MO3:
            rgb_matrix_set_color(LED_R5, RGB_GREEN);
            rgb_matrix_set_color(LED_R6, RGB_GREEN);
            rgb_matrix_set_color(LED_R7, RGB_GREEN);
            rgb_matrix_set_color(LED_R8, RGB_GREEN);
            break;
        default:
            break;
    }
}
#endif
