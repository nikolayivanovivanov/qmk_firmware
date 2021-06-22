#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4



// I can't make it work per key. TAPPING_TERM applies all the time
#define ONESHOT_TIMEOUT 300

#define TAPPING_FORCE_HOLD
#define TAPPING_FORCE_HOLD_PER_KEY
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
// Usefull for dual keys when you fast tap and release
#define PERMISSIVE_HOLD
// hope that this disables this feature
/* #define ONESHOT_TAP_TOGGLE 15 */
#define COMBO_COUNT 4
// I think that this is the time between the first key press and the second one
// If it is too small, the combo will be ignored
#define COMBO_TERM 500
