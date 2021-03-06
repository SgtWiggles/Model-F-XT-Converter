#include "Command.h"

#include <keylayouts.h>

#include <string.h>

#include "Functions.h"

#define BASE 0
#define USER 1
#define NUML 2
#define FNCL 3

unsigned func_layer_tap_toggle(unsigned key, int released) {
    static uint8_t keystate = 0;
    static struct Command const hold = HOLD(FNCL);
    static struct Command const togg = TOGGLE(FNCL);

    uint8_t count = tap_count(key);
    switch (count) {
        case 1: {
            keystate = 1;
            run_cmd(&hold, key, released);
        } break;
        case 2: {
            run_cmd(&togg, key, released);
            keystate = 2;
            tap_count_reset(key);
        } break;

        default:
            if (keystate != 2)
                run_cmd(&hold, key, released);

            tap_count_reset(key);
            break;
    }

    return 0;
}

#define FUNC_LAYER_TAP_PTR 0

DEFINE_FUNCTION_ARRAY() = {
    [FUNC_LAYER_TAP_PTR] = func_layer_tap_toggle,
};

DEFINE_COMMAND_ARRAY() = {
    [BASE] =
        {
            [F_TILDE] = REMAP(KEY_TILDE),
            [F_1] = REMAP(KEY_1),
            [F_2] = REMAP(KEY_2),
            [F_3] = REMAP(KEY_3),
            [F_4] = REMAP(KEY_4),
            [F_5] = REMAP(KEY_5),
            [F_6] = REMAP(KEY_6),
            [F_7] = REMAP(KEY_7),
            [F_8] = REMAP(KEY_8),
            [F_9] = REMAP(KEY_9),
            [F_0] = REMAP(KEY_0),
            [F_MINUS] = REMAP(KEY_MINUS),
            [F_EQUAL] = REMAP(KEY_EQUAL),
            [F_BACKSPACE] = REMAP(KEY_BACKSPACE),
            [F_TAB] = REMAP(KEY_TAB),
            [F_Q] = REMAP(KEY_Q),
            [F_W] = REMAP(KEY_W),
            [F_E] = REMAP(KEY_E),
            [F_R] = REMAP(KEY_R),
            [F_T] = REMAP(KEY_T),
            [F_Y] = REMAP(KEY_Y),
            [F_U] = REMAP(KEY_U),
            [F_I] = REMAP(KEY_I),
            [F_O] = REMAP(KEY_O),
            [F_P] = REMAP(KEY_P),
            [F_LEFT_BRACE] = REMAP(KEY_LEFT_BRACE),
            [F_RIGHT_BRACE] = REMAP(KEY_RIGHT_BRACE),
            [F_ENTER] = REMAP(KEY_ENTER),
            [F_CTRL] = REMAP(KEY_ESC),
            [F_A] = REMAP(KEY_A),
            [F_S] = REMAP(KEY_S),
            [F_D] = REMAP(KEY_D),
            [F_F] = REMAP(KEY_F),
            [F_G] = REMAP(KEY_G),
            [F_H] = REMAP(KEY_H),
            [F_J] = REMAP(KEY_J),
            [F_K] = REMAP(KEY_K),
            [F_L] = REMAP(KEY_L),
            [F_SEMICOLON] = REMAP(KEY_SEMICOLON),
            [F_QUOTE] = REMAP(KEY_QUOTE),
            [F_ESC] = CALL(FUNC_LAYER_TAP_PTR),
            [F_SHIFT] = REMAP(MODIFIERKEY_SHIFT),
            [F_BACKSLASH] = REMAP(KEY_BACKSLASH),
            [F_Z] = REMAP(KEY_Z),
            [F_X] = REMAP(KEY_X),
            [F_C] = REMAP(KEY_C),
            [F_V] = REMAP(KEY_V),
            [F_B] = REMAP(KEY_B),
            [F_N] = REMAP(KEY_N),
            [F_M] = REMAP(KEY_M),
            [F_COMMA] = REMAP(KEY_COMMA),
            [F_PERIOD] = REMAP(KEY_PERIOD),
            [F_SLASH] = REMAP(KEY_SLASH),
            [F_RSHIFT] = REMAP(MODIFIERKEY_RIGHT_SHIFT),
            [F_PRTSC] = REMAP(KEYPAD_ASTERIX),
            [F_ALT] = REMAP(MODIFIERKEY_CTRL),
            [F_SPACE] = REMAP(KEY_SPACE),
            [F_CAPS_LOCK] = REMAP(MODIFIERKEY_RIGHT_ALT),
            [F_F1] = REMAP(KEY_F1),
            [F_F2] = REMAP(KEY_F2),
            [F_F3] = REMAP(KEY_F3),
            [F_F4] = REMAP(KEY_F4),
            [F_F5] = REMAP(KEY_F5),
            [F_F6] = REMAP(KEY_F6),
            [F_F7] = REMAP(KEY_F7),
            [F_F8] = REMAP(KEY_F8),
            [F_F9] = REMAP(KEY_F9),
            [F_F10] = REMAP(KEY_F10),
            [F_NUM_LOCK] = TOGGLE(NUML),
            [F_SCROLL_LOCK] = REMAP(KEY_SCROLL_LOCK),
            [F_PAD_7] = REMAP(KEYPAD_7),
            [F_PAD_8] = REMAP(KEYPAD_8),
            [F_PAD_9] = REMAP(KEYPAD_9),
            [F_PAD_MINUS] = REMAP(KEYPAD_MINUS),
            [F_PAD_4] = REMAP(KEYPAD_4),
            [F_PAD_5] = REMAP(KEYPAD_5),
            [F_PAD_6] = REMAP(KEYPAD_6),
            [F_PAD_PLUS] = REMAP(KEYPAD_PLUS),
            [F_PAD_1] = REMAP(KEYPAD_1),
            [F_PAD_2] = REMAP(KEYPAD_2),
            [F_PAD_3] = REMAP(KEYPAD_3),
            [F_PAD_0] = REMAP(KEYPAD_0),
            [F_PAD_PERIOD] = REMAP(KEYPAD_PERIOD),
        },

    [NUML] =
        {
            [F_F8] = REMAP(MODIFIERKEY_GUI),
            [F_F10] = REMAP(MODIFIERKEY_ALT),
        },

    [FNCL] =
        {
            [F_NUM_LOCK] = REMAP(KEY_NUM_LOCK),
            [F_1] = REMAP(KEY_F1),
            [F_2] = REMAP(KEY_F2),
            [F_3] = REMAP(KEY_F3),
            [F_4] = REMAP(KEY_F4),
            [F_5] = REMAP(KEY_F5),
            [F_6] = REMAP(KEY_F6),
            [F_7] = REMAP(KEY_F7),
            [F_8] = REMAP(KEY_F8),
            [F_9] = REMAP(KEY_F9),
            [F_0] = REMAP(KEY_F10),
            [F_MINUS] = REMAP(KEY_F11),
            [F_EQUAL] = REMAP(KEY_F12),
            [F_BACKSPACE] = REMAP(KEY_DELETE),

            [F_H] = REMAP(KEY_LEFT),
            [F_J] = REMAP(KEY_DOWN),
            [F_K] = REMAP(KEY_UP),
            [F_L] = REMAP(KEY_RIGHT),

            [F_LEFT_BRACE] = REMAP(KEY_MEDIA_VOLUME_DEC),
            [F_RIGHT_BRACE] = REMAP(KEY_MEDIA_VOLUME_INC),
            [F_COMMA] = REMAP(KEY_MEDIA_PREV_TRACK),
            [F_PERIOD] = REMAP(KEY_MEDIA_NEXT_TRACK),
            [F_P] = REMAP(KEY_MEDIA_PLAY_PAUSE),
            [F_M] = REMAP(KEY_MEDIA_MUTE),
            [F_U] = REMAP(KEY_PAGE_UP),
            [F_D] = REMAP(KEY_PAGE_DOWN),
        },
};

