#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE,  // USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,               // USB Toggle Automatic GCR control
    DBG_TOG,                // DEBUG Toggle On / Off
    DBG_MTRX,               // DEBUG Toggle Matrix Prints
    DBG_KBD,                // DEBUG Toggle Keyboard Prints
    DBG_MOU,                // DEBUG Toggle Mouse Prints
    MD_BOOT,                // Restart into bootloader after hold timeout
};

// Layer Declarations
enum {
    _WIN_LOWER = 0,
    _WIN_RAISE,
    _MAC_LOWER,
    _MAC_RAISE,
    // ..., the rest of your layers
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_WIN_LOWER] = LAYOUT_65_ansi_blocker(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, TO(_MAC_LOWER), MO(_WIN_RAISE), KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_WIN_RAISE), KC_LEFT, KC_DOWN, KC_RGHT),
                                                              [_WIN_RAISE] = LAYOUT_65_ansi_blocker(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_VOLU, KC_TRNS, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_VOLD, KC_CAPS, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_MPLY, KC_MSTP, KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), RGB_TOG, NK_TOGG, KC_TRNS, KC_WBAK, KC_WFWD, KC_TRNS, KC_TRNS, KC_PGUP, KC_STOP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END),
                                                              [_MAC_LOWER] = LAYOUT_65_ansi_blocker(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGDN, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, TO(_WIN_LOWER), MO(_MAC_RAISE), KC_LALT, KC_LGUI, KC_SPC, KC_LGUI, MO(_MAC_RAISE), KC_LEFT, KC_DOWN, KC_RGHT),
                                                              [_MAC_RAISE] = LAYOUT_65_ansi_blocker(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_VOLU, KC_TRNS, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_VOLD, KC_CAPS, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_MPLY, KC_MSTP, KC_TRNS, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), RGB_TOG, NK_TOGG, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_RGHT), KC_TRNS, KC_TRNS, KC_PGUP, KC_STOP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END)};

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable_noeeprom();
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable_noeeprom();
                    } break;
                }
            }
            return false;
        default:
            return true;  // Process all other keycodes normally
    }
}

// changes underglow based on current layer
#define RBG_VAL 120
#define LAYER_INDICATOR_LED_MIN 80
#define LAYER_INDICATOR_LED_MAX 82
static uint8_t capslock_leds[] = {59, 68, 69};
// rgb indicator
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    for (uint8_t i = LAYER_INDICATOR_LED_MIN; i <= LAYER_INDICATOR_LED_MAX; i++) {
        if (i >= LAYER_INDICATOR_LED_MIN && i <= LAYER_INDICATOR_LED_MAX) {
            switch (layer) {
                case _WIN_LOWER:
                    // green-ish
                    rgb_matrix_set_color(i, RGB_YELLOW);
                    break;
                case _WIN_RAISE:
                    // Red
                    rgb_matrix_set_color(i, RGB_RED);
                    break;
                case _MAC_LOWER:
                    // Dark Blue
                    rgb_matrix_set_color(i, RGB_PURPLE);
                    break;
                case _MAC_RAISE:
                default:
                    // Default colors
                    rgb_matrix_set_color(i, RGB_GREEN);
                    break;
            }
        }
    }
    for (uint8_t idx = 0; idx <= sizeof(capslock_leds) / sizeof(capslock_leds[0]); idx++) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(capslock_leds[idx], 255, 255, 255);
        } else {
            rgb_matrix_set_color(capslock_leds[idx], 0, 0, 0);
        }
    }
}
