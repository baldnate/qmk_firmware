#include "sweet16.h"

enum layers {
 numpad,
 emote,
 obs
};

enum custom_keycodes {
  KC_DIV_RESET = SAFE_RANGE, KC_7_NUMPAD, KC_8_OBSPAD, KC_9_EMOTEPAD,
  KC_F9_NUMPAD, KC_F10_OBSPAD, KC_F11_EMOTEPAD, KC_F12_RESET,
  KC_HOLD_NUMPAD, KC_HOLD_OBSPAD, KC_HOLD_RESET,
  KC_CONCERN, KC_TREVINO, KC_TOOHIGH, KC_BOLOHMM,
  KC_PRIDEPOG, KC_HAHADOGE, KC_TSTORMS, KC_MIX,
  KC_GOODLUCK, KC_HAHASWEAT, KC_CCTV, KC_DBSTYLE
};

const uint16_t PROGMEM keymaps[][4][4] = {
  [numpad] = LAYOUT_ortho_4x4(
    KC_7_NUMPAD,    KC_8_OBSPAD,    KC_9_EMOTEPAD,    KC_DIV_RESET,
    KC_KP_4,        KC_KP_5,        KC_KP_6,          KC_KP_ASTERISK,
    KC_KP_1,        KC_KP_2,        KC_KP_3,          KC_KP_MINUS,
    KC_KP_0,        KC_KP_DOT,      KC_KP_ENTER,      KC_KP_PLUS
  ),
  [emote] = LAYOUT_ortho_4x4(
    KC_HOLD_NUMPAD, KC_HOLD_OBSPAD, KC_NO,            KC_HOLD_RESET,
    KC_CONCERN,     KC_TREVINO,     KC_TOOHIGH,       KC_BOLOHMM,
    KC_PRIDEPOG,    KC_HAHADOGE,    KC_TSTORMS,       KC_MIX,
    KC_GOODLUCK,    KC_HAHASWEAT,   KC_CCTV,          KC_DBSTYLE
  ),
  [obs] = LAYOUT_ortho_4x4(
    KC_F9_NUMPAD,   HYPR(KC_F10),   KC_F11_EMOTEPAD,  KC_F12_RESET,
    HYPR(KC_F13),   HYPR(KC_F14),   HYPR(KC_F15),     HYPR(KC_F16),
    HYPR(KC_F17),   HYPR(KC_F18),   HYPR(KC_F19),     HYPR(KC_F20),
    HYPR(KC_F21),   HYPR(KC_F22),   HYPR(KC_F23),     HYPR(KC_F24)
  ),

};

const uint16_t hold_time = 500;
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

uint16_t layer_keydown_timer;
void process_layer_hold(uint16_t keycode, keyrecord_t *record, uint8_t layer) {
  if (record->event.pressed) {
    layer_keydown_timer = timer_read();
  } else {
    if (timer_elapsed(layer_keydown_timer) > hold_time) {
      layer_clear();
      layer_on(layer);
    } else {
      tap_code16(keycode);
    }
  }
}

uint16_t numlock_keydown_timer;
void process_numlock_hold(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    numlock_keydown_timer = timer_read();
  } else {
    if (timer_elapsed(numlock_keydown_timer) > hold_time) {
      tap_code16(KC_NUMLOCK);
    } else {
      tap_code16(keycode);
    }
  }
}

bool send_emote(keyrecord_t *record, const char *msg) {
  if(record->event.pressed){
    send_string(msg);
    return false;
  }
  return true;
}

bool process_other_keys(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_CONCERN: {
      return send_emote(record, "ConcernWealthe ");
    }
    case KC_TREVINO: {
      return send_emote(record, "TrevinoGasm ");
    }
    case KC_TOOHIGH: {
      return send_emote(record, "TooHigh ");
    }
      case KC_BOLOHMM: {
      return send_emote(record, "BoloHmm ");
    }
    case KC_PRIDEPOG: {
      return send_emote(record, "PridePog ");
    }
    case KC_HAHADOGE: {
      return send_emote(record, "HahaDoge ");
    }
    case KC_TSTORMS: {
      return send_emote(record, "baldnaTstorm ");
    }
    case KC_MIX: {
      return send_emote(record, "baldnaMix ");
    }
    case KC_GOODLUCK: {
      return send_emote(record, "baldnaGL ");
    }
    case KC_HAHASWEAT: {
      return send_emote(record, "HahaSweat ");
    }
    case KC_CCTV: {
      return send_emote(record, "baldnaCCTV ");
    }
    case KC_DBSTYLE: {
      return send_emote(record, "DBstyle ");
    }
    default: {
      return true;
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // numpad top row
    case KC_7_NUMPAD: {
      process_numlock_hold(KC_KP_7, record);
      return false;
    }
    case KC_8_OBSPAD: {
      process_layer_hold(KC_KP_8, record, obs);
      return false;
    }
    case KC_9_EMOTEPAD: {
      process_layer_hold(KC_KP_9, record, emote);
      return false;
    }
    case KC_DIV_RESET: {
      process_reset_hold(KC_KP_SLASH, record);
      return false;
    }

    // emote top row
    case KC_HOLD_NUMPAD: {
      process_layer_hold(KC_NO, record, numpad);
      return false;
    }
    case KC_HOLD_OBSPAD: {
      process_layer_hold(KC_NO, record, obs);
      return false;
    }
    // row 1 col 3 is nop on this layher
    case KC_HOLD_RESET: {
      process_reset_hold(KC_NO, record);
      return false;
    }

    // obs top row
    case KC_F9_NUMPAD: {
      process_layer_hold(HYPR(KC_F9), record, numpad);
      return false;
    }
    // row 1 col 2 is normal key on this layer
    case KC_F11_EMOTEPAD: {
      process_layer_hold(HYPR(KC_F11), record, emote);
      return false;
    }
    case KC_F12_RESET: {
      process_reset_hold(HYPR(KC_F12), record);
      return false;
    }


    default: {
      return process_other_keys(keycode, record);
    }
  }
}