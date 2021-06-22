/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _QWERTY_VIM,
  _NORMAL,
  _NUMS,
  _VISUAL
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
};

#define LOWER MO(_NORMAL)
#define RAISE MO(_NUMS)

// Tap Dance '' becomes ''arrowLeft
void dance_f13_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_ESC);
    } else {
        register_code(KC_F13);
        /* PLAY_SONG(my_leader_succeed); */
    }
}

void dance_f13_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_ESC);
    } else {
        unregister_code(KC_F13);
    }
    layer_clear();
    layer_on(_QWERTY);
}

void dance_fen_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        /* register_code(KC_ESC); */
        tap_code16(KC_ESC);
    } else {
        layer_clear();
        layer_on(_NORMAL);
        /* register_code(KC_F13); */
        /* PLAY_SONG(my_leader_succeed); */
    }
}

void dance_fen_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        /* unregister_code(KC_ESC); */
    } else {
        /* layer_clear(); */
        /* layer_on(_NORMAL); */
    }
}

// aoa Escape if tapped once, F13 if quickly tap it twice
// Tap Dance declarations
enum {
    TD_ESC_F13,
    TD_ESC_TO_NORMAL,
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for F13
    [TD_ESC_F13] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f13_finished, dance_f13_reset),
    [TD_ESC_TO_NORMAL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_fen_finished, dance_fen_reset)
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_NO, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


[_QWERTY_VIM] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_NORMAL] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMS] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),


/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_VISUAL] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  KC_NO,  KC_NO,  KC_NO,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool wasVimLayer = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _NORMAL:
            if (IS_LAYER_ON_STATE(state, _NORMAL)) {
                tap_code(KC_F18);
                wasVimLayer = true;
            } else {
                /* tap_code(KC_F17); */
            }
            break;
        case _VISUAL:
            if (IS_LAYER_ON_STATE(state, _VISUAL)) {
                tap_code(KC_F19);
                wasVimLayer = true;
            } else {
                /* tap_code(KC_F17); */
            }
            break;
        case _QWERTY_VIM:
            if (IS_LAYER_ON_STATE(state, _QWERTY_VIM)) {
                // Do not send F17 if we are returning from _NORMAL_TMP
                tap_code(KC_F20);
                wasVimLayer = true;
            } else {
                /* tap_code(KC_F17); */
            }
        case _QWERTY:
            if (IS_LAYER_ON_STATE(state, _QWERTY)) {
                // Do not send F17 if we are returning from _NORMAL_TMP
                if (wasVimLayer == true) {
                    tap_code(KC_F17);
                }
                wasVimLayer = false;
            } else {
                /* tap_code(KC_F17); */
            }
            break;
    }
    return state;
}
/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); */
/* } */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    /* case COLEMAK: */
    /*   if (record->event.pressed) { */
    /*     set_single_persistent_default_layer(_COLEMAK); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case DVORAK: */
    /*   if (record->event.pressed) { */
    /*     set_single_persistent_default_layer(_DVORAK); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case BACKLIT: */
    /*   if (record->event.pressed) { */
    /*     register_code(KC_RSFT); */
    /*     #ifdef BACKLIGHT_ENABLE */
    /*       backlight_step(); */
    /*     #endif */
    /*     #ifdef KEYBOARD_planck_rev5 */
    /*       writePinLow(E6); */
    /*     #endif */
    /*   } else { */
    /*     unregister_code(KC_RSFT); */
    /*     #ifdef KEYBOARD_planck_rev5 */
    /*       writePinHigh(E6); */
    /*     #endif */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case PLOVER: */
    /*   if (record->event.pressed) { */
    /*     #ifdef AUDIO_ENABLE */
    /*       stop_all_notes(); */
    /*       PLAY_SONG(plover_song); */
    /*     #endif */
    /*     layer_off(_RAISE); */
    /*     layer_off(_LOWER); */
    /*     layer_off(_ADJUST); */
    /*     layer_on(_PLOVER); */
    /*     if (!eeconfig_is_enabled()) { */
    /*         eeconfig_init(); */
    /*     } */
    /*     keymap_config.raw = eeconfig_read_keymap(); */
    /*     keymap_config.nkro = 1; */
    /*     eeconfig_update_keymap(keymap_config.raw); */
    /*   } */
    /*   return false; */
    /*   break; */
    /* case EXT_PLV: */
    /*   if (record->event.pressed) { */
    /*     #ifdef AUDIO_ENABLE */
    /*       PLAY_SONG(plover_gb_song); */
    /*     #endif */
    /*     layer_off(_PLOVER); */
    /*   } */
    /*   return false; */
    /*   break; */
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

/* void encoder_update(bool clockwise) { */
/*   if (muse_mode) { */
/*     if (IS_LAYER_ON(_RAISE)) { */
/*       if (clockwise) { */
/*         muse_offset++; */
/*       } else { */
/*         muse_offset--; */
/*       } */
/*     } else { */
/*       if (clockwise) { */
/*         muse_tempo+=1; */
/*       } else { */
/*         muse_tempo-=1; */
/*       } */
/*     } */
/*   } else { */
/*     if (clockwise) { */
/*       #ifdef MOUSEKEY_ENABLE */
/*         tap_code(KC_MS_WH_DOWN); */
/*       #else */
/*         tap_code(KC_PGDN); */
/*       #endif */
/*     } else { */
/*       #ifdef MOUSEKEY_ENABLE */
/*         tap_code(KC_MS_WH_UP); */
/*       #else */
/*         tap_code(KC_PGUP); */
/*       #endif */
/*     } */
/*   } */
/* } */

/* void dip_switch_update_user(uint8_t index, bool active) { */
/*     switch (index) { */
/*         case 0: { */
/* #ifdef AUDIO_ENABLE */
/*             static bool play_sound = false; */
/* #endif */
/*             if (active) { */
/* #ifdef AUDIO_ENABLE */
/*                 if (play_sound) { PLAY_SONG(plover_song); } */
/* #endif */
/*                 layer_on(_ADJUST); */
/*             } else { */
/* #ifdef AUDIO_ENABLE */
/*                 if (play_sound) { PLAY_SONG(plover_gb_song); } */
/* #endif */
/*                 layer_off(_ADJUST); */
/*             } */
/* #ifdef AUDIO_ENABLE */
/*             play_sound = true; */
/* #endif */
/*             break; */
/*         } */
/*         case 1: */
/*             if (active) { */
/*                 muse_mode = true; */
/*             } else { */
/*                 muse_mode = false; */
/*             } */
/*     } */
/* } */

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
