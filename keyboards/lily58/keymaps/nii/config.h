/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define ONESHOT_TIMEOUT 3000

#define TAPPING_FORCE_HOLD
#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// Usefull for dual keys when you fast tap and release
#define PERMISSIVE_HOLD
// hope that this disables this feature
/* #define ONESHOT_TAP_TOGGLE 15 */
#define COMBO_COUNT 0
// I think that this is the time between the first key press and the second one
// If it is too small, the combo will be ignored
#define COMBO_TERM 500

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#undef RGB_DI_PIN
#define RGB_DI_PIN D4
#define RGBLED_SPLIT { 10, 10 }
#define RGBLED_NUM 20

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODERS_PAD_A_RIGHT { F5 }
#define ENCODERS_PAD_B_RIGHT { F4 }

// Uncomment this if you use an ALPS EC11K encoder, or are noticing missing encoder actuations
// #define ENCODER_RESOLUTION 2

// Underglow
/*
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
*/

