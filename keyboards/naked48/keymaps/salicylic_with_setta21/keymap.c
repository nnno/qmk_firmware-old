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
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  SEND_SUM,
  SEND_AVERAGE,
  SEND_COUNTIF,
  SEND_MAX,
  SEND_MIN
};

// Fillers to make layering more clear
#define KC_LOWER LOWER
#define KC_RAISE RAISE
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

#define KC_JCLON KC_QUOT  // : and +
#define KC_JAT   KC_LBRC  // @ and `
#define KC_JHAT  KC_EQL   // ^ and ~
#define KC_JENUN KC_RO    // \ and _ (EN mark and UNder score)
#define KC_JENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define KC_JLBRC KC_RBRC  // [ and {
#define KC_JRBRC KC_BSLS  // ] and }
#define KC_JAMPR KC_CIRC  // &
#define KC_JQUES LSFT(KC_SLSH)  // ?
#define KC_JTILD LSFT(KC_EQL)  // ~
#define KC_JQUOT LSFT(KC_7)  // '
#define KC_JLPRN KC_ASTR  // (
#define KC_JRPRN KC_LPRN  // )
#define KC_JLCBR KC_RCBR  // {
#define KC_JRCBR KC_PIPE  // }
#define KC_JPIPE LSFT(KC_JYEN)  // |
#define KC_JASTR LSFT(KC_QUOT)  // *
#define KC_JEQL LSFT(KC_MINS)  // =
#define KC_JPLUS LSFT(KC_SCLN)  // +
#define KC_JDQUO LSFT(KC_2)  // "
#define KC_SF11 SFT_T(KC_F11)
#define KC_SF12 LCTL_T(KC_F12)
#define KC_LEN LT(_LOWER, KC_ENT)
#define KC_RSP LT(_RAISE, KC_SPC)
#define KC_NAD LT(_ADJUST, KC_NLCK)
#define KC_CAD LCA(KC_DEL)
#define KC_APSCR LALT(KC_PSCR)

#define KC_SSUM  SEND_SUM
#define KC_SAVE  SEND_AVERAGE
#define KC_SCOU  SEND_COUNTIF
#define KC_SMAX  SEND_MAX
#define KC_SMIN  SEND_MIN

#define KC_RPDO LT(_RAISE, KC_PDOT)
#define KC_LP0 LT(_LOWER, KC_P0)
#define KC_NAD LT(_ADJUST, KC_NLCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        TAB,     Q,     W,     E,     R,     T,                   Y,     U,     I,     O,     P, JLBRC,          LP0,    P1,    P4,    P7,   NAD,   ESC, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       LSFT,     A,     S,     D,     F,     G,                   H,     J,     K,     L,  MINS, JRBRC,                  P2,    P5,    P8,  PSLS,    F2, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      LCTRL,     Z,     X,     C,     V,     B,                   N,     M,  COMM,   DOT,  SLSH, JENUN,         RPDO,    P3,    P6,    P9,  PAST,  JEQL, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
              LEFT, RIGHT,  LGUI,  MHEN,   LEN,  BSPC,   DEL,   RSP,  HENK,  LALT,    UP,  DOWN,                       PENT,         PPLS,  PMNS,   DEL  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  ),


  [_LOWER] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        ESC,  EXLM, JQUES, JLBRC, JRBRC, JTILD,                   6,     7,     8,     9, JASTR,  SLSH,        LOWER, XXXXX,  LEFT, XXXXX, XXXXX,   ESC, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
      JQUOT,  HASH, JDQUO, JLPRN, JRPRN,   JAT,               XXXXX,     4,     5,     6, _____,  JEQL,                DOWN,   DOWN,    UP,  PSLS,   F2, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       JHAT,  PERC, JAMPR,  SCLN, JCLON, JPIPE,                   0,     1,     2,     3, JPLUS,   ENT,        RAISE, XXXXX, RIGHT, XXXXX,  PAST,  JEQL, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____,  ZKHK, LOWER, _____, _____, RAISE,     0,   DOT, _____, _____,                       PENT,         PPLS,  PMNS,   DEL  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  ),


  [_RAISE] = LAYOUT_With_Setta21_kc( \
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        ESC,     1,     2,     3,     4,     5,                   6, XXXXX,    UP, XXXXX,  PGUP,  BSPC,        LOWER,   F11,    F4,    F7,  SMIN,   ESC, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       SF11,    F1,    F2,    F3,    F4,    F5,               XXXXX,  LEFT,  DOWN, RIGHT,  LSFT,   ENT,                 F12,    F5,    F8,  SMAX,    F2, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       SF12,    F6,    F7,    F8,    F9,   F10,               XXXXX, XXXXX, XXXXX, XXXXX,  PGDN, XXXXX,        RAISE,    F3,    F6,    F9,  SCOU,  JEQL, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____, _____, LOWER, _____, _____, RAISE, _____, _____, _____, _____,                      JRPRN,         SSUM,  SAVE,   DEL  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
  ),


  [_ADJUST] = LAYOUT_With_Setta21_kc( /* Base */
  //,-----------------------------------------|             |-----------------------------------------|      |-----------------------------------------|
        ESC,     1,     2,     3,     4,     5,                   6,     7,     8,     9,     0,   DEL,        LOWER,  LVAD,  LHUD,  LSAD,ADJUST,  LTOG, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       SF11,    F1,    F2,    F3,    F4,    F5,                LTOG,  LMOD, XXXXX,   CAD, APSCR,  PSCR,                LVAI,  LHUI,  LSAI, XXXXX, _____, \
  //|------+------+------+------+------+------|             |------+------+------+------+------+------|      |------+------+------+------+------+------|
       SF12,    F6,    F7,    F8,    F9,   F10,                LVAD,  LVAI,  LHUD,  LHUI,  LSAD,  LSAI,        RAISE, XXXXX, XXXXX, XXXXX, XXXXX, _____, \
  //|------+------+------+------+------+------|------+------+------+------+------+------+------|             |-------------+-------------+------+------|
             _____, _____, _____, _____, LOWER, _____, _____, RAISE, _____, _____, _____, _____,                       LMOD,        _____, _____, _____  \
          //`----------------------------------------------------------------------------------|             |-----------------------------------------|
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
    case SEND_SUM:
      if (record->event.pressed) {
        SEND_STRING("_SUM*");
      }
      return false;
      break;
    case SEND_AVERAGE:
      if (record->event.pressed) {
        SEND_STRING("_AVERAGE*");
      }
      return false;
      break;
    case SEND_COUNTIF:
      if (record->event.pressed) {
        SEND_STRING("_COUNTIF*");
      }
      return false;
      break;
    case SEND_MAX:
      if (record->event.pressed) {
        SEND_STRING("_MAX*");
      }
      return false;
      break;
    case SEND_MIN:
      if (record->event.pressed) {
        SEND_STRING("_MIN*");
      }
      return false;
      break;
  }
  return true;
}
