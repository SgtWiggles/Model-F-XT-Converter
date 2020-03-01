#include "Command.h"

#include <Arduino.h>
#include <Keyboard.h>

uint8_t layer = 1;

#define BASE 0

void initBaseCommands() {
    memset(keymap, 0, sizeof(keymap) / sizeof(keymap[0][0]));
    // clang-format off
    keymap[F_TILDE][BASE]       = REMAP(KEY_TILDE              );
    keymap[F_1][BASE]           = REMAP(KEY_1                  );
    keymap[F_2][BASE]           = REMAP(KEY_2                  );
    keymap[F_3][BASE]           = REMAP(KEY_3                  );
    keymap[F_4][BASE]           = REMAP(KEY_4                  );
    keymap[F_5][BASE]           = REMAP(KEY_5                  );
    keymap[F_6][BASE]           = REMAP(KEY_6                  );
    keymap[F_7][BASE]           = REMAP(KEY_7                  );
    keymap[F_8][BASE]           = REMAP(KEY_8                  );
    keymap[F_9][BASE]           = REMAP(KEY_9                  );
    keymap[F_0][BASE]           = REMAP(KEY_0                  );
    keymap[F_MINUS][BASE]       = REMAP(KEY_MINUS              );
    keymap[F_EQUAL][BASE]       = REMAP(KEY_EQUAL              );
    keymap[F_BACKSPACE][BASE]   = REMAP(KEY_BACKSPACE          );
    keymap[F_TAB][BASE]         = REMAP(KEY_TAB                );
    keymap[F_Q][BASE]           = REMAP(KEY_Q                  );
    keymap[F_W][BASE]           = REMAP(KEY_W                  );
    keymap[F_E][BASE]           = REMAP(KEY_E                  );
    keymap[F_R][BASE]           = REMAP(KEY_R                  );
    keymap[F_T][BASE]           = REMAP(KEY_T                  );
    keymap[F_Y][BASE]           = REMAP(KEY_Y                  );
    keymap[F_U][BASE]           = REMAP(KEY_U                  );
    keymap[F_I][BASE]           = REMAP(KEY_I                  );
    keymap[F_O][BASE]           = REMAP(KEY_O                  );
    keymap[F_P][BASE]           = REMAP(KEY_P                  );
    keymap[F_LEFT_BRACE][BASE]  = REMAP(KEY_LEFT_BRACE         );
    keymap[F_RIGHT_BRACE][BASE] = REMAP(KEY_RIGHT_BRACE        );
    keymap[F_ENTER][BASE]       = REMAP(KEY_ENTER              );
    keymap[F_CTRL][BASE]        = REMAP(MODIFIERKEY_CTRL       );
    keymap[F_A][BASE]           = REMAP(KEY_A                  );
    keymap[F_S][BASE]           = REMAP(KEY_S                  );
    keymap[F_D][BASE]           = REMAP(KEY_D                  );
    keymap[F_F][BASE]           = REMAP(KEY_F                  );
    keymap[F_G][BASE]           = REMAP(KEY_G                  );
    keymap[F_H][BASE]           = REMAP(KEY_H                  );
    keymap[F_J][BASE]           = REMAP(KEY_J                  );
    keymap[F_K][BASE]           = REMAP(KEY_K                  );
    keymap[F_L][BASE]           = REMAP(KEY_L                  );
    keymap[F_SEMICOLON][BASE]   = REMAP(KEY_SEMICOLON          );
    keymap[F_QUOTE][BASE]       = REMAP(KEY_QUOTE              );
    keymap[F_ESC][BASE]         = REMAP(KEY_ESC                );
    keymap[F_SHIFT][BASE]       = REMAP(MODIFIERKEY_SHIFT      );
    keymap[F_BACKSLASH][BASE]   = REMAP(KEY_BACKSLASH          );
    keymap[F_Z][BASE]           = REMAP(KEY_Z                  );
    keymap[F_X][BASE]           = REMAP(KEY_X                  );
    keymap[F_C][BASE]           = REMAP(KEY_C                  );
    keymap[F_V][BASE]           = REMAP(KEY_V                  );
    keymap[F_B][BASE]           = REMAP(KEY_B                  );
    keymap[F_N][BASE]           = REMAP(KEY_N                  );
    keymap[F_M][BASE]           = REMAP(KEY_M                  );
    keymap[F_COMMA][BASE]       = REMAP(KEY_COMMA              );
    keymap[F_PERIOD][BASE]      = REMAP(KEY_PERIOD             );
    keymap[F_SLASH][BASE]       = REMAP(KEY_SLASH              );
    keymap[F_RSHIFT][BASE]      = REMAP(MODIFIERKEY_RIGHT_SHIFT);
    keymap[F_PRTSC][BASE]       = REMAP(KEYPAD_ASTERIX         );
    keymap[F_ALT][BASE]         = REMAP(MODIFIERKEY_ALT        );
    keymap[F_SPACE][BASE]       = REMAP(KEY_SPACE              );
    keymap[F_CAPS_LOCK][BASE]   = REMAP(KEY_CAPS_LOCK          );
    keymap[F_F1][BASE]          = REMAP(KEY_F1                 );
    keymap[F_F2][BASE]          = REMAP(KEY_F2                 );
    keymap[F_F3][BASE]          = REMAP(KEY_F3                 );
    keymap[F_F4][BASE]          = REMAP(KEY_F4                 );
    keymap[F_F5][BASE]          = REMAP(KEY_F5                 );
    keymap[F_F6][BASE]          = REMAP(KEY_F6                 );
    keymap[F_F7][BASE]          = REMAP(KEY_F7                 );
    keymap[F_F8][BASE]          = REMAP(KEY_F8                 );
    keymap[F_F9][BASE]          = REMAP(KEY_F9                 );
    keymap[F_F10][BASE]         = REMAP(KEY_F10                );
    keymap[F_NUM_LOCK][BASE]    = REMAP(KEY_NUM_LOCK           );
    keymap[F_SCROLL_LOCK][BASE] = REMAP(KEY_SCROLL_LOCK        );
    keymap[F_PAD_7][BASE]       = REMAP(KEYPAD_7               );
    keymap[F_PAD_8][BASE]       = REMAP(KEYPAD_8               );
    keymap[F_PAD_9][BASE]       = REMAP(KEYPAD_9               );
    keymap[F_PAD_MINUS][BASE]   = REMAP(KEYPAD_MINUS           );
    keymap[F_PAD_4][BASE]       = REMAP(KEYPAD_4               );
    keymap[F_PAD_5][BASE]       = REMAP(KEYPAD_5               );
    keymap[F_PAD_6][BASE]       = REMAP(KEYPAD_6               );
    keymap[F_PAD_PLUS][BASE]    = REMAP(KEYPAD_PLUS            );
    keymap[F_PAD_1][BASE]       = REMAP(KEYPAD_1               );
    keymap[F_PAD_2][BASE]       = REMAP(KEYPAD_2               );
    keymap[F_PAD_3][BASE]       = REMAP(KEYPAD_3               );
    keymap[F_PAD_0][BASE]       = REMAP(KEYPAD_0               );
    keymap[F_PAD_PERIOD][BASE]  = REMAP(KEYPAD_PERIOD          );
    // clang-format on
}

unsigned runKey(unsigned fkey, bool released) {
    Command const* cmd = &keymap[fkey][0];

    for (int i = TOTAL_LAYERS - 1; i >= 0; --i) {
        Command const* c = &keymap[fkey][i];
        if ((layer & (1 << i)) && c->command != Command::PASS_THROUGH) {
            cmd = c;
            break;
        }
    }

    switch (cmd->command) {
        case Command::TOGGLE_LAYER:
            if (!released)
                layer ^= (1 << cmd->data);
            return 0;
        case Command::HOLD_LAYER: {
            uint8_t const mask = ~(1 << cmd->data);
            layer = (layer & mask);  // turn layer bit off
            layer |= (!released << cmd->data);
            return 0;
        }
        case Command::REMAP_KEY:
            return cmd->data;

        default:
            return 0;
    }

    return 0;
}

