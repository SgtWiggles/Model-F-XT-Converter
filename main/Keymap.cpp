#include "Command.h"

#include <Arduino.h>
#include <Keyboard.h>

#include <string.h>

DEFINE_COMMAND_ARRAY();

#define BASE 0
#define USER 1
#define NUML 2
#define FNCL 3

void initCommands() {
    // clang-format off
    keymap[F_CTRL][BASE]      = REMAP(KEY_ESC);
    keymap[F_ALT][BASE]       = REMAP(MODIFIERKEY_CTRL);
    keymap[F_CAPS_LOCK][BASE] = REMAP(MODIFIERKEY_RIGHT_ALT);

    keymap[F_NUM_LOCK][BASE]  = TOGGLE(NUML);
    keymap[F_F8][NUML]        = REMAP(MODIFIERKEY_GUI);
    keymap[F_F10][NUML]       = REMAP(MODIFIERKEY_ALT);

    keymap[F_ESC][BASE]       = HOLD(FNCL);
    keymap[F_NUM_LOCK][FNCL]  = REMAP(KEY_NUM_LOCK);
    keymap[F_1][FNCL]         = REMAP(KEY_F1);
    keymap[F_2][FNCL]         = REMAP(KEY_F2);
    keymap[F_3][FNCL]         = REMAP(KEY_F3);
    keymap[F_4][FNCL]         = REMAP(KEY_F4);
    keymap[F_5][FNCL]         = REMAP(KEY_F5);
    keymap[F_6][FNCL]         = REMAP(KEY_F6);
    keymap[F_7][FNCL]         = REMAP(KEY_F7);
    keymap[F_8][FNCL]         = REMAP(KEY_F8);
    keymap[F_9][FNCL]         = REMAP(KEY_F9);
    keymap[F_0][FNCL]         = REMAP(KEY_F10);
    keymap[F_MINUS][FNCL]     = REMAP(KEY_F11);
    keymap[F_EQUAL][FNCL]     = REMAP(KEY_F12);
    keymap[F_BACKSPACE][FNCL] = REMAP(KEY_DELETE);

    keymap[F_H][FNCL] = REMAP(KEY_LEFT);
    keymap[F_J][FNCL] = REMAP(KEY_DOWN);
    keymap[F_K][FNCL] = REMAP(KEY_UP);
    keymap[F_L][FNCL] = REMAP(KEY_RIGHT);

    keymap[F_LEFT_BRACE][FNCL]  = REMAP(KEY_MEDIA_VOLUME_DEC);
    keymap[F_RIGHT_BRACE][FNCL] = REMAP(KEY_MEDIA_VOLUME_INC);
    keymap[F_COMMA][FNCL]       = REMAP(KEY_MEDIA_PREV_TRACK);
    keymap[F_PERIOD][FNCL]      = REMAP(KEY_MEDIA_NEXT_TRACK);
    keymap[F_P][FNCL]           = REMAP(KEY_MEDIA_PLAY_PAUSE);
    keymap[F_M][FNCL]           = REMAP(KEY_MEDIA_MUTE);
    keymap[F_U][FNCL]           = REMAP(KEY_PAGE_UP);
    keymap[F_D][FNCL]           = REMAP(KEY_PAGE_DOWN);
    // clang-format on
}
