/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE


#define OLED_FADE_TIMEOUT 30000  // 30 seconds

// Variables for both modules
static uint16_t last_keycode = 0;

// Variables for the master
static uint32_t oled_timer = 0;

// Callback triggered on each keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_keycode = keycode;

        if (is_keyboard_master()) {
            oled_timer = timer_read32();
        }
    }
    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
      oled_timer = timer_read32();

      return OLED_ROTATION_270;
  } else {
      return rotation;
  }
}

static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,0,4,12,24,240,56,12,230,34,34,2,1,1,129,129,129,129,129,129,1,1,1,1,1,1,2,2,2,2,2,2,132,68,36,40,104,216,144,48,32,64,192,0,0,0,0,0,0,0,0,0,240,28,4,6,2,2,130,194,66,66,34,34,34,34,162,162,162,178,146,146,146,146,146,146,178,162,162,162,163,161,163,190,138,138,154,158,187,169,169,41,0,0,128,128,128,128,128,128,128,64,64,64,64,64,32,32,32,32,16,16,16,16,16,8,8,8,16,16,240,24,8,12,4,28,224,0,0,3,2,4,248,7,0,30,51,96,192,128,31,49,32,32,32,36,100,65,65,99,38,60,0,0,0,0,0,0,132,127,41,40,56,16,0,0,1,3,28,56,192,3,14,56,160,64,64,32,56,15,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,226,3,1,1,0,0,0,0,0,0,192,192,96,32,32,32,48,16,16,16,16,16,24,8,12,6,2,2,2,1,3,14,24,48,32,63,0,0,130,130,129,255,0,0,0,0,128,240,28,4,0,240,24,8,8,8,40,40,8,8,144,112,0,0,0,0,0,15,240,80,80,112,32,0,0,0,0,0,248,15,0,0,192,63,16,16,48,96,192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,128,128,128,128,128,128,128,128,0,0,0,0,0,0,0,0,0,128,128,255,128,128,128,128,128,128,0,0,0,0,1,3,2,6,4,4,4,8,8,8,8,8,8,8,8,8,8,232,48,8,8,8,8,248,0,0,0,0,0,0,113,31,12,8,56,48,51,38,44,40,33,33,33,33,34,34,35,33,33,32,32,32,32,32,32,32,34,45,40,40,40,40,40,40,40,36,52,19,24,12,7,1,0,0,0,0,0,3,14,8,16,16,16,48,32,33,33,67,67,67,67,71,69,133,132,132,132,132,132,132,132,132,140,136,136,136,137,137,153,241,81,81,81,121,105,233,168,168,168,8,0,0,0,1,1,1,1,1,3,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,3,6,4,12,24,19,30,0
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

static void render_status(void) {
    // Clear the display first
    oled_clear();

    oled_set_cursor(0, 0);

    oled_write("CORNE", true);
    oled_write_ln_P(PSTR("   v3"), true);

    oled_write("_____", false);
    oled_write_ln_P(PSTR(""), false);

    // Host Keyboard Layer Status

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("SYM"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("SYS"), false);
            break;
        default:
            oled_write_ln_P(PSTR("???"), false);
    }

    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("KEY"), false);
    char keycode_str[16];
    snprintf(keycode_str, sizeof(keycode_str), "%02X", last_keycode);
    oled_write_ln(keycode_str, false);

    oled_write_ln_P(PSTR(""), false);
    oled_write("_____", false);
    oled_write_ln_P(PSTR(""), false);

    oled_write_ln_P(PSTR("WPM"), false);
    oled_write_ln_P(PSTR(""), false);
    char wpm_str[8];
    snprintf(wpm_str, sizeof(wpm_str), "  %03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (timer_elapsed32(oled_timer) > OLED_FADE_TIMEOUT) {
            oled_off();
            return false;
        }

        if (!is_oled_on()) {
            oled_on();
            oled_timer = timer_read32();
        }

        render_status();
    } else {
        oled_clear();
        oled_render_logo();
    }
    return false;
}
#endif
