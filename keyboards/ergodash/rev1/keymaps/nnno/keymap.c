#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty */
  [_QWERTY] = LAYOUT( \
    KC_ESC , KC_1,     KC_2,    KC_3,    KC_4,    KC_5,  _______,                         _______,   KC_6,    KC_7,     KC_8,   KC_9,    KC_0, KC_BSPC, \
    KC_ESC , KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,  _______,                         _______,   KC_Y,    KC_U,     KC_I,   KC_O,    KC_P, KC_BSLS, \
    KC_LCTL, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,  KC_EQL ,                         KC_MINS,   KC_H,    KC_J,     KC_K,   KC_L, KC_SCLN,  KC_ENT, \
    KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,   LOWER ,                          RAISE ,   KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
    KC_DOWN, KC_UP, KC_LALT, GUI_T(KC_LANG2),   KC_SPC,   LOWER , _______,       _______,  RAISE , KC_ENT,   GUI_T(KC_LANG1), KC_GRV, KC_QUOT, KC_RGHT  \
  ),
  /* Raise */
  [_RAISE] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
    KC_TAB , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PIPE, \
    _______, _______, _______, _______, _______, _______, KC_LBRC,                        KC_RBRC, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,  LOWER ,                         RAISE , _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,  LOWER , _______,      _______,  RAISE , KC_ENT,           KC_TILD, _______, _______, _______  \
  ),
  /* Lower */
  [_LOWER] = LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,                        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, \
    _______, _______, _______, _______, _______, _______, KC_LCBR,                        KC_RCBR, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, KC_DQT , \
    _______, _______, _______, _______, _______, _______,  LOWER ,                         RAISE , _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          KC_SPC,   LOWER , _______,      _______,  RAISE , KC_ENT,           KC_TILD, _______, _______, _______  \
  ),

  /* Adjust */
  [_ADJUST] = LAYOUT( \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
         print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
