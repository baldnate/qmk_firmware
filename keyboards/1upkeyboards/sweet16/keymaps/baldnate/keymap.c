#include QMK_KEYBOARD_H

uint16_t f9_reset_timer;

enum custom_keycodes {
  KC_F9_RESET = SAFE_RANGE
};

uint16_t copy_paste_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_ortho_4x4(
    KC_F9_RESET,  HYPR(KC_F10), HYPR(KC_F11), HYPR(KC_F12),
    HYPR(KC_F13), HYPR(KC_F14), HYPR(KC_F15), HYPR(KC_F16),
    HYPR(KC_F17), HYPR(KC_F18), HYPR(KC_F19), HYPR(KC_F20),
    HYPR(KC_F21), HYPR(KC_F22), HYPR(KC_F23), HYPR(KC_F24)
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F9_RESET: { // One key copy/paste
      if (record->event.pressed) {
          f9_reset_timer = timer_read();
      } else {
        if (timer_elapsed(f9_reset_timer) > 5000) {  // Hold 5 seconds+
          reset_keyboard();
        } else {  // Tap, paste
          tap_code16(HYPR(KC_F9));
        }
      } 
      return false;
    }
    default: {
      return true;
    }
  }
}