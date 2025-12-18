#include QMK_KEYBOARD_H

enum layers { MAC_BASE, WIN_BASE, MAC_FN, WIN_FN, MOUSE };

enum custom_keycodes { MC_COPY = SAFE_RANGE, MC_PASTE };

#define MT_F MT(MOD_LCTL, KC_F)
#define MT_J MT(MOD_RCTL, KC_J)
#define MT_D MT(MOD_LGUI, KC_D)
#define MT_K MT(MOD_RGUI, KC_K)
#define MT_S MT(MOD_LALT, KC_S)
#define MT_L MT(MOD_RALT, KC_L)
#define MT_SCLN MT(MOD_RSFT, KC_SCLN)
#define MT_A MT(MOD_LSFT, KC_A)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_RSFT OSM(MOD_RSFT)

static uint16_t esc_timer = 0;
static uint16_t copy_timer = 0;
static uint16_t paste_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_68(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PSCR,
        KC_ESC,  MT_A,    MT_S,    MT_D,    MT_F,    KC_G,    KC_H,    MT_J,    MT_K,    MT_L,    MT_SCLN, KC_QUOT,          KC_ENT,  KC_END,
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OS_RSFT,          KC_UP,   KC_PGDN,
        KC_LALT, KC_LCTL, KC_LGUI, KC_SPC,  KC_RGUI, MO(MAC_FN), KC_NO,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [WIN_BASE] = LAYOUT_ansi_68(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PSCR,
        KC_ESC,  MT_A,    MT_S,    MT_D,    MT_F,    KC_G,    KC_H,    MT_J,    MT_K,    MT_L,    MT_SCLN, KC_QUOT,          KC_ENT,  KC_END,
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OS_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_RALT, MO(WIN_FN), KC_NO,         KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [MAC_FN] = LAYOUT_ansi_68(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, RGB_TOG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_SPI, KC_TRNS, RGB_MOD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, RGB_VAI,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_HUI, RGB_VAD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_SAI, RGB_HUD, RGB_SAD
    ),
    [WIN_FN] = LAYOUT_ansi_68(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, RGB_TOG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_SPD, RGB_SPI, KC_TRNS, RGB_MOD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, RGB_VAI,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_HUI, RGB_VAD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_SAI, RGB_HUD, RGB_SAD
    ),
    [MOUSE] = LAYOUT_ansi_68(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MC_COPY, KC_NO,   KC_NO,   KC_NO,   MC_PASTE,KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_TRNS, KC_NO,   KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN1, KC_NO, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MS_WH_UP, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            if (record->event.pressed) {
                esc_timer = timer_read();
                
                if (layer_state_is(MOUSE)) {
                    layer_off(MOUSE);
                    return false; 
                }
                
            } else {
                if (!layer_state_is(MOUSE) && timer_elapsed(esc_timer) < TAPPING_TERM) {
                    return true;
                } else if (timer_elapsed(esc_timer) >= TAPPING_TERM) {
                    layer_on(MOUSE);
                    return false;
                }
            }
            return true;
            
        case MC_COPY:
            if (record->event.pressed) {
                copy_timer = timer_read();
            } else {
                if (timer_elapsed(copy_timer) < TAPPING_TERM) {
                    tap_code16(C(KC_C));
                } else {
                    tap_code16(C(S(KC_C)));
                }
            }
            return false;

        case MC_PASTE:
            if (record->event.pressed) {
                paste_timer = timer_read();
            } else {
                if (timer_elapsed(paste_timer) < TAPPING_TERM) {
                    tap_code16(C(KC_V));
                } else {
                    tap_code16(C(S(KC_V)));
                }
            }
            return false;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
        case MT_A:
        case MT_S:
        case MT_D:
        case MT_F:
        case MT_J:
        case MT_K:
        case MT_L:
        case MT_SCLN:
            return false;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t old_layer = get_highest_layer(layer_state);
    uint8_t new_layer = get_highest_layer(state);
    
    if (new_layer == MOUSE && old_layer != MOUSE) {
        clear_keyboard();
        clear_mods();
        clear_oneshot_mods();
    }
    
    if (old_layer == MOUSE && new_layer != MOUSE) {
        clear_keyboard();
        clear_mods();
        clear_oneshot_mods();
    }
    
    return state;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (current_layer == MOUSE) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(MOUSE, (keypos_t){col, row});
                    if (keycode == KC_MS_LEFT || keycode == KC_MS_DOWN || keycode == KC_MS_UP || keycode == KC_MS_RIGHT || 
                        keycode == KC_MS_BTN1 || keycode == KC_MS_BTN2 || keycode == KC_MS_BTN3 || 
                        keycode == KC_MS_WH_UP || keycode == KC_MS_WH_DOWN || keycode == KC_MS_WH_LEFT || keycode == KC_MS_WH_RIGHT) {
                        rgb_matrix_set_color(index, 0, 100, 255);
                    }
                    if (keycode == MC_COPY || keycode == MC_PASTE) {
                        rgb_matrix_set_color(index, 0, 255, 100);
                    }
                }
            }
        }
    }

    if (current_layer == MAC_FN || current_layer == WIN_FN) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});
                    if (keycode == RGB_TOG || keycode == RGB_MOD || keycode == RGB_VAI || keycode == RGB_VAD || 
                        keycode == RGB_HUI || keycode == RGB_HUD || keycode == RGB_SAI || keycode == RGB_SAD || 
                        keycode == RGB_SPI || keycode == RGB_SPD) {
                        rgb_matrix_set_color(index, 255, 150, 0);
                    }
                }
            }
        }
    }

    uint8_t mods = get_mods() | get_oneshot_mods();
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED) {
                uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col, row});
                if ((keycode == MT_A || keycode == MT_S || keycode == MT_D || keycode == MT_F || 
                     keycode == MT_J || keycode == MT_K || keycode == MT_L || keycode == MT_SCLN) && 
                    (mods & (MOD_MASK_SHIFT | MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI))) {
                    rgb_matrix_set_color(index, 255, 0, 0);
                }
            }
        }
    }

    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
}
