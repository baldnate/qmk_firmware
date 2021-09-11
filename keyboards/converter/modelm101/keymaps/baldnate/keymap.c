/* Copyright 2019 iw0rm3r
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
  [0] = LAYOUT( /* Base layer */
    KC_ESC,           KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_PSCR, KC_SLCK, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
    KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,   KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
    KC_CAPS, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                 KC_P4,   KC_P5,   KC_P6,
    KC_LSFT, KC_NUBS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,            KC_UP,              KC_P1,   KC_P2,   KC_P3,   KC_PENT,
    KC_LCTL,          KC_LALT,                           KC_SPC,                                      KC_RALT,          KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT,   KC_P0,            KC_PDOT
  ),
};

const uint16_t hold_time = 1000;
uint16_t reset_keydown_timer;
void process_reset_hold(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    reset_keydown_timer = timer_read();
  } else {
    if (timer_elapsed(reset_keydown_timer) > hold_time) {
      reset_keyboard();
    } else {
      tap_code16(keycode);
    }
  }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case KC_PSCR: {
        process_reset_hold(KC_PSCR, record);
        return false;
      }
  }

  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

#define RGB_DEFAULT 0x00, 0x50, 0x00
void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    setrgb(RGB_DEFAULT, (LED_TYPE *)&led[2]);
  } else {
    sethsv(HSV_OFF, (LED_TYPE *)&led[2]);
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    setrgb(RGB_DEFAULT, (LED_TYPE *)&led[1]); 
  } else {
    sethsv(HSV_OFF, (LED_TYPE *)&led[1]);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    setrgb(RGB_DEFAULT, (LED_TYPE *)&led[0]);
  } else {
    sethsv(HSV_OFF, (LED_TYPE *)&led[0]);
  }

  rgblight_set();
}

void keyboard_post_init_user(void) {

}