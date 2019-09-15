/* Copyright 2018 Salicylic_Acid
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _MOUSE 1
#define _BROWSER 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MOUSE,
  BROWSER,
  LOWER,
  RAISE,
  ADJUST
};

// Fillers to make layering more clear
#define KC_LOWER LOWER
#define KC_RAISE RAISE

#define KC_MOUSE MOUSE
#define KC_BROWSER BROWSER

#define KC_ADJUST ADJUST

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO

#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_SNUBS S(KC_NUBS)
#define KC_SNUHS S(KC_NUHS)

#define KC_RTAB LCTL(KC_TAB)
#define KC_LTAB LCTL(LSFT(KC_TAB))
#define KC_CTAB LCTL(KC_W)
#define KC_RETAB LCTL(LSFT(KC_T))

#define KC_TGMO TG(_MOUSE)
#define KC_TGBR TG(_BROWSER)
#define KC_BSAD LT(_ADJUST, KC_BSPC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_With_Nafuda_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
        TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,  BSPC,                TGMO,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
        ESC,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  SCLN,  QUOT,         BSAD,    UP,  TGBR, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH,   ENT,         LEFT,  DOWN, RIGHT, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
            ADJUST, LCTRL,  LALT,  LGUI, LOWER,   SPC,   SPC, RAISE,  LEFT,  DOWN,    UP, RIGHT  \
          //`----------------------------------------------------------------------------------|
  ),

  [_MOUSE] = LAYOUT_With_Nafuda_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
        TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,  BSPC,                TGMO,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
        ESC,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  SCLN,  QUOT,         BTN1,  MS_U,  BTN2, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH,   ENT,         MS_L,  MS_D,  MS_R, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
            ADJUST, LCTRL,  LALT,  LGUI, LOWER,   SPC,   SPC, RAISE,  LEFT,  DOWN,    UP, RIGHT  \
          //`----------------------------------------------------------------------------------|
  ),

  [_BROWSER] = LAYOUT_With_Nafuda_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
        TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P,  BSPC,                CTAB,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
        ESC,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  SCLN,  QUOT,        RETAB,  WH_U,  TGBR, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH,   ENT,         LTAB,  WH_D,  RTAB, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
            ADJUST, LCTRL,  LALT,  LGUI, LOWER,   SPC,   SPC, RAISE,  LEFT,  DOWN,    UP, RIGHT  \
          //`----------------------------------------------------------------------------------|
  ),

  [_LOWER] = LAYOUT_With_Nafuda_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
       TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                CIRC,  AMPR,  ASTR,  LPRN,  RPRN,   DEL,                TGMO,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
        DEL,    F1,    F2,    F3,    F4,    F5,                  F6,  UNDS,  PLUS,  LCBR,  RCBR,  PIPE,         BSAD,    UP,  TGBR, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
      _____,    F7,    F8,  F9,     F10,   F11,                 F12, SNUHS, SNUBS, _____, _____, _____,         LEFT,  DOWN, RIGHT,  \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
             _____, _____, _____, _____, _____, _____, _____, _____,  MNXT,  VOLD,  VOLU,  MPLY \
          //`----------------------------------------------------------------------------------|
  ),


  [_RAISE] = LAYOUT_With_Nafuda_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
       TILD,     1,     2,     3,     4,     5,                   6,     7,     8,     9,     0,   DEL,                TGMO,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
        DEL,    F1,    F2,    F3,    F4,    F5,                  F6,  MINS,   EQL,  LBRC,  RBRC,  BSLS,         BSAD,    UP,  TGBR, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
      _____,    F7,    F8,  F9,     F10,   F11,                 F12,  NUHS,  NUBS, _____, _____, _____,         LEFT,  DOWN, RIGHT,  \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
             _____, _____, _____, _____, _____, _____, _____, _____,  MNXT,  VOLD,  VOLU,  MPLY \
          //`----------------------------------------------------------------------------------|
  ),


  [_ADJUST] = LAYOUT_With_Nafuda_kc( /* Base */
  //,-----------------------------------------|             |-----------------------------------------|      |--------------------|
      _____,   RST, XXXXX, XXXXX, XXXXX, XXXXX,               XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, _____,                LVAD,        \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LTOG,  LMOD, XXXXX,   CAD, APSCR,  PSCR,       ADJUST,  LSAD,  LVAI, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                LVAD,  LVAI,  LHUD,  LHUI,  LSAD,  LSAI,         LMOD,  LTOG,  LSAI, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |--------------------|
             _____, _____, _____, _____, LOWER, _____, _____, RAISE, _____, _____, _____, _____ \
          //`----------------------------------------------------------------------------------|
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}
