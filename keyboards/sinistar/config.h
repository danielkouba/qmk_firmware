/*
Copyright 2019 Danny Nguyen <danny@keeb.io>

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB10
#define PRODUCT_ID      0x1133
#define DEVICE_VER      0x0100
#define MANUFACTURER    Kouba
#define PRODUCT         Sinistar
#define DESCRIPTION     3x2 Macropad with Rotary Encoders

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 2

#define DIODE_DIRECTION COL2ROW


/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { \
    D4, C6, D7 \
}
#define MATRIX_COL_PINS { \
    E6, B4 \
}

/*                      RE0,RE1,RE2,RE3,RE4,RE5*/
#define ENCODERS_PAD_A { D1, F6, D2, B2, F4, B1}
#define ENCODERS_PAD_B { D0, F7, D3, B6, F5, B3}


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
