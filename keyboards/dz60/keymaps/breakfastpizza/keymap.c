#include QMK_KEYBOARD_H

#define DEFAULT_LAYER 0
#define FN_LAYER 1
#define NUMPAD_LAYER 2
#define RGB_LAYER 3
#define DEBUG_LAYER 4

#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum custom_keycodes {
  SCRN = SAFE_RANGE,
  CK_BACK = TO(DEFAULT_LAYER),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SCRN:
      if (record->event.pressed) {
          // MacOS window screenshot mode CMD + SHIFT + 4 + SPACE
          SEND_STRING(SS_DOWN(X_RGUI)SS_DOWN(X_RSFT) "4" SS_UP(X_RSFT)SS_UP(X_RGUI)SS_DELAY(500)SS_TAP(X_SPC));
      }
      break;
  }
  return true;
};


void matrix_scan_user(void) {
  #ifdef RGBLIGHT_ENABLE
    static uint8_t old_layer = 255;
    uint8_t new_layer = biton32(layer_state);
    if (old_layer != new_layer) {
          switch (new_layer) {
            case DEFAULT_LAYER:
              rgblight_sethsv(255, 0, 60);
            break;
            case FN_LAYER:
              rgblight_setrgb(0x00, 0xA0, 0xFF); // #00A0FF BLUE
            break;
            case NUMPAD_LAYER:
              rgblight_setrgb(0xFF, 0x88, 0x00); // #FF8800 ORANGE
            break;
            case RGB_LAYER:
              rgblight_sethsv_at(15, 255, 255, 0);
              rgblight_sethsv_at(32, 255, 255, 1);
              rgblight_sethsv_at(48, 255, 255, 2);
              rgblight_sethsv_at(64, 255, 255, 3);
              rgblight_sethsv_at(80, 255, 255, 4);
              rgblight_sethsv_at(96, 255, 255, 5);
              rgblight_sethsv_at(112, 255, 255, 6);
              rgblight_sethsv_at(128, 255, 255, 7);
              rgblight_sethsv_at(144,255, 255, 8);
              rgblight_sethsv_at(160, 255, 255, 9);
              rgblight_sethsv_at(176, 255, 255, 10);
              rgblight_sethsv_at(192, 255, 255, 11);
              rgblight_sethsv_at(208, 255, 255, 12);
              rgblight_sethsv_at(224, 255, 255, 13);
              rgblight_sethsv_at(240, 255, 255, 14);
              rgblight_sethsv_at(255, 255, 255, 15);
            break;
            case DEBUG_LAYER:
              rgblight_setrgb(0xFF, 0x00, 0xFF); // #FF00FF MAGENTA
            break;
            }
        old_layer = new_layer;
    }
  #endif
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DEFAULT_LAYER 0
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │gsc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │bk │del│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │tab  │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │esc   │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │     ⮐ │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │L1 │sft│ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │sft│ ↑ │ ◌ │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │ctl │alt │cmd │spc     │sft │spc       │L1 │rgb│ ← │ ↓ │ → │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/

    [DEFAULT_LAYER] = LAYOUT_all(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        MO(1), KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, SCRN,
        KC_LCTL, KC_LALT, KC_LCMD, KC_SPC, KC_RSFT, KC_SPC, MO(1), RGB_TOG, KC_LEFT, KC_DOWN, KC_RGHT
    ),

/* FN_LAYER 1
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ ` │f1 │f2 │f3 │f4 │f5 │f6 │f7 │f8 │f9 │f10│f11│f12│   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │cap   │   │   │   │   │   │   │   │   │   │   │   │        │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │sft│pup│   │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │tg2 │tg3 │tg4 │        │____│          │___│   │hm │pdn│end│
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/

    [FN_LAYER] = LAYOUT_all(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F8, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,
        TG(2), TG(3), TG(4), XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END
    ),

/* NUMPAD_LAYER 2
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │ / │ * │ = │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │ 7 │ 8 │ 9 │ + │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │ 4 │ 5 │ 6 │ , │   │   │   │   │   │   │        │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │   │   │   │ 1 │ 2 │ 3 │ = │   │   │   │   │   │   │   │   │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │____│tg3 │tg4 │ 0      │ .  │ ent      │L1 │   │   │   │   │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/

    [NUMPAD_LAYER] = LAYOUT_all(
        XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS, KC_PAST, KC_PMNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_P7, KC_P8, KC_P9, KC_PPLS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_P4, KC_P5, KC_P6, KC_PCMM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_P1, KC_P2, KC_P3, KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, TG(3), TG(4), KC_P0, KC_PDOT, KC_PENT, CK_BACK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/* RGB_LAYER 3
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │pln│swl│snk│knt│xms│grd│tst│   │   │   │   │   │   │   │tog│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │mode │ H↑│ S↑│ V↑│SP↑│   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │ H↓│ S↓│ V↓│SP↓│   │   │   │   │   │   │   │        │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │tg2 │____│tg4 │        │L1  │          │   │   │   │   │   │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/

    [RGB_LAYER] = LAYOUT_all(
        RGB_M_P, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
        RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TG(2), _______, TG(4), XXXXXXX, CK_BACK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/* DEBUG_LAYER 4
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │EEP│dbg│res│   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │
 * ├───┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬───┬───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┴┬──┴─┬─┴──┬┴───┴───┼───┴┬──┴───┴───┼───┼───┼───┼───┼───┤
 * │tg2 │tg3 │____│        │L1  │          │   │   │   │   │   │
 * └────┴────┴────┴────────┴────┴──────────┴───┴───┴───┴───┴───┘
*/

    [DEBUG_LAYER] = LAYOUT_all(
        EEP_RST, DEBUG, RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TG(2), TG(3), _______, XXXXXXX, CK_BACK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};
