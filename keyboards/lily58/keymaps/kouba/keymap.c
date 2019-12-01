#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif






extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2



enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

enum {
  TD_CO_PA,
  TD_SHIFT_CAPS,
  TD_CTRL_ALT_DEL,
};

#define DVTLS LCTL(LSFT(KC_I))
#define CLRCCH LCTL(LSFT(KC_DEL))

//TODO: add tap dance on 'i' to do ctrl+shift+i
//TODO: add tap dance on 'del' to do ctrl+shift+del
//TAPDANCE : Copy & Paste
void dance_cpst_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LCTL);
    register_code (KC_C);
  } else {
    register_code (KC_LCTL);
    register_code (KC_V);
  }
}

void dance_cpst_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
    unregister_code (KC_C);
  } else {
    unregister_code (KC_LCTL);
    unregister_code (KC_V);
  }
}

//TAPDANCE : Ctrl Alt Del and Ctrl Shift Esc
void dance_cad_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LCTL);
    register_code (KC_LALT);
    register_code (KC_DEL);
  } else {
    register_code (KC_LCTL);
    register_code (KC_LSFT);
    register_code (KC_ESC);
  }
}

void dance_cad_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LCTL);
    unregister_code (KC_LALT);
    unregister_code (KC_DEL);
  } else {
    unregister_code (KC_LCTL);
    unregister_code (KC_LSFT);
    unregister_code (KC_ESC);
  }
}


//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Copy, twice for Paste
  [TD_CO_PA]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cpst_finished, dance_cpst_reset),
    //Tap once for Copy, twice for Paste
  [TD_CTRL_ALT_DEL]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cad_finished, dance_cad_reset),
    //Tap once for Shift, twice for Caps Lock
  [TD_SHIFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MS Clk|    | CP PST|------+------+------+------+------+------|
 * |  DEL |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | Alt  | CTL  | /Space  /       \ RAISE\  |LOWER |DEVTLS|CLRCCH|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
            KC_GESC, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
             KC_TAB, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  TD(TD_SHIFT_CAPS), KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
             KC_DEL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MS_BTN1,  TD(TD_CO_PA),  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  XXXXXXX, \
                          KC_LGUI, KC_LALT, KC_LCTL, LT(1,KC_SPC),       LT(2,KC_ENT),   LOWER, DVTLS, CLRCCH \
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |  Up  |      |      |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|      | Left | Down | Right|      |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   =  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | Alt  | CTL  | /Space  /       \RAISE \  |LOWER |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_RAISE] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,\
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX,   KC_UP,  KC_LCBR, KC_RCBR, KC_BSLS, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, KC_EQL, KC_PLUS,  KC_LCBR, KC_RCBR, KC_PIPE, \
                             XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      |   -  |   +  |      |      |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | Alt  | CTL  | /Space  /       \RAISE \  |LOWER |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT( \
  _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                               _______, _______, _______, KC_LCBR, KC_RCBR, _______, \
  KC_GRV,  XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX,                                  KC_6,    KC_7,    KC_8, KC_LBRC, KC_RBRC, _______, \
  _______, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX,                               XXXXXXX, KC_MINS, KC_PLUS,   KC_UP, KC_RGHT, XXXXXXX, \
  _______, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, _______, TD(TD_CTRL_ALT_DEL), XXXXXXX, KC_PLUS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, \
                             _______,    KC_0, _______, _______,             _______, _______, _______, _______ \
),
};



void encoder_update_user(uint8_t index, bool clockwise, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (index == 0  && IS_LAYER_ON(layer2)) { /* First encoder : Layer Layer 2*/
    if (clockwise) {
      tap_code(KC_VOLD);
    } else {
      tap_code(KC_VOLU);
    }
  } else if (index == 0) { /* First encoder : Layer 1 */
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}


void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
  }
  return true;
}
