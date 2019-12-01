/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_A, KC_B,
        KC_C  , KC_D,
        KC_F, KC_E
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        KC_G  , KC_H,
        _______, KC_J,
        KC_K, KC_L
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_MS_LEFT);
        } else {
            tap_code(KC_MS_RIGHT);
        }
    }
    else if (index == 2) {
        if (clockwise) {
            tap_code(KC_MS_UP);
        } else {
            tap_code(KC_MS_DOWN);
        }
    }
    else if (index == 3) {
        if (clockwise) {
            tap_code(KC_G);
        } else {
            tap_code(KC_H);
        }
    }
    else if (index == 4) {
        if (clockwise) {
            tap_code(KC_I);
        } else {
            tap_code(KC_J);
        }
    }
    else if (index == 5) {
        if (clockwise) {
            tap_code(KC_L);
        } else {
            tap_code(KC_M);
        }
    }
}
