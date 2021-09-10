#include QMK_KEYBOARD_H

#define BRIGHTNESS 75
#define NUMPAD_BLUE 169
#define OBS_PURPLE 185
#define EMOTE_RED 0
#define LAYER_EFFECT RGBLIGHT_MODE_BREATHING

enum layers {
 LAYER_NUMPAD,
 LAYER_EMOTE,
 LAYER_OBS
};

enum custom_keycodes {
  KC_DIV_RESET = SAFE_RANGE, KC_7_NUMLOCK, KC_8_OBSPAD, KC_9_EMOTEPAD,
  KC_F9_NUMPAD, KC_F10_OBSPAD, KC_F11_EMOTEPAD, KC_F12_RESET,
  KC_HOLD_NUMPAD, KC_HOLD_OBSPAD, KC_HOLD_RESET,
  KC_CONCERN, KC_TREVINO, KC_TOOHIGH, KC_BOLOHMM,
  KC_PRIDEPOG, KC_HAHADOGE, KC_TSTORMS, KC_MIX,
  KC_GOODLUCK, KC_HAHASWEAT, KC_CCTV, KC_DBSTYLE
};

enum {
  TD_7_NUMPAD = 0,  TD_8_OBSPAD,    TD_9_EMOTEPAD,    TD_DIV_RESET,
  TD_F9_NUMPAD,     TD_F10_OBSPAD,  TD_F11_EMOTEPAD,  TD_F12_RESET,
  TD_NOP_NUMPAD,    TD_NOP_OBSPAD,  /* NOP, */        TD_NOP_RESET
};

const uint16_t PROGMEM keymaps[][4][4] = {
  [LAYER_NUMPAD] = LAYOUT_ortho_4x4(
    KC_7_NUMLOCK,   `KC_8_OBSPAD,    KC_9_EMOTEPAD,    KC_DIV_RESET,
    KC_KP_4,        KC_KP_5,        KC_KP_6,          KC_KP_ASTERISK,
    KC_KP_1,        KC_KP_2,        KC_KP_3,          KC_KP_MINUS,
    KC_KP_0,        KC_KP_DOT,      KC_KP_ENTER,      KC_KP_PLUS
  ),
  [LAYER_EMOTE] = LAYOUT_ortho_4x4(
    KC_HOLD_NUMPAD, KC_HOLD_OBSPAD, KC_NO,            KC_HOLD_RESET,
    KC_CONCERN,     KC_TREVINO,     KC_TOOHIGH,       KC_BOLOHMM,
    KC_PRIDEPOG,    KC_HAHADOGE,    KC_TSTORMS,       KC_MIX,
    KC_GOODLUCK,    KC_HAHASWEAT,   KC_CCTV,          KC_DBSTYLE
  ),
  [LAYER_OBS] = LAYOUT_ortho_4x4(
    KC_F9_NUMPAD,   HYPR(KC_F10),   KC_F11_EMOTEPAD,  KC_F12_RESET,
    HYPR(KC_F13),   HYPR(KC_F14),   HYPR(KC_F15),     HYPR(KC_F16),
    HYPR(KC_F17),   HYPR(KC_F18),   HYPR(KC_F19),     HYPR(KC_F20),
    HYPR(KC_F21),   HYPR(KC_F22),   HYPR(KC_F23),     HYPR(KC_F24)
  ),
};

void td_kc_reset(qk_tap_dance_state_t *state, uint16_t keycode) {
  if (state->count == 1) {
    tap_code16(keycode);
  } else if (state->count == 2) {
    reset_keyboard();
  }
  reset_tap_dance(state);
}

void td_div_reset(qk_tap_dance_state_t *state, void *user_data) { td_kc_reset(state, KC_KP_SLASH); }
void td_f12_reset(qk_tap_dance_state_t *state, void *user_data) { td_kc_reset(state, HYPR(KC_F12)); }


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_7_NUMPAD]     = ACTION_TAP_DANCE_DOUBLE(KC_KP_7, KC_NUMLOCK),
  [TD_8_OBSPAD]     = ACTION_TAP_DANCE_LAYER_MOVE(KC_KP_8, LAYER_OBS),
  [TD_9_EMOTEPAD]   = ACTION_TAP_DANCE_LAYER_MOVE(KC_KP_7, LAYER_EMOTE),
  [TD_DIV_RESET]    = ACTION_TAP_DANCE_FN(td_div_reset),

  [TD_F9_NUMPAD]    = ACTION_TAP_DANCE_LAYER_MOVE(HYPR(KC_F9), LAYER_NUMPAD),
  [TD_F10_OBSPAD]   = ACTION_TAP_DANCE_LAYER_MOVE(HYPR(KC_F10), LAYER_NUMPAD),
  [TD_F11_EMOTEPAD] = ACTION_TAP_DANCE_LAYER_MOVE(HYPR(KC_F11), LAYER_NUMPAD),
  [TD_F12_RESET]    = ACTION_TAP_DANCE_FN(td_f12_reset),

  [TD_NOP_NUMPAD]   = ACTION_TAP_DANCE_LAYER_MOVE(KC_KP_7, LAYER_NUMPAD),
  [TD_NOP_OBSPAD]   = ACTION_TAP_DANCE_LAYER_MOVE(KC_KP_7, LAYER_NUMPAD),
  [TD_NOP_RESET]    = ACTION_TAP_DANCE_LAYER_MOVE(KC_KP_7, LAYER_NUMPAD),
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

void switch_to_layer(uint8_t layer) {
  switch (layer) {
    case LAYER_NUMPAD:
      rgblight_mode_noeeprom(LAYER_EFFECT);
      rgblight_sethsv_noeeprom(NUMPAD_BLUE, 255, BRIGHTNESS);
      break;
    case LAYER_EMOTE:
      rgblight_mode_noeeprom(LAYER_EFFECT);
      rgblight_sethsv_noeeprom(EMOTE_RED, 255, BRIGHTNESS);
      break;
    case LAYER_OBS:
      rgblight_mode_noeeprom(LAYER_EFFECT);
      rgblight_sethsv_noeeprom(OBS_PURPLE, 255, BRIGHTNESS);
      break;
    default:
      break;
  }
  layer_clear();
  layer_on(layer);
}

uint16_t layer_keydown_timer;
void process_layer_hold(uint16_t keycode, keyrecord_t *record, uint8_t layer) {
  if (record->event.pressed) {
    layer_keydown_timer = timer_read();
  } else {
    if (timer_elapsed(layer_keydown_timer) > hold_time) {
      switch_to_layer(layer);
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
    case KC_7_NUMLOCK: {
      process_numlock_hold(KC_KP_7, record);
      return false;
    }
    case KC_8_OBSPAD: {
      process_layer_hold(KC_KP_8, record, LAYER_OBS);
      return false;
    }
    case KC_9_EMOTEPAD: {
      process_layer_hold(KC_KP_9, record, LAYER_EMOTE);
      return false;
    }
    case KC_DIV_RESET: {
      process_reset_hold(KC_KP_SLASH, record);
      return false;
    }

    // emote top row
    case KC_HOLD_NUMPAD: {
      process_layer_hold(KC_NO, record, LAYER_NUMPAD);
      return false;
    }
    case KC_HOLD_OBSPAD: {
      process_layer_hold(KC_NO, record, LAYER_OBS);
      return false;
    }
    // row 1 col 3 is nop on this layher
    case KC_HOLD_RESET: {
      process_reset_hold(KC_NO, record);
      return false;
    }

    // obs top row
    case KC_F9_NUMPAD: {
      process_layer_hold(HYPR(KC_F9), record, LAYER_NUMPAD);
      return false;
    }
    // row 1 col 2 is normal key on this layer
    case KC_F11_EMOTEPAD: {
      process_layer_hold(HYPR(KC_F11), record, LAYER_EMOTE);
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

void keyboard_post_init_user(void) {
  rgblight_mode_noeeprom(LAYER_EFFECT);
  rgblight_sethsv_noeeprom(NUMPAD_BLUE, 255, BRIGHTNESS);
}
