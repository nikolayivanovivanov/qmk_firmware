// In case of clangd finding many errors, change
//pip3 install scan-build
//make clean
//intercept-build make lily58/rev1:nii
//You have to replace all /vagrant in the compile_commands.json file with c:/data/www/projects/qmk/qmk_firmware
//
//
#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
/* #define _LOWER 1 */
/* #define _RAISE 2 */
/* #define _ADJUST 3 */
#define _NAV 1
#define _VIMIDEA 2
/* #define _SYMRL 5 */
/* #define _SYMLL 6 */
#define _APP 3
#define _DBGL 4

/* #define _QWERTY 0 */
/* #define _NAV 1 */
/* #define _SYMRL 2 */
/* #define _SYMLL 3 */
/* #define _APP 4 */
/* #define _DBGL 5 */


/* enum custom_keycodes { */
/*   QWERTY = SAFE_RANGE, */
/*   LOWER, */
/*   RAISE, */
/*   ADJUST */
/* }; */

enum custom_keycodes {
    /* RGB_SLD = SAFE_RANGE, */
    QWERTY = SAFE_RANGE,
    ST_MACRO_PLUS,
    ST_MACRO_LCBR,
    ST_MACRO_RCBR,
    ST_MACRO_LPRN,
    ST_MACRO_RPRN,
    ST_MACRO_LABK,
    ST_MACRO_RABK,
    ST_MACRO_LBRK,
    ST_MACRO_RBRK,
    ST_MACRO_SCLN,
    ST_MACRO_SCLN_END,
    ST_MACRO_DOT,
    ST_MACRO_QUOT,
    ST_MACRO_GRAVE,
    ST_MACRO_TO_NAV,
    /* ST_MACRO_TO_BASE, */
    /* ST_MACRO_ESC_TO_BASE, */
    /* ST_MACRO_YANK, */
    /* ST_MACRO_PUT, */
    /* ST_MACRO_CHANGE, */
    /* ST_MACRO_CUT, */
    ST_MACRO_START_DEBUG,
    /* ST_MACRO_CAPSLOCK, */
    ST_MACRO_CTRL_OR_BRACKET,
    ST_MACRO_RALT_OR_RBRACKET,
    ST_MACRO_STRUCT,
    ST_MACRO_0,
    ST_MACRO_1,
    ST_MACRO_2,
    ST_MACRO_3,
    ST_MACRO_4,
    ST_MACRO_5,
    ST_MACRO_6,
    ST_MACRO_7,
    /* ST_MACRO_8, */
    ST_MACRO_9,
    ST_MACRO_10,
    ST_MACRO_11,
    /* ST_MACRO_12, */
    /* ST_MACRO_13, */
    ST_MACRO_14,
    ST_MACRO_15,
    ST_MACRO_16,
    ST_MACRO_VIM_SEARCH,
    ST_MACRO_PASTE_HISTORY,
    ST_MACRO_EXT_SEL,
    ST_MACRO_EM,
    ST_SEMIM,
    ST_MACRO_ARROW,
    ST_MACRO_EQ_ARROW,
    /* ST_MACRO_18, */
    /* ST_MACRO_19, */
    /* ST_MACRO_20, */
    /* ST_MACRO_21, */
    /* ST_MACRO_22, */
    /* ST_MACRO_23, */
    /* ST_MACRO_24, */
    /* ST_MACRO_25, */
    /* ST_MACRO_26, */
    /* ST_MACRO_27, */
    /* ST_MACRO_28, */
    /* ST_MACRO_29, */
    ST_MACRO_30,
    ST_MACRO_31,
    /* ST_MACRO_32, */
    /* ST_MACRO_33, */
    /* ST_MACRO_34, */
    /* ST_MACRO_35, */
    /* ST_MACRO_36, */
    /* ST_MACRO_37, */
    /* ST_MACRO_38, */
    /* ST_MACRO_39, */
    /* ST_MACRO_40, */
    /* ST_MACRO_41, */
    /* ST_MACRO_42, */
    /* ST_MACRO_43, */
    /* ST_MACRO_44, */
    /* ST_MACRO_45, */
    /* ST_MACRO_46, */
    /* ST_MACRO_47, */
    /* ST_MACRO_48, */
    /* ST_MACRO_49, */
    /* ST_MACRO_50, */
    /* ST_MACRO_51, */
};

// Lag and leads to unwanted layer switches
// enum combos {
//   SS_LAYER,
//   SS_LAYER_R,
// //   SSP_LAYER,
// //   SSP_LAYER_R
//   /* WE_LAYER_APP, */
//   /* SD_LAYER_VIMIDEA, */
//   /* XC_LAYER_DEBUG, */
//   /* IO_LAYER_APP_R, */
//   /* KL_LAYER_VIMIDEA_R */
// };

// const uint16_t PROGMEM ss_combo[] = {KC_LSHIFT, KC_RSHIFT, COMBO_END};
// const uint16_t PROGMEM ss_combo_r[] = {KC_RSHIFT, KC_LSHIFT, COMBO_END};
// // const uint16_t PROGMEM ssp_combo[] = {KC_LSHIFT, KC_LSPO, COMBO_END};
// // const uint16_t PROGMEM ssp_combo_r[] = {KC_RSHIFT, KC_RSPC, COMBO_END};

// /* const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END}; */
// /* const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END}; */
// /* const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END}; */
// /* const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END}; */
// /* const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END}; */

// combo_t key_combos[COMBO_COUNT] = {
//   [SS_LAYER] = COMBO_ACTION(ss_combo),
//   [SS_LAYER_R] = COMBO_ACTION(ss_combo_r),
// //   [SSP_LAYER] = COMBO_ACTION(ssp_combo),
// //   [SSP_LAYER_R] = COMBO_ACTION(ssp_combo_r)
//   /* [WE_LAYER_APP] = COMBO_ACTION(we_combo), */
//   /* [IO_LAYER_APP_R] = COMBO_ACTION(io_combo), */
//   /* [SD_LAYER_VIMIDEA] = COMBO_ACTION(sd_combo), */
//   /* [KL_LAYER_VIMIDEA_R] = COMBO_ACTION(kl_combo), */
//   /* [XC_LAYER_DEBUG] = COMBO_ACTION(xc_combo) */
// };

// void process_combo_event(uint16_t combo_index, bool pressed) {
//   switch(combo_index) {
//     // case SS_LAYER:
//     // case SS_LAYER_R:
//     //   if (pressed) {
//     //       register_code16(KC_F23);
//     //   } else {
//     //       unregister_code16(KC_F23);
//     //   }
//     //   break;
//     case SS_LAYER:
//     case SS_LAYER_R:
//     /* case WE_LAYER_APP: */
//     /* case IO_LAYER_APP_R: */
//       if (pressed) {
//           layer_clear();
//           layer_on(_APP);
//       } else {
//           layer_clear();
//           layer_on(_QWERTY);
//       }
//       break;
//     // case SSP_LAYER:
//     // case SSP_LAYER_R:
//     // // case SD_LAYER_VIMIDEA:
//     // // case KL_LAYER_VIMIDEA_R:
//     //   if (pressed) {
//     //       layer_clear();
//     //       layer_on(_VIMIDEA);
//     //   } else {
//     //       layer_clear();
//     //       layer_on(_QWERTY);
//     //   }
//     //   break;
//     /* case XC_LAYER_DEBUG: */
//     /*   if (pressed) { */
//     /*       layer_clear(); */
//     /*       layer_on(_DBGL); */
//     /*   } else { */
//     /*       layer_clear(); */
//     /*       layer_on(_QWERTY); */
//     /*   } */
//     /*   break; */
//   }
// }
// Tap Dance '' becomes ''arrowLeft
void dance_quot_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_QUOTE);
    } else {
        register_code(KC_QUOTE);
    }
}

void dance_quot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_QUOTE);
    } else {
        unregister_code(KC_QUOTE);
        tap_code(KC_QUOTE);
        // did not work
        /* unregister_code16(KC_LSFT); */
        /* unregister_code16(KC_RSFT); */
        /* UP(KC_LSFT); */
        /* SEND_STRING(SS_DELAY(4000) SS_TAP(X_LEFT)); */
        /* UP(KC_LSFT); */
        /* SEND_STRING( SS_TAP(X_LEFT)); */
        uint8_t current_mods = keyboard_report->mods;
        del_mods(keyboard_report->mods);
        // clear_mods();
        tap_code(KC_LEFT);
        // add_last_key(KC_LEFT);
        add_mods(current_mods);
        // tap_code(KC_LEFT);
    }
}


// Tap Dance `` becomes ``arrowLeft
void dance_bquot_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_GRAVE);
    } else {
        register_code(KC_GRAVE);
    }
}

void dance_bquot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_GRAVE);
    } else {
        unregister_code(KC_GRAVE);
        tap_code(KC_GRAVE);
        tap_code(KC_LEFT);
    }
}


// Tap Dance "" becomes ""arrowLeft
void dance_dquot_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(S(KC_QUOTE));
    } else {
        register_code16(S(KC_QUOTE));
    }
}

void dance_dquot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(S(KC_QUOTE));
    } else {
        unregister_code16(S(KC_QUOTE));
        tap_code16(S(KC_QUOTE));
        // No solution for this https://github.com/qmk/qmk_firmware/issues/4758
        // To make it work with shift ' for "
        // Did not work
        /* clear_mods(); */
        // Did not work
        /* unregister_code(KC_LSFT); */
        tap_code(KC_LEFT);
    }
}

// Tap Dance .. becomes ..arrowLeft
void dance_ddot_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_DOT);
    } else {
        register_code(KC_DOT);
    }
}

void dance_ddot_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_DOT);
    } else {
        unregister_code(KC_DOT);
        tap_code(KC_DOT);
        tap_code(KC_LEFT);
    }
}


// Tap Dance ++ becomes ++arrowLeft
void dance_dplus_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(S(KC_EQUAL));
    } else {
        register_code16(S(KC_EQUAL));
    }
}

void dance_dplus_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(S(KC_EQUAL));
    } else {
        unregister_code16(S(KC_EQUAL));
        tap_code16(S(KC_EQUAL));
        tap_code(KC_LEFT);
    }
}


// ((, {{, <<, [[ become (|), {|}, <|>, [|]

// -----PRN
void dance_dprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LPRN);
    } else {
        register_code16(KC_LPRN);
    }
}

void dance_dprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LPRN);
    } else {
        unregister_code16(KC_LPRN);
        tap_code16(KC_RPRN);
        // No solution for this https://github.com/qmk/qmk_firmware/issues/4758
        // To make it work with shift ' for "
        // Did not work
        /* clear_mods(); */
        // Did not work
        /* unregister_code(KC_LSFT); */
        tap_code(KC_LEFT);
    }
}

void dance_drprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_RPRN);
    } else {
        register_code16(KC_RPRN);
    }
}

void dance_drprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_RPRN);
    } else {
        unregister_code16(KC_RPRN);
        tap_code16(KC_SCOLON);
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
        tap_code16(KC_LPRN);
    }
}


//-----CBR
void dance_dcbr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LCBR);
    } else {
        register_code16(KC_LCBR);
    }
}

void dance_dcbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LCBR);
    } else {
        unregister_code16(KC_LCBR);
        tap_code16(KC_RCBR);
        tap_code(KC_LEFT);
    }
}

void dance_drcbr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_RCBR);
    } else {
        register_code16(KC_RCBR);
    }
}

void dance_drcbr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_RCBR);
    } else {
        unregister_code16(KC_RCBR);
        tap_code(KC_LEFT);
        tap_code(KC_LEFT);
        tap_code16(KC_LCBR);
        tap_code16(KC_ENTER);
    }
}

//-----ABK
void dance_dabk_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LABK);
    } else {
        register_code16(KC_LABK);
    }
}

void dance_dabk_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LABK);
    } else {
        unregister_code16(KC_LABK);
        tap_code16(KC_RABK);
        tap_code(KC_LEFT);
    }
}


//-----BRACKET
void dance_dbracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LBRACKET);
    } else {
        register_code16(KC_LBRACKET);
    }
}

void dance_dbracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LBRACKET);
    } else {
        unregister_code16(KC_LBRACKET);
        tap_code16(KC_RBRACKET);
        tap_code(KC_LEFT);
    }
}


//----- SLASH becomes "space f" for easy motion search
/* void dance_dslash_finished(qk_tap_dance_state_t *state, void *user_data) { */
/*     if (state->count == 1) { */
/*         register_code(KC_SLASH); */
/*     } else { */
/*         register_code(KC_SPC); */
/*     } */
/* } */

/* void dance_dslash_reset(qk_tap_dance_state_t *state, void *user_data) { */
/*     if (state->count == 1) { */
/*         unregister_code(KC_SLASH); */
/*     } else { */
/*         unregister_code(KC_SPC); */
/*         tap_code(KC_F); */
/*     } */
/* } */

void dance_dscolon_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SCOLON);
    } else {
        register_code(KC_F22);
    }
}

void dance_dscolon_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SCOLON);
    } else {
        // 22 is used by AHK as ending char for hotstrings (abbreviations)
        unregister_code(KC_F22);
    }
}
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


// aoa Escape if tapped once, F13 if quickly tap it twice
// Tap Dance declarations
enum {
    TD_ESC_F13,
    TD_QUOT,
    TD_BQUOT,
    TD_DQUOT,
    TD_DOT,
    TD_PLUS,
    TD_LPRN,
    TD_LCBR,
    TD_LABK,
    TD_LBRACKET,
    TD_RPRN,
    TD_RCBR,
    TD_SCOLON,
    /* TD_SLASH, */
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for F13
    [TD_ESC_F13] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_f13_finished, dance_f13_reset),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quot_finished, dance_quot_reset),
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dquot_finished, dance_dquot_reset),
    [TD_BQUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_bquot_finished, dance_bquot_reset),
    [TD_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dprn_finished, dance_dprn_reset),
    [TD_LCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dcbr_finished, dance_dcbr_reset),
    [TD_LABK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dabk_finished, dance_dabk_reset),
    [TD_LBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dbracket_finished, dance_dbracket_reset),

    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ddot_finished, dance_ddot_reset),
    [TD_PLUS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dplus_finished, dance_dplus_reset),
    [TD_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drprn_finished, dance_drprn_reset),
    [TD_RCBR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_drcbr_finished, dance_drcbr_reset),
    /* [TD_SCOLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dscolon_finished, dance_dscolon_reset), */
    // problem when adding single line comments
    /* [TD_SLASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dslash_finished, dance_dslash_reset), */
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |                    |   7  |   8  |   9  |   0  |  -   |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |RCtrl | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  TD(TD_ESC_F13)                  , KC_1 , KC_2 , KC_3                      , KC_4           , KC_5       /* ,                , */      , KC_6      , KC_7            , KC_8            , KC_9   , KC_0    , KC_BSPC       ,
//   KC_LBRACKET           , KC_Q , KC_W , KC_E                      , KC_R           , KC_T      /*  ,                , */      , KC_Y      , KC_U            , KC_I            , KC_O   , KC_P    , KC_RBRACKET ,
  ST_MACRO_LBRK           , KC_Q , KC_W , KC_E                      , KC_R           , KC_T      /*  ,                , */      , KC_Y      , KC_U            , KC_I            , KC_O   , KC_P    , ST_MACRO_RBRK ,
  ST_MACRO_GRAVE          , KC_A , KC_S , KC_D                      , KC_F           , KC_G     /*   ,                , */      , KC_H      , KC_J            , KC_K            , KC_L   , KC_SCOLON , ST_MACRO_QUOT ,
  LSFT_T(KC_F13)                 , KC_Z , KC_X , KC_C                      , KC_V           , KC_B          , LT(_VIMIDEA, KC_ENTER) , LT(_VIMIDEA, KC_HOME) , KC_N      , KC_M            , KC_COMM         , ST_MACRO_DOT , KC_SLSH , RSFT_T(KC_END)       ,
                       /* ,      ,      , */      LALT_T(KC_BSLASH) , KC_LCTRL , KC_LSHIFT     , MO(_NAV)       , KC_SPC  , KC_RSHIFT , RCTL_T(KC_MINS) , LALT_T(KC_EQL) /* ,        , */
),

  // vim normal
 [_NAV] = LAYOUT(
  KC_NO     , KC_NO       , KC_NO          , MO(_DBGL)                          , KC_END      , KC_NO         /*         ,                         , */       , KC_HOME         , KC_PGDN        , KC_PGUP          , KC_END   , KC_NO           , KC_DEL  ,
  KC_NO , TO(_QWERTY) , LCTL(KC_RIGHT) , LCTL(KC_RIGHT)                      , LCTL(KC_Y) , KC_NO         /* ,                         , */       , LCTL(KC_INSERT) , LCTL(KC_Z)     , KC_HOME          , KC_END   , LSFT(KC_INSERT) , ST_MACRO_31 ,
//   KC_NO         , OSL(_APP)   , OSL(_VIMIDEA)          , KC_DELETE                           , KC_NO      , KC_NO    /*              ,                         , */       , KC_LEFT         , KC_DOWN        , KC_UP            , KC_RIGHT , OSL(_VIMIDEA)   , ST_MACRO_31 ,
  KC_NO         , OSL(_APP)   , OSL(_VIMIDEA)          , KC_DELETE                           , KC_NO      , KC_NO    /*              ,                         , */       , KC_LEFT         , KC_DOWN        , KC_UP            , KC_RIGHT , ST_SEMIM   , KC_NO ,
  KC_LSHIFT     , KC_NO       , LCTL(KC_X)     , KC_DELETE                           , KC_LSFT    , LCTL(KC_LEFT)            , KC_ENTER               , KC_HOME  , KC_F3           , KC_APPLICATION , LSFT(KC_TAB)     , KC_TAB   , LCTL(KC_F)      , KC_END  ,
   /*           ,             ,                , */                          KC_LALT , KC_LCTRL   , KC_NO                    , KC_NO                  , MO(_APP) , KC_F23/*autocomplete*/       , ST_MACRO_ARROW , ST_MACRO_EQ_ARROW /* ,          , */
  )                                  ,

  [_VIMIDEA] = LAYOUT(
    KC_F12        , KC_F1      , KC_F2      , KC_F3                                , KC_F4       , KC_F5        /* ,            , */     , KC_F6        , KC_F7    , KC_F8         , KC_F9       , KC_F10                 , KC_F11        ,
    ST_MACRO_LCBR , ST_MACRO_1 , ST_MACRO_2 , ST_MACRO_3                           , ST_MACRO_4  , ST_MACRO_5   /* ,            , */     , ST_MACRO_15  , KC_NO    , KC_NO         , ST_MACRO_16 , ST_MACRO_PASTE_HISTORY , ST_MACRO_RCBR ,
    KC_NO         , ST_MACRO_6 , ST_MACRO_7 , KC_NO                                , ST_MACRO_9  , KC_NO        /* ,            , */     , KC_NO        , KC_NO    , KC_NO         , KC_NO       , ST_MACRO_SCLN_END      , KC_NO         ,
    KC_CAPS       , KC_NO      , KC_NO      , ST_MACRO_10                          , ST_MACRO_11 , ST_MACRO_31     , ST_MACRO_STRUCT , ST_MACRO_STRUCT  , KC_NO        , KC_NO    , LALT(KC_UP) , LALT(KC_DOWN)       , ST_MACRO_VIM_SEARCH    , KC_RSHIFT     ,
             /*   ,            ,            , */ RGUI(KC_SPACE)/*Change_language*/ , KC_CAPS     , MO(_APP)        , ST_MACRO_5 , KC_SPC , MO(_VIMIDEA) , ST_MACRO_ARROW , ST_MACRO_EQ_ARROW /*    ,             , */
  ),
  /* [_VIMIDEA] = LAYOUT( */
  /*   KC_F12                           ,  KC_F1     ,   KC_F2    , KC_F3       , KC_F4       , KC_F5                             , KC_F6       , KC_F7          , KC_F8         , KC_F9       , KC_F10                 ,  KC_F11    , */
  /*   ST_MACRO_0                       , ST_MACRO_1 , ST_MACRO_2 , ST_MACRO_3  , ST_MACRO_4  , ST_MACRO_5                        , ST_MACRO_15 , KC_NO          , KC_NO         , ST_MACRO_16 , ST_MACRO_PASTE_HISTORY , KC_NO      , */
  /*   KC_NO                            , ST_MACRO_6 , ST_MACRO_7 , ST_MACRO_8  , ST_MACRO_9  , KC_NO                             , KC_NO       , KC_NO          , KC_NO         , KC_NO       , ST_MACRO_SCLN_END      , KC_NO      , */
  /*   KC_CAPS                          , KC_NO      , KC_NO      , ST_MACRO_10 , ST_MACRO_11 , ST_MACRO_31 , KC_NO     , KC_NO   , KC_NO       , KC_NO          , LALT(KC_DOWN) , KC_NO       , ST_MACRO_VIM_SEARCH    , KC_RSHIFT  , */
  /*                            KC_RGUI, KC_BSLASH, MO(_APP), LCTL(KC_ENT),   KC_SPC,   MO(_VIMIDEA),   KC_RCTRL, KC_LALT */
  /* ), */

  /* [_SYMRL] = LAYOUT( */
  /* ST_MACRO_0, KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,    KC_PERC,    KC_CIRC,                     KC_AMPR,    KC_ASTR,    ST_MACRO_LPRN , ST_MACRO_RPRN,   KC_UNDS, */
  /*   ST_MACRO_LCBR                    , ST_MACRO_1 , ST_MACRO_2 , ST_MACRO_3  , ST_MACRO_4  , ST_MACRO_5  , KC_BSLASH , KC_UNDS , ST_MACRO_LBRK , ST_MACRO_RBRK , ST_MACRO_PLUS , ST_MACRO_RCBR      , */
  /*   KC_NO                            , ST_MACRO_6 , ST_MACRO_7 , OSL(_DBGL)  , ST_MACRO_9  , KC_NO       , KC_HASH   , KC_PIPE , ST_MACRO_LCBR , ST_MACRO_RCBR , KC_EQUAL      , LSFT(ST_MACRO_QUOT)         , */
  /*   KC_LSHIFT                        , KC_NO      , KC_NO      , ST_MACRO_10 , ST_MACRO_11 , ST_MACRO_31 , KC_NO     , KC_NO   , KC_NO         , KC_NO         , ST_MACRO_LABK , ST_MACRO_RABK , KC_BSLASH , LSFT(ST_MACRO_QUOT) , */
  /*                            KC_LALT , KC_LCTRL   , MO(_APP)   , MO(_NAV)    , KC_ENT      , MO(_APP)    , ST_MACRO_LBRK , ST_MACRO_RBRK */
  /* ), */

  /* [_SYMRL] = LAYOUT( */
  /*   KC_F1                            , KC_F2      , KC_F3      , KC_F4       , KC_F5       , KC_F6       , KC_F7     , KC_F8   , ST_MACRO_LPRN , ST_MACRO_RPRN , KC_F11        , KC_F12        , */
  /*   ST_MACRO_0                       , ST_MACRO_1 , ST_MACRO_2 , ST_MACRO_3  , ST_MACRO_4  , ST_MACRO_5  , KC_BSLASH , KC_UNDS , ST_MACRO_LBRK , ST_MACRO_RBRK , ST_MACRO_PLUS , KC_MINUS      , */
  /*   KC_NO                            , ST_MACRO_6 , ST_MACRO_7 , ST_MACRO_8  , ST_MACRO_9  , KC_NO       , KC_HASH   , KC_PIPE , ST_MACRO_LCBR , ST_MACRO_RCBR , KC_EQUAL      , KC_NO         , */
  /*   KC_LSHIFT                        , KC_NO      , MO(_DBGL)      , ST_MACRO_10 , ST_MACRO_11 , ST_MACRO_31 , KC_NO     , KC_NO   , KC_NO         , KC_NO         , ST_MACRO_LABK , ST_MACRO_RABK , KC_BSLASH , KC_NO , */
  /*                            KC_LALT , KC_LCTRL   , MO(_APP)   , MO(_NAV)    , KC_ENT      , MO(_APP)    , ST_MACRO_LBRK , ST_MACRO_RBRK */
  /* ), */

  /* [_SYMLL] = LAYOUT( */
  /* KC_PLUS                  , KC_EXLM , KC_AT    , KC_HASH        , KC_DLR           , KC_PERC        , KC_CIRC     , KC_AMPR , KC_ASTR , ST_MACRO_LPRN , ST_MACRO_RPRN          , KC_UNDS       , */
  /*         ST_MACRO_LCBR    , KC_NO   , KC_NO    , KC_EXLM        , KC_NO            , KC_TILD        , ST_MACRO_15 , KC_NO   , KC_NO   , ST_MACRO_16   , ST_MACRO_PASTE_HISTORY , ST_MACRO_RCBR , */
  /*         KC_NO            , KC_AT   , KC_AMPR  , KC_DLR         , ST_MACRO_EM      , KC_NO          , KC_NO       , KC_NO   , KC_NO   , KC_NO         , ST_MACRO_SCLN_END      , KC_NO         , */
  /*         KC_NO            , KC_PERC , KC_ASTR  , KC_CIRC        , ST_MACRO_EXT_SEL , KC_NO          , KC_NO       , KC_NO   , KC_NO   , KC_NO         , LALT(KC_DOWN)          , KC_NO         , ST_MACRO_VIM_SEARCH , KC_RSHIFT , */
  /*                  KC_PIPE , KC_CAPS , MO(_APP) , TD(TD_ESC_F13) , KC_NO            , KC_TRANSPARENT , KC_RCTRL    , KC_RALT */

  /*  ), */
  /* // Numbers */
  /* [_NUML] = LAYOUT( */
  /*         KC_0           , KC_1       , KC_2  , KC_3  , KC_4  , KC_5        , KC_LCTRL , KC_LCTRL  , KC_LALT , KC_LGUI , ST_MACRO_30 , KC_ENTER  , */
  /*         KC_DELETE      , KC_6       , KC_7  , KC_8  , KC_9  , KC_0        , KC_NO    , KC_NO     , KC_NO   , KC_NO   , KC_NO       , KC_ENTER  , */
  /*         KC_LSHIFT      , LCTL(KC_B) , KC_NO , KC_NO , KC_NO , ST_MACRO_31 , KC_NO    , KC_NO     , KC_NO   , KC_NO   , KC_NO       , KC_RSHIFT , */
  /*         LCTL(KC_ENTER) , KC_NO      , KC_NO , KC_NO , KC_NO , KC_CAPSLOCK , KC_NO    , MO(_FUNL) , KC_NO   , KC_NO   , KC_NO       , KC_NO)    , */

  [_APP] = LAYOUT(
    KC_F12        , KC_F1      , KC_F2      , KC_F3                                , KC_F4       , KC_F5        /* ,            , */     , KC_F6        , KC_F7    , KC_F8         , KC_F9       , KC_F10                 , KC_F11        ,
    LCTL(KC_F4)                , LALT(LCTL(LSFT(KC_Q))) , LALT(LCTL(LSFT(KC_W))) , LALT(LCTL(LSFT(KC_E))) , LALT(LCTL(LSFT(KC_R))) , LCTL(LGUI(KC_5))         /* ,              , */            , LALT(LCTL(LSFT(KC_Y))) , LCTL(LGUI(KC_8))       , LCTL(LGUI(KC_1))     , LCTL(LGUI(KC_5))                  , LALT(LCTL(LSFT(KC_P))) , LGUI(KC_UP)   ,
    LGUI(KC_TAB)               , RCTL(KC_ESC)/*Windows_key*/            , LCTL(LGUI(KC_8))       , LALT(LCTL(LSFT(KC_D))) , LCTL(LGUI(KC_7))       , LALT(LCTL(LSFT(KC_G)))   /* ,              , */            , LCTL(LGUI(KC_4))       , LALT(LCTL(LSFT(KC_J))) , LCTL(LGUI(KC_3))     , RGUI(KC_SPACE)/*Change_language*/ , LCTL(LGUI(KC_2))       , LGUI(KC_DOWN) ,
    LALT(LCTL(KC_PSCREEN))     , OSM(MOD_RGUI) , LCTL(LGUI(KC_9))       , LALT(LCTL(LSFT(KC_C))) , LALT(LCTL(LSFT(KC_V))) , LALT(LCTL(LSFT(KC_B)))      , LALT(KC_F4)      , LCTL(KC_F4) , LALT(LCTL(LSFT(KC_N))) , LCTL(LGUI(KC_6))       , LALT(KC_TAB)         , LALT(KC_GRAVE)                    , LCTL(LGUI(KC_0))       , KC_PSCREEN    ,
                            /* ,                        ,                        , */ LALT(KC_MINUS)      , LALT(KC_EQUAL)         , KC_TRANSPARENT              , LGUI(KC_TAB) , KC_NO         , KC_TRANSPARENT         , KC_AUDIO_VOL_UP      , KC_AUDIO_VOL_DOWN /* ,                                   , */
  ),
  // Debug
  // RALT(KC_X) on the right control is to switch xdebug on browsers. I always forget the shortcup. Let it be on the debug layer
  // RALT(LSFT(KC_X)) is for Firefox
  [_DBGL] = LAYOUT(
          KC_NO , KC_NO , KC_NO , KC_NO     , KC_NO , KC_NO  /*      ,             , */    , ST_MACRO_14 , KC_NO                , KC_F11             , KC_F10 , KC_NO , KC_NO ,
          KC_NO , KC_NO , KC_NO , KC_NO     , KC_NO , KC_NO  /*      ,             , */    , ST_MACRO_14 , KC_NO                , KC_F11             , KC_F10 , KC_NO , KC_NO ,
          KC_NO , KC_NO , KC_NO , KC_NO     , KC_NO , KC_NO     /*   ,             , */    , KC_LEFT     , KC_DOWN            , KC_UP            , KC_RIGHT , KC_NO , KC_NO ,
          KC_NO , KC_NO , KC_NO , KC_NO     , KC_NO , KC_NO          , TO(_QWERTY) , KC_NO , KC_NO       , KC_NO                , KC_NO              , KC_NO  , KC_NO , KC_F8 ,
        /*      ,       ,       , */  KC_NO , KC_NO , KC_TRANSPARENT , KC_LSHIFT   , KC_F8 , KC_NO       , ST_MACRO_START_DEBUG , RALT(LSFT(KC_X)) /* ,        , */
  )
};

/* int RGB_current_mode; */

// Setting ADJUST layer RGB back to default
/* void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) { */
/*   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) { */
/*     layer_on(layer3); */
/*   } else { */
/*     layer_off(layer3); */
/*   } */
/* } */

void matrix_init_user(void) {
    /* #ifdef RGBLIGHT_ENABLE */
    /*   RGB_current_mode = rgblight_config.mode; */
    /* #endif */
}

/* //SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk */
/* #ifdef OLED_DRIVER_ENABLE */

/* oled_rotation_t oled_init_user(oled_rotation_t rotation) { */
/*   if (!is_keyboard_master()) */
/*     return OLED_ROTATION_180;  // flips the display 180 degrees if offhand */
/*   return rotation; */
/* } */

/* // When you add source files to SRC in rules.mk, you can use functions. */
/* const char *read_layer_state(void); */
/* const char *read_logo(void); */
/* void set_keylog(uint16_t keycode, keyrecord_t *record); */
/* const char *read_keylog(void); */
/* const char *read_keylogs(void); */

/* // const char *read_mode_icon(bool swap); */
/* // const char *read_host_led_state(void); */
/* // void set_timelog(void); */
/* // const char *read_timelog(void); */

/* void oled_task_user(void) { */
/*   if (is_keyboard_master()) { */
/*     // If you want to change the display of OLED, you need to change here */
/*     oled_write_ln(read_layer_state(), false); */
/*     oled_write_ln(read_keylog(), false); */
/*     oled_write_ln(read_keylogs(), false); */
/*     //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false); */
/*     //oled_write_ln(read_host_led_state(), false); */
/*     //oled_write_ln(read_timelog(), false); */
/*   } else { */
/*     oled_write(read_logo(), false); */
/*   } */
/* } */
/* #endif // OLED_DRIVER_ENABLE */

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*   if (record->event.pressed) { */
/* #ifdef OLED_DRIVER_ENABLE */
/*     set_keylog(keycode, record); */
/* #endif */
/*     // set_timelog(); */
/*   } */

/*   switch (keycode) { */
/*     case QWERTY: */
/*       if (record->event.pressed) { */
/*         set_single_persistent_default_layer(_QWERTY); */
/*       } */
/*       return false; */
/*       break; */
/*     case LOWER: */
/*       if (record->event.pressed) { */
/*         layer_on(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case RAISE: */
/*       if (record->event.pressed) { */
/*         layer_on(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*       break; */
/*     case ADJUST: */
/*         if (record->event.pressed) { */
/*           layer_on(_ADJUST); */
/*         } else { */
/*           layer_off(_ADJUST); */
/*         } */
/*         return false; */
/*         break; */
/*   } */
/*   return true; */
/* } */

/* #ifdef ENCODER_ENABLE */
/* void encoder_update_user(uint8_t index, bool clockwise) { */
/*     if (index == 0) { */
/*         switch (biton32(layer_state)) { */
/*             case _QWERTY: */
/*                 // Move whole words. Hold shift to select while moving. */
/*                 if (clockwise) { */
/*                     tap_code16(C(KC_RGHT)); */
/*                 } else { */
/*                     tap_code16(C(KC_LEFT)); */
/*                 } */
/*                 break; */
/*             default: */
/*                 // History scrubbing. For Adobe products, hold shift while moving */
/*                 // backward to go forward instead. */
/*                 if (clockwise) { */
/*                     tap_code16(C(KC_Z)); */
/*                 } else { */
/*                     tap_code16(C(KC_Y)); */
/*                 } */
/*                 break; */
/*         } */
/*     } else if (index == 1) { */
/*         switch (biton32(layer_state)) { */
/*             case _QWERTY: */
/*                 // Scrolling with PageUp and PgDn. */
/*                 if (clockwise) { */
/*                     tap_code(KC_PGDN); */
/*                 } else { */
/*                     tap_code(KC_PGUP); */
/*                 } */
/*                 break; */
/*             default: */
/*                 // Volume control. */
/*                 if (clockwise) { */
/*                     tap_code(KC_VOLU); */
/*                 } else { */
/*                     tap_code(KC_VOLD); */
/*                 } */
/*                 break; */
/*         } */
/*     } */
/* } */
/* #endif */



// Copy from planck

// Must be declared outsice the function, because otherwise they will be reset every time key is pressed
// l and r bracket_key_timer are for checking how long the ctrl and alt keys are held
uint16_t lbracket_key_timer;
uint16_t rbracket_key_timer;
uint16_t lbracket_key_first_timer;
int lbracket_counter = 0;
bool rctr_pressed = false;
bool ralt_pressed = false;
bool is_char_pressed_while_rctr_pressed = false;
bool is_char_pressed_while_ralt_pressed = false;
uint16_t minus_key_timer;
uint16_t scln_key_timer;
uint16_t plus_key_timer;
uint16_t dot_key_timer;
uint16_t grave_key_timer;
uint16_t quot_key_timer;
uint16_t lcbr_key_timer;
uint16_t lprn_key_timer;
uint16_t labk_key_timer;
uint16_t lbrk_key_timer;
uint16_t rcbr_key_timer;
uint16_t rprn_key_timer;
uint16_t rabk_key_timer;
uint16_t rbrk_key_timer;




/* uint16_t minus_key_first_timer; */

uint16_t last_keys[16];

bool cant_ac_enabled = false;
bool dont_ac_enabled = false;
bool corr_ac_enabled = false;
bool arr_ac_enabled = false;
bool com_ac_enabled = false;
bool con_ac_enabled = false;
bool int_ac_enabled = false;
bool ins_ac_enabled = false;
bool mus_ac_enabled = false;
bool ill_ac_enabled = false;
bool nii_ac_enabled = false;
bool mf_ac_enabled = false;
bool mf_c_ac_enabled = false;
bool cs_ac_enabled = false;
bool cs_c_ac_enabled = false;
bool cs_c_ds_enabled = false;
bool mm_ac_enabled = false;
bool hg_ac_enabled = false;
bool m_ac_enabled = false;
bool g_ac_enabled = false;

bool ac_is_something_enabled = false;

void add_last_key(uint16_t keycode) {
    int i, n;
    n = 8;
    // shift right and enter the last key at the beginning
    /* uint16_t temp; */
    /* temp = last_keys_carousel[n - 1]; */
    for (i = n - 1; i > 0; i--) {
        last_keys[i] = last_keys[i - 1];
    }
    last_keys[0] = keycode;
}

void clear_last_keys(void) {
    memset(last_keys, 0, sizeof(last_keys));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* if (record->event.pressed) { */
/* #ifdef OLED_DRIVER_ENABLE */
  /*   set_keylog(keycode, record); */
/* #endif */
  /*   // set_timelog(); */
  /* } */
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      /* return false; */
      break;
    /* case LOWER: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_LOWER); */
    /*     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
    /*   } else { */
    /*     layer_off(_LOWER); */
    /*     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
    /*   } */
    /*   /1* return false; *1/ */
    /*   break; */
    /* case RAISE: */
    /*   if (record->event.pressed) { */
    /*     layer_on(_RAISE); */
    /*     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
    /*   } else { */
    /*     layer_off(_RAISE); */
    /*     update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
    /*   } */
    /*   /1* return false; *1/ */
    /*   break; */
    /* case ADJUST: */
    /*     if (record->event.pressed) { */
    /*       layer_on(_ADJUST); */
    /*     } else { */
    /*       layer_off(_ADJUST); */
    /*     } */
    /*     /1* return false; *1/ */
    /*     break; */

  }

switch (keycode) {
    // set_timelog();
    // IDEA adds > after $this- and this macro makes it $this->>
    /* case ST_MACRO_MINUS: */
    /* if (record->event.pressed) { */
    /*     register_code(KC_MINUS); */
    /* } else { */
    /*     unregister_code(KC_MINUS); */
    /*     if (timer_elapsed(minus_key_timer) < TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0) { */
    /*         tap_code(KC_BSPACE); */
    /*         tap_code16(KC_RABK); */
    /*     } else { */
    /*         minus_key_timer = timer_read(); */
    /*     } */
    /* } */
    /* break; */
    case ST_MACRO_PLUS:
    if (record->event.pressed) {
        register_code16(KC_PLUS);
    } else {
        unregister_code16(KC_PLUS);
        add_last_key(KC_PLUS);
        if (timer_elapsed(plus_key_timer) < 2 * TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0 && last_keys[0] == KC_PLUS) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
        } else {
            plus_key_timer = timer_read();
        }
    }
    break;
    case ST_MACRO_LCBR:
    if (record->event.pressed) {
        register_code16(KC_LCBR);
    } else {
        unregister_code16(KC_LCBR);
        add_last_key(KC_LCBR);
        lcbr_key_timer = timer_read();
    }
    break;
    case ST_MACRO_RCBR:
    if (record->event.pressed) {
        register_code16(KC_RCBR);
    } else {
        unregister_code16(KC_RCBR);
        add_last_key(KC_RCBR);
        if (timer_elapsed(lcbr_key_timer) < 5 * TAPPING_TERM && last_keys[0] == KC_RCBR && last_keys[1] == KC_LCBR) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
            rcbr_key_timer = timer_read();
        }
    }
    break;
    case ST_MACRO_LPRN:
    if (record->event.pressed) {
        register_code16(KC_LPRN);
    } else {
        unregister_code16(KC_LPRN);
        add_last_key(KC_LPRN);
        lprn_key_timer = timer_read();
    }
    break;
    case ST_MACRO_RPRN:
    if (record->event.pressed) {
        register_code16(KC_RPRN);
    } else {
        unregister_code16(KC_RPRN);
        add_last_key(KC_RPRN);
        if (timer_elapsed(lprn_key_timer) < 5 * TAPPING_TERM && last_keys[0] == KC_RPRN && last_keys[1] == KC_LPRN) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
            rprn_key_timer = timer_read();
        }
    }
    break;
    case ST_MACRO_LABK:
    if (record->event.pressed) {
        register_code16(KC_LABK);
    } else {
        unregister_code16(KC_LABK);
        add_last_key(KC_LABK);
        labk_key_timer = timer_read();
    }
    break;
    case ST_MACRO_RABK:
    if (record->event.pressed) {
        register_code16(KC_RABK);
    } else {
        unregister_code16(KC_RABK);
        add_last_key(KC_RABK);
        if (timer_elapsed(labk_key_timer) < 5 * TAPPING_TERM && last_keys[0] == KC_RABK && last_keys[1] == KC_LABK) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
            rabk_key_timer = timer_read();
        }
    }
    break;
    case ST_MACRO_LBRK:
    if (record->event.pressed) {
        register_code16(KC_LBRC);
    } else {
        unregister_code16(KC_LBRC);
        add_last_key(KC_LBRC);
        lbrk_key_timer = timer_read();
    }
    break;
    case ST_MACRO_RBRK:
    if (record->event.pressed) {
        register_code16(KC_RBRC);
    } else {
        unregister_code16(KC_RBRC);
        add_last_key(KC_RBRC);
        if (timer_elapsed(lbrk_key_timer) < 5 * TAPPING_TERM && last_keys[0] == KC_RBRC && last_keys[1] == KC_LBRC) {
            uint8_t current_mods = keyboard_report->mods;
            del_mods(keyboard_report->mods);
            // clear_mods();
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
            rbrk_key_timer = timer_read();
            add_mods(current_mods);
        }
    }
    break;
    case ST_MACRO_SCLN:
    // This is adding ; ad the end of the sequence (); {}; and so on, and after '';
    if (record->event.pressed) {
        register_code16(KC_SCLN);
    } else {
        unregister_code16(KC_SCLN);
        // atmp
        if (
                // Make sure shift os not pressed
            ((keyboard_report->mods & MOD_MASK_SHIFT) == 0) &&
            (
                // 2 sec and 3 for the ;
            (timer_elapsed(rcbr_key_timer) < 10 * TAPPING_TERM && timer_elapsed(lcbr_key_timer) < 15 * TAPPING_TERM && last_keys[1] == KC_RCBR && last_keys[0] == KC_LEFT) ||
            (timer_elapsed(rprn_key_timer) < 10 * TAPPING_TERM && timer_elapsed(lprn_key_timer) < 15 * TAPPING_TERM && last_keys[1] == KC_RPRN && last_keys[0] == KC_LEFT) ||
            (timer_elapsed(rabk_key_timer) < 10 * TAPPING_TERM && timer_elapsed(rabk_key_timer) < 15 * TAPPING_TERM && last_keys[1] == KC_RABK && last_keys[0] == KC_LEFT) ||
            (timer_elapsed(rbrk_key_timer) < 10 * TAPPING_TERM && timer_elapsed(rbrk_key_timer) < 15 * TAPPING_TERM && last_keys[1] == KC_RBRC && last_keys[0] == KC_LEFT) ||
            (timer_elapsed(quot_key_timer) < 15 * TAPPING_TERM && last_keys[1] == KC_QUOTE && last_keys[0] == KC_LEFT)
            )
        ) {
            tap_code(KC_BSPACE);
            tap_code(KC_RIGHT);
            tap_code(KC_SCLN);
            tap_code(KC_LEFT);
            tap_code(KC_LEFT);
            clear_last_keys();
        }
    }
    break;
    case ST_MACRO_SCLN_END:
        if (!record->event.pressed) {
            // Add ; at the end of the line and return back.
            // Works in vim only - normal and insert mode.
            SEND_STRING(SS_LCTRL(SS_TAP(X_LBRACKET)));
            SEND_STRING("m'A;");
            SEND_STRING(SS_LCTRL(SS_TAP(X_LBRACKET)));
            SEND_STRING(SS_DELAY(100) "`'a");
            /* SEND_STRING("''a"); */
        }
        break;
    case ST_MACRO_DOT:
    if (record->event.pressed) {
        register_code(KC_DOT);
    } else {
        unregister_code(KC_DOT);
        // tap_code(last_keys[0]);
        // tap_code(last_keys[1]);
        // Check if the last 2 chars are . If yes, skip this to allow ...
        // if ((keyboard_report->mods & MOD_MASK_SHIFT) == 0 && last_keys[1] != KC_DOT && last_keys[0] == KC_DOT) {
        if (timer_elapsed(dot_key_timer) < 3 * TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0 && last_keys[1] != KC_DOT && last_keys[0] == KC_DOT) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
        } else {
            if (timer_elapsed(dot_key_timer) < 6 * TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0 && last_keys[1] == KC_DOT && last_keys[0] == KC_LEFT) {
                // This is a third . for a short time. Must be ... As after the second . we moved left, now move right to compensate
                tap_code(KC_RIGHT);
                add_last_key(KC_RIGHT);
            } else {
                dot_key_timer = timer_read();
            }
        }
        add_last_key(KC_DOT);
    }
    break;
    case ST_MACRO_QUOT:
    if (record->event.pressed) {
        register_code(KC_QUOT);
    } else {
        unregister_code(KC_QUOT);
        add_last_key(KC_QUOTE);
        if (timer_elapsed(quot_key_timer) < 3 * TAPPING_TERM && last_keys[0] == KC_QUOTE) {
            if ((keyboard_report->mods & MOD_MASK_SHIFT) == 0) {
                // Single quotes
                tap_code(KC_LEFT);
                add_last_key(KC_LEFT);
            } else{
                // Dougle quotes
                uint8_t current_mods = keyboard_report->mods;
                // clear_mods();
                del_mods(keyboard_report->mods);
                /* clear_macro_mods(); */
                tap_code(KC_LEFT);
                add_last_key(KC_LEFT);
                add_mods(current_mods);
             }
        } else {
            quot_key_timer = timer_read();
        }
    }
    break;
    // Works for single quote only
    /* case ST_MACRO_QUOT: */
    /* if (record->event.pressed) { */
    /*     register_code(KC_QUOT); */
    /* } else { */
    /*     unregister_code(KC_QUOT); */
    /*     if (timer_elapsed(quot_key_timer) < TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0) { */
    /*         tap_code(KC_LEFT); */
    /*     } else { */
    /*         quot_key_timer = timer_read(); */
    /*     } */
    /* } */
    /* break; */
    case ST_MACRO_GRAVE:
    if (record->event.pressed) {
        register_code(KC_GRAVE);
    } else {
        unregister_code(KC_GRAVE);
        add_last_key(KC_GRAVE);
        if (timer_elapsed(grave_key_timer) < 3 * TAPPING_TERM && (keyboard_report->mods & MOD_MASK_SHIFT) == 0 && last_keys[1] == KC_GRAVE) {
            tap_code(KC_LEFT);
            add_last_key(KC_LEFT);
        } else {
            grave_key_timer = timer_read();
        }
    }
    break;
    case ST_MACRO_START_DEBUG:
    if (record->event.pressed) {
      /* layer_on(_QWERTY); */
      // Open the Idea terminal
      SEND_STRING(SS_LALT(SS_TAP(X_F12)));
      // Wait a little to init PowerShell
      SEND_STRING(SS_DELAY(2000)"debugm" SS_DELAY(100) SS_TAP(X_ENTER));
      SEND_STRING(SS_DELAY(200) SS_TAP(X_ESC) SS_DELAY(500));
      // Start the debugger - will have to hit enter once you confirm that the correct debugger is selected
      tap_code(KC_F8);
      /* layer_clear(); */
      /* layer_on(_LOWER); */

    }
    break;
    /* case ST_MACRO_CAPSLOCK: */
    /* if (record->event.pressed) { */
    /*     tap_code(KC_CAPSLOCK); */
    /*     // beep */
    /*     /1* PLAY_SONG(my_leader_start); *1/ */
    /* } */
    /* break; */
    // You may do it for the rest of the brackets
    // Or even overcomplicate it by detecting ] the second time
    /* case ST_MACRO_CTRL_OR_BRACKET: */
    /* if (record->event.pressed) { */
    /*     lbracket_key_timer = timer_read(); */
    /*     register_code(KC_RCTL); */
    /*     rctr_pressed = true; */
    /* } else { */
    /*   //This will release the ctrl so that it has no effect on the next keys */
    /*     unregister_code(KC_RCTL); */
    /*     if (!is_char_pressed_while_rctr_pressed && timer_elapsed(lbracket_key_timer) < TAPPING_TERM) { */
    /*       if (lbracket_counter == 1 && timer_elapsed(lbracket_key_first_timer) < 3 * TAPPING_TERM) { */
    /*         SEND_STRING(SS_TAP(X_RBRACKET) SS_DELAY(100) SS_TAP(X_LEFT)); */
    /*         add_last_key(KC_RBRACKET); */
    /*         add_last_key(KC_LEFT); */

    /*         lbracket_counter = 0; */
    /*         /1* SEND_STRING(SS_LSFT(SS_TAP(X_8))); *1/ */
    /*       } else { */
    /*         SEND_STRING(SS_TAP(X_LBRACKET)); */
    /*         add_last_key(KC_LBRACKET); */
    /*         lbracket_key_first_timer = timer_read(); */
    /*         lbracket_counter++; */
    /*         lbrk_key_timer = timer_read(); */
    /*       } */
    /*       // probably this will mess up the double tap */
    /*       /1* is_char_pressed_while_rctr_pressed = true; *1/ */
    /*   } else { */
    /*       is_char_pressed_while_rctr_pressed = false; */
    /*   } */
    /*   rctr_pressed = false; */
    /* } */
    /* break; */
    /* case ST_MACRO_RALT_OR_RBRACKET: */
    /* if (record->event.pressed) { */
    /*     rbracket_key_timer = timer_read(); */
    /*     register_code(KC_RALT); */
    /*     ralt_pressed = true; */
    /* } else { */
    /*     if (!is_char_pressed_while_ralt_pressed && timer_elapsed(rbracket_key_timer) < TAPPING_TERM) { */
    /*         /1* clear_mods(); *1/ */
    /*         unregister_code(KC_RALT); */
    /*         // !!! Very important. If I do not press and release the alt key again, it stays in pressed mode */
    /*         // I think that it is Windows OS problem - leaving the alt toggled on after releasing it */
    /*         // Now to toggle it, press it for more than TAPPING_TERM */
    /*         register_code(KC_RALT); */
    /*         unregister_code(KC_RALT); */
    /*         /1* unregister_code(KC_RALT); *1/ */

    /*         tap_code(KC_RBRACKET); */
    /*         add_last_key(KC_RBRACKET); */

    /*         if (timer_elapsed(lbrk_key_timer) < 3 * TAPPING_TERM) { */
    /*             tap_code(KC_LEFT); */
    /*             add_last_key(KC_LEFT); */
    /*         } */

    /*         rbrk_key_timer = timer_read(); */
    /*     } else { */
    /*         //This will release the alt so that it has no effect on the next keys */
    /*         unregister_code(KC_RALT); */
    /*         is_char_pressed_while_ralt_pressed = false; */
    /*     } */

    /*   ralt_pressed = false; */
    /* } */
    /* break; */
    case ST_MACRO_STRUCT:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_LBRACKET)) SS_DELAY(100) SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) "MTs" SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_T)));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_Q)));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_W)));

    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_E)));

    }
    break;
    case ST_MACRO_4:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_R)));

    }
    break;
    case ST_MACRO_5:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_T)));

    }
    break;
    case ST_MACRO_6:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_A)));

    }
    break;
    case ST_MACRO_7:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_S)));

    }
    break;
    /* case ST_MACRO_8: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_D))); */

    /* } */
    break;
    case ST_MACRO_9:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_F)));

    }
    break;
    case ST_MACRO_10:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_C)));

    }
    break;
    case ST_MACRO_11:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_V)));

    }
    break;
    /* case ST_MACRO_12: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_B))); */

    /* } */
    /* break; */
    /* case ST_MACRO_13: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_ENTER)); */

    /* } */
    /* break; */
    case ST_MACRO_14:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_F9)) SS_DELAY(100) SS_LALT(SS_TAP(X_SLASH)) SS_DELAY(100) SS_TAP(X_ENTER) SS_DELAY(100) SS_TAP(X_TAB));

    }
    break;
    case ST_MACRO_15:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_Y)));

    }
    break;
    case ST_MACRO_16:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_O)));

    }
    break;
    case ST_MACRO_VIM_SEARCH:
    if (record->event.pressed) {
      // Wait before the second slash, because ideavim (and vim) rewrites cnoremap %s/ %snomagic/ which messes up the rest of the macro
      /* SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(300) SS_LSFT(SS_TAP(X_5)) SS_DELAY(10) SS_TAP(X_S) SS_DELAY(10) SS_TAP(X_SLASH) SS_DELAY(500) SS_TAP(X_SLASH) "gc" SS_DELAY(10) SS_TAP(X_LEFT) SS_DELAY(10) SS_TAP(X_LEFT) SS_DELAY(10) SS_TAP(X_LEFT)); */
      // Did not work well on ideavim - was not recognized as command
      /* SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(300) SS_LSFT(SS_TAP(X_5)) SS_DELAY(100) "snomagic///gc" SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(100) SS_TAP(X_LEFT)); */
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(300) SS_LSFT(SS_TAP(X_5)) SS_DELAY(10) SS_TAP(X_S) SS_DELAY(10) SS_TAP(X_SLASH) SS_DELAY(200) "//gc" SS_DELAY(100) SS_TAP(X_LEFT) SS_DELAY(10) SS_TAP(X_LEFT) SS_DELAY(10) SS_TAP(X_LEFT)  SS_DELAY(10) SS_TAP(X_LEFT));
    }
    break;
    case ST_MACRO_PASTE_HISTORY:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(300) "YRShow" SS_TAP(X_ENTER));
    }
    break;
    case ST_SEMIM:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_LBRACKET))SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(300) "M");
    }
    break;
    case ST_MACRO_ARROW:
    if (record->event.pressed) {
      SEND_STRING("->");
    }
    break;
    case ST_MACRO_EQ_ARROW:
    if (record->event.pressed) {
      SEND_STRING("=>");
    }
    break;
    case ST_MACRO_EXT_SEL:
    if (record->event.pressed) {
      SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(200) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(30) SS_LSFT(SS_TAP(X_M)) SS_DELAY(30) SS_LSFT(SS_TAP(X_S)) SS_DELAY(30) SS_TAP(X_W) SS_DELAY(30) SS_TAP(X_ENTER));
    }
    break;
    case ST_MACRO_EM:
    // EasyMotion
    if (record->event.pressed) {
      SEND_STRING(" f");
      /* SEND_STRING(SS_TAP(X_SPACE) SS_DELAY(300) SS_TAP(X_F)); */
    }
    break;
    /* case ST_MACRO_18: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_GRAVE) SS_DELAY(100) SS_TAP(X_GRAVE) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_19: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_9)) SS_DELAY(100) SS_LSFT(SS_TAP(X_0)) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_20: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_EQUAL)) SS_DELAY(100) SS_LSFT(SS_TAP(X_EQUAL)) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_21: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_MINUS) SS_DELAY(100) SS_LSFT(SS_TAP(X_DOT))); */

    /* } */
    /* break; */
    /* case ST_MACRO_22: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_LBRACKET)) SS_DELAY(100) SS_LSFT(SS_TAP(X_RBRACKET)) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_23: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_EQUAL) SS_DELAY(100) SS_LSFT(SS_TAP(X_DOT))); */

    /* } */
    /* break; */
    /* case ST_MACRO_24: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_QUOTE) SS_DELAY(100) SS_TAP(X_QUOTE) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_25: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_COMMA)) SS_DELAY(100) SS_LSFT(SS_TAP(X_DOT)) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_26: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_DOT) SS_DELAY(100) SS_TAP(X_DOT) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_27: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_5)) SS_DELAY(100) SS_TAP(X_S) SS_DELAY(100) SS_TAP(X_SLASH)); */

    /* } */
    /* break; */
    /* case ST_MACRO_28: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_QUOTE)) SS_DELAY(100) SS_LSFT(SS_TAP(X_QUOTE)) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    /* case ST_MACRO_29: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_TAP(X_LBRACKET) SS_DELAY(100) SS_TAP(X_RBRACKET) SS_DELAY(100) SS_TAP(X_LEFT)); */

    /* } */
    /* break; */
    case ST_MACRO_30:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_1) SS_DELAY(100) SS_TAP(X_5) SS_DELAY(100) SS_TAP(X_0) SS_DELAY(100) SS_TAP(X_3));

    }
    break;
    case ST_MACRO_31:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_F9) SS_DELAY(100) SS_TAP(X_B));

    }
    break;
    /* case ST_MACRO_32: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_Q))); */

    /* } */
    /* break; */
    /* case ST_MACRO_33: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_W))); */

    /* } */
    /* break; */
    /* case ST_MACRO_34: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_E))); */

    /* } */
    /* break; */
    /* case ST_MACRO_35: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_R))); */

    /* } */
    /* break; */
    /* case ST_MACRO_36: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_T))); */

    /* } */
    /* break; */
    /* case ST_MACRO_37: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_Y))); */

    /* } */
    /* break; */
    /* case ST_MACRO_38: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_I))); */

    /* } */
    /* break; */
    /* case ST_MACRO_39: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_O))); */

    /* } */
    /* break; */
    /* case ST_MACRO_40: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_P))); */

    /* } */
    /* break; */
    /* case ST_MACRO_41: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_A))); */

    /* } */
    /* break; */
    /* case ST_MACRO_42: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_S))); */

    /* } */
    /* break; */
    /* case ST_MACRO_43: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_D))); */

    /* } */
    /* break; */
    /* case ST_MACRO_44: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_F))); */

    /* } */
    /* break; */
    /* case ST_MACRO_45: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_G))); */

    /* } */
    /* break; */
    /* case ST_MACRO_46: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_C))); */

    /* } */
    /* break; */
    /* case ST_MACRO_47: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_HOME)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_V))); */

    /* } */
    /* break; */
    /* case ST_MACRO_48: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_TAP(X_ENTER)); */

    /* } */
    /* break; */
    /* case ST_MACRO_49: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_5)) SS_DELAY(100) SS_TAP(X_S) SS_DELAY(100) SS_TAP(X_SLASH)); */

    /* } */
    /* break; */
    /* case ST_MACRO_50: */
    /* if (record->event.pressed) { */
    /*   SEND_STRING(SS_LSFT(SS_TAP(X_SCOLON)) SS_DELAY(100) SS_LSFT(SS_TAP(X_M)) SS_DELAY(100) SS_LSFT(SS_TAP(X_T))); */

    /* } */
    /* break; */
    case KC_Q:
    case KC_W:
    case KC_E:
    case KC_R:
    case KC_T:
    case KC_Y:
    case KC_U:
    case KC_I:
    case KC_O:
    case KC_P:
    case KC_A:
    case KC_S:
    case KC_D:
    case KC_F:
    case KC_G:
    case KC_H:
    case KC_J:
    case KC_K:
    case KC_L:
    case KC_Z:
    case KC_X:
    case KC_C:
    case KC_V:
    case KC_B:
    case KC_N:
    case KC_M:
    case LSFT(KC_Q):
    case LSFT(KC_W):
    case LSFT(KC_E):
    case LSFT(KC_R):
    case LSFT(KC_T):
    case LSFT(KC_Y):
    case LSFT(KC_U):
    case LSFT(KC_I):
    case LSFT(KC_O):
    case LSFT(KC_P):
    case LSFT(KC_A):
    case LSFT(KC_S):
    case LSFT(KC_D):
    case LSFT(KC_F):
    case LSFT(KC_G):
    case LSFT(KC_H):
    case LSFT(KC_J):
    case LSFT(KC_K):
    case LSFT(KC_L):
    case LSFT(KC_Z):
    case LSFT(KC_X):
    case LSFT(KC_C):
    case LSFT(KC_V):
    case LSFT(KC_B):
    case LSFT(KC_N):
    case LSFT(KC_M):
    case KC_1:
    case KC_2:
    case KC_3:
    case KC_4:
    case KC_5:
    case KC_6:
    case KC_7:
    case KC_8:
    case KC_9:
    case KC_0:
    case KC_ENTER:
    /* case KC_ESCAPE: */
    case KC_BSPACE:
    case KC_TAB:
    case KC_SPACE:
    case KC_MINUS:
    case KC_EQUAL:
    case KC_LBRACKET:
    case KC_RBRACKET:
    case KC_BSLASH:
    case KC_NONUS_HASH:
    case KC_SCOLON:
    case KC_QUOTE:
    case KC_GRAVE:
    case KC_COMMA:
    case KC_DOT:
    case KC_SLASH:
    case KC_NONUS_BSLASH:
    case KC_TILDE:
    case KC_EXCLAIM:
    case KC_AT:
    case KC_HASH:
    case KC_DOLLAR:
    case KC_PERCENT:
    case KC_CIRCUMFLEX:
    case KC_AMPERSAND:
    case KC_ASTERISK:
    case KC_LEFT_PAREN:
    case KC_RIGHT_PAREN:
    case KC_UNDERSCORE:
    case KC_PLUS:
    case KC_LEFT_CURLY_BRACE:
    case KC_RIGHT_CURLY_BRACE:
    case KC_PIPE:
    case KC_COLON:
    case KC_DOUBLE_QUOTE:
    case KC_LEFT_ANGLE_BRACKET:
    case KC_RIGHT_ANGLE_BRACKET:
    case KC_QUESTION:
      if (!record->event.pressed) {
          int i, n;
          n = 8;
          // If backspace, sift to the left
          if (keycode == KC_BSPACE) {
              for (i = 0; i < n - 1; i++) {
                  last_keys[i] = last_keys[i + 1];
              }
              last_keys[n - 1] = 0;
          } else {
              // shift right and enter the last key at the beginning
              /* uint16_t temp; */
              /* temp = last_keys_carousel[n - 1]; */
              for (i = n - 1; i > 0; i--) {
                  last_keys[i] = last_keys[i - 1];
              }
              last_keys[0] = keycode;
          }

          // The letters are reversed
          // !!! Have in mind that the LSFT(KC_KEYCODE) does not work at all, but I'll leave this mess for later fixing

          /* bool corr_ac_enabled = false; */
          if ((last_keys[3] == KC_C && last_keys[2] == KC_O && last_keys[1] == KC_R && last_keys[0] == KC_R) || (last_keys[3] == LSFT(KC_C) && last_keys[2] == KC_O && last_keys[1] == KC_R && last_keys[0] == KC_R)) {
              corr_ac_enabled = true;
          /* bool cant_ac_enabled = false; */
          } else if ((last_keys[3] == KC_C && last_keys[2] == KC_A && last_keys[1] == KC_N && last_keys[0] == KC_T) || (last_keys[3] == LSFT(KC_C) && last_keys[2] == KC_A && last_keys[1] == KC_N && last_keys[0] == KC_T) || (last_keys[3] == LSFT(KC_C) && last_keys[2] == KC_A && last_keys[1] == KC_N && last_keys[0] == LSFT(KC_T))) {
              cant_ac_enabled = true;
          } else if ((last_keys[3] == KC_D && last_keys[2] == KC_O && last_keys[1] == KC_N && last_keys[0] == KC_T) || (last_keys[3] == LSFT(KC_D) && last_keys[2] == KC_O && last_keys[1] == KC_N && last_keys[0] == KC_T) || (last_keys[3] == LSFT(KC_D) && last_keys[2] == KC_O && last_keys[1] == KC_N && last_keys[0] == LSFT(KC_T))) {
          /* bool dont_ac_enabled = false; */
              dont_ac_enabled = true;
          } else if ((last_keys[2] == KC_I && last_keys[1] == KC_L && last_keys[0] == KC_L) || (last_keys[2] == LSFT(KC_I) && last_keys[1] == KC_L && last_keys[0] == KC_L) || (last_keys[2] == LSFT(KC_I) && last_keys[1] == KC_L && last_keys[0] == LSFT(KC_L))) {
          /* bool ill_ac_enabled = false; */
              ill_ac_enabled = true;
          } else if ((last_keys[2] == KC_A && last_keys[1] == KC_R && last_keys[0] == KC_R) || (last_keys[2] == LSFT(KC_A) && last_keys[1] == KC_R && last_keys[0] == KC_R)) {
          /* bool arr_ac_enabled = false; */
              arr_ac_enabled = true;
          } else if ((last_keys[2] == KC_C && last_keys[1] == KC_O && last_keys[0] == KC_M) || (last_keys[2] == LSFT(KC_C) && last_keys[1] == KC_O && last_keys[0] == KC_M)) {
          /* bool com_ac_enabled = false; */
              com_ac_enabled = true;
          } else if ((last_keys[2] == KC_C && last_keys[1] == KC_O && last_keys[0] == KC_N) || (last_keys[2] == LSFT(KC_C) && last_keys[1] == KC_O && last_keys[0] == KC_N)) {
          /* bool con_ac_enabled = false; */
              con_ac_enabled = true;
          } else if ((last_keys[2] == KC_I && last_keys[1] == KC_N && last_keys[0] == KC_T) || (last_keys[2] == LSFT(KC_I) && last_keys[1] == KC_N && last_keys[0] == KC_T)) {
          /* bool int_ac_enabled = false; */
              int_ac_enabled = true;
          } else if ((last_keys[2] == KC_I && last_keys[1] == KC_N && last_keys[0] == KC_S) || (last_keys[2] == LSFT(KC_I) && last_keys[1] == KC_N && last_keys[0] == KC_S)) {
          /* bool ins_ac_enabled = false; */
              ins_ac_enabled = true;
          } else if (last_keys[2] == KC_N && last_keys[1] == KC_I && last_keys[0] == KC_I) {
          /* bool nii_ac_enabled = false; */
              nii_ac_enabled = true;
          } else if ((last_keys[2] == KC_M && last_keys[1] == KC_U && last_keys[0] == KC_S) || (last_keys[2] == LSFT(KC_M) && last_keys[1] == KC_U && last_keys[0] == KC_S)) {
          /* bool mus_ac_enabled = false; */
              mus_ac_enabled = true;
              // I could not do it in any way. Write MusicFiles only if MF is typed - make the trick below when actually typing
          /* } else if ((last_keys[1] == ((KC_LSFT | KC_RSFT) & KC_M) && last_keys[0] == KC_F) || (last_keys[1] == LSFT(KC_M) && last_keys[0] == LSFT(KC_F))) { */
          /* } else if ((last_keys[1] == LSFT(KC_M) && last_keys[0] == KC_F) || (last_keys[1] == LSFT(KC_M) && last_keys[0] == LSFT(KC_F))) { */
          /* bool mf_c_ac_enabled  = false; */
              /* mf_c_ac_enabled = true; */
          } else if (last_keys[1] == KC_M  && last_keys[0] == KC_F) {
          /* bool mf_ac_enabled  = false; */
              mf_ac_enabled = true;
          } else if ((last_keys[1] == KC_M && last_keys[0] == KC_M) || (last_keys[1] == LSFT(KC_M) && last_keys[0] == KC_M) || (last_keys[1] == LSFT(KC_M) && last_keys[0] == LSFT(KC_M))) {
          /* bool mm_ac_enabled  = false; */
              mm_ac_enabled = true;
          } else if ((last_keys[1] == LSFT(KC_C) && last_keys[0] == KC_S) || (last_keys[1] == LSFT(KC_C) && last_keys[0] == LSFT(KC_S))) {
          /* bool cs_c_ac_enabled = false; */
              cs_c_ac_enabled = true;
          } else if (last_keys[1] == KC_C && last_keys[0] == KC_S) {
          /* bool cs_ac_enabled = false; */
              cs_ac_enabled = true;
          } else if ((last_keys[1] == KC_D && last_keys[0] == KC_S) || (last_keys[1] == LSFT(KC_D) && last_keys[0] == KC_S) || (last_keys[1] == LSFT(KC_D) && last_keys[0] == LSFT(KC_S))) {
          /* bool cs_c_ds_enabled = false; */
              cs_c_ds_enabled = true;
          } else if ((last_keys[1] == KC_H && last_keys[0] == KC_G) || (last_keys[1] == LSFT(KC_H) && last_keys[0] == LSFT(KC_G))) {
          /* bool hg_ac_enabled  = false; */
              hg_ac_enabled = true;
          } else if (last_keys[0] == KC_G || last_keys[0] == LSFT(KC_G)) {
          /* bool g_ac_enabled   = false; */
              g_ac_enabled = true;
          } else {
              dont_ac_enabled = false;
              cant_ac_enabled = false;
              corr_ac_enabled = false;
              arr_ac_enabled  = false;
              com_ac_enabled  = false;
              con_ac_enabled  = false;
              int_ac_enabled  = false;
              ins_ac_enabled  = false;
              mus_ac_enabled  = false;
              nii_ac_enabled  = false;
              ill_ac_enabled  = false;
              mf_ac_enabled   = false;
              mf_c_ac_enabled = false;
              cs_ac_enabled   = false;
              cs_c_ac_enabled = false;
              cs_c_ds_enabled = false;
              mm_ac_enabled   = false;
              hg_ac_enabled   = false;
              m_ac_enabled    = false;
              g_ac_enabled    = false;
          }
      }

      lbracket_counter = 0;
      if (rctr_pressed) {
          is_char_pressed_while_rctr_pressed = true;
      }

      if (ralt_pressed) {
          is_char_pressed_while_ralt_pressed = true;
      }
      break;
      // does not work, because blocks the when we return false to prevent F23 to be sent
      /* case LT(_SYMRL, KC_F23): */
      case KC_F23:
        ac_is_something_enabled = false;
        if (!record->event.pressed) {
            // It could happen that more than one autocomplete is enabled. For example:
            // hg will enable "Hi, Gerhard!" and "Gerhard"
            // The longer one should be checked first. So,
            // ORDER THESE BY ABBREVIATION LENGTH
          if (cant_ac_enabled == true) {
              tap_code(KC_BSPACE);
              SEND_STRING("'t ");
              ac_is_something_enabled = true;
          } else if (dont_ac_enabled == true) {
              tap_code(KC_BSPACE);
              SEND_STRING("'t ");
              ac_is_something_enabled = true;
          } else if (corr_ac_enabled == true) {
              SEND_STRING("espondence");
              ac_is_something_enabled = true;
          } else if (ill_ac_enabled == true) {
              tap_code(KC_BSPACE);
              tap_code(KC_BSPACE);
              tap_code(KC_BSPACE);
              SEND_STRING("I'll ");
              ac_is_something_enabled = true;
          } else if (arr_ac_enabled == true) {
              SEND_STRING("angement");
              ac_is_something_enabled = true;
          } else if (com_ac_enabled == true) {
              SEND_STRING("position");
              ac_is_something_enabled = true;
          } else if (con_ac_enabled == true) {
              SEND_STRING("tact");
              ac_is_something_enabled = true;
          } else if (int_ac_enabled == true) {
              SEND_STRING("erpretation");
              ac_is_something_enabled = true;
          } else if (ins_ac_enabled == true) {
              SEND_STRING("trument");
              ac_is_something_enabled = true;
          } else if (mus_ac_enabled == true) {
              SEND_STRING("icalion");
              ac_is_something_enabled = true;
          } else if (nii_ac_enabled == true) {
              tap_code(KC_BSPACE);
              SEND_STRING("kolayivanovivanov");
              ac_is_something_enabled = true;
              // I couldn't make it work
          /* } else if (mf_c_ac_enabled == true) { */
          /*     tap_code(KC_BSPACE); */
          /*     SEND_STRING("usicFile"); */
          /*     ac_is_something_enabled = true; */
          } else if (mf_ac_enabled == true) {
              // In this case mf, or Mf or MF is typed. Keep the capital letters
              tap_code(KC_LEFT);
              SEND_STRING("usic");
              tap_code(KC_RIGHT);
              SEND_STRING("ile");
              ac_is_something_enabled = true;
          } else if (mm_ac_enabled == true) {
              tap_code(KC_BSPACE);
              SEND_STRING("ember");
              ac_is_something_enabled = true;
          } else if (cs_c_ac_enabled == true) {
              SEND_STRING("lientSite");
              ac_is_something_enabled = true;
          } else if (cs_ac_enabled == true) {
              tap_code(KC_LEFT);
              SEND_STRING("lient");
              tap_code(KC_RIGHT);
              SEND_STRING("ite");
              ac_is_something_enabled = true;
          } else if (cs_c_ds_enabled == true) {
              tap_code(KC_BSPACE);
              tap_code(KC_BSPACE);
              SEND_STRING("DownloadStatistics");
              ac_is_something_enabled = true;
          } else if (hg_ac_enabled == true) {
              tap_code(KC_BSPACE);
              tap_code(KC_BSPACE);
              SEND_STRING("Hi, Gerhard!");
              ac_is_something_enabled = true;
          } else if (g_ac_enabled == true) {
              SEND_STRING("erhard");
              ac_is_something_enabled = true;
          }


          //atmp debug
          /* int i; */
          /* tap_code(KC_ENTER); */
          /* for (i = 0; i < 3; i++) { */
          /*     if (last_keys[i] > 0) { */
          /*         tap_code(last_keys[i]); */
          /*     } */
          /* } */
          //atmp end

          if (ac_is_something_enabled) {
              dont_ac_enabled = false;
              cant_ac_enabled = false;
              corr_ac_enabled = false;
              arr_ac_enabled  = false;
              com_ac_enabled  = false;
              con_ac_enabled  = false;
              int_ac_enabled  = false;
              ins_ac_enabled  = false;
              mus_ac_enabled  = false;
              nii_ac_enabled  = false;
              ill_ac_enabled = false;
              mf_ac_enabled   = false;
              mf_c_ac_enabled = false;
              cs_ac_enabled   = false;
              cs_c_ac_enabled = false;
              cs_c_ds_enabled = false;
              mm_ac_enabled   = false;
              hg_ac_enabled   = false;
              m_ac_enabled    = false;
              g_ac_enabled    = false;

              last_keys[0] = 0;
              last_keys[1] = 0;
              last_keys[2] = 0;
              last_keys[3] = 0;
              last_keys[4] = 0;
          }


          lbracket_counter = 0;
          if (rctr_pressed) {
              is_char_pressed_while_ralt_pressed = true;
          }
          if (ralt_pressed) {
              is_char_pressed_while_ralt_pressed = true;
          }
        }

      return false;
      break;

    default:
    // Some other key is pressed.
    // If this works, you have to make it 0 in all above macros, but not only in ordinary keys
      lbracket_counter = 0;
      if (rctr_pressed) {
          is_char_pressed_while_ralt_pressed = true;
      }
      if (ralt_pressed) {
          is_char_pressed_while_ralt_pressed = true;
      }

      // This simple code works
      /* if (keycode == KC_C) { */
      /*     c_autocomplete_enabled = true; */
      /* } */
      /* if (c_autocomplete_enabled == true && keycode == KC_SCOLON) { */
      /*     SEND_STRING("omposition"); */
      /* } */
      /* if (keycode != KC_C) { */
      /*     c_autocomplete_enabled = false; */
      /* } */


}
return true;
}

// Chaning layer sends the proper F keys to warn
// Not good idea, because AutoHotkey did not always caught the F keys and they ware typed a <F...> in vim. I use MO now anyway
/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     if (IS_LAYER_ON_STATE(state, _VIMIDEA)) { */
/*         tap_code(KC_F19); */
/*     } else if (IS_LAYER_ON_STATE(state, _APP)) { */
/*         tap_code(KC_F18); */
/*     } */
/*     /1* switch (get_highest_layer(state)) { *1/ */
/*     /1* /2* case _RAISE: *2/ *1/ */
/*     /1* /2*     rgblight_setrgb (0x00,  0x00, 0xFF); *2/ *1/ */
/*     /1* /2*     break; *2/ *1/ */
/*     /1* case _VIMIDEA: *1/ */
/*     /1*     tap_code(KC_F19); *1/ */
/*     /1*     break; *1/ */
/*     /1* case _APP: *1/ */
/*     /1*     tap_code(KC_F18); *1/ */
/*     /1*     break; *1/ */
/*     /1* /2* case _RAISE: *2/ *1/ */
/*     /1* /2*     tap_code(KC_F19); *2/ *1/ */
/*     /1* /2*     break; *2/ *1/ */
/*     /1* /2* default: //  for any other layers, or the default layer *2/ *1/ */
/*     /1* /2*     tap_code(KC_F17); *2/ *1/ */
/*     /1* /2*     break; *2/ *1/ */
/*     /1* } *1/ */
/*     /1* /2* return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); *2/ *1/ */
/*   return state; */
/* } */

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        /* case KC_ESCAPE: */
        /*     return 85; */
        /* case LT(_NUML,KC_ENTER): */
        /*     return 180; */
        // case TD(TD_DOT):
        //     return 180;
        /* case KC_QUOTE: */
        /* case KC_GRAVE: */
        /* case KC_SLASH: */
        // case TD(TD_QUOT):
        // case TD(TD_DQUOT):
        // case TD(TD_BQUOT):
        // case TD(TD_LBRACKET):
        // case TD(TD_LPRN):
        // case TD(TD_LCBR):
        // case TD(TD_LABK):
        /* case TD(TD_SLASH): */
        /* case TD(TD_SCOLON): */
            // return 280;
        case TD(TD_ESC_F13):
            return 350;
        // case OSM(MOD_RGUI):
        //     return 3000;
        /* case OSM(MOD_RCTL): */
        /*     return 3000; */
        /* case OSM(MOD_RALT): */
        /*     return 3000; */
        // case OSL(_NAV):
        //     return 1000;
        // case OSL(_VIMIDEA):
        //     return 2000;
        // case OSL(_APP):
        //     return 2000;
        // case OSL(_DBGL):
        //     return 2000;
        /* case LT(_NAV, KC_F13): */
        /*     return 150; */
        /* case OSL(_SHIFT): */
        /*     /1* return 300; *1/ */
        /*     return 230; */
        /* case MO(_LOWER): */
        /*     return 120; */
        default:
            return TAPPING_TERM;

    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // Allow or not permissive hold for the key
    // https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold
    switch (keycode) {
        case LT(_VIMIDEA, KC_ENTER):
        case LT(_VIMIDEA, KC_END):
            return true;
        default:
            return true;
    }
}
