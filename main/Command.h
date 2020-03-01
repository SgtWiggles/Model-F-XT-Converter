#pragma once
#include <stdint.h>

enum FKey {
    F_NULL,
    F_TILDE,
    F_1,
    F_2,
    F_3,
    F_4,
    F_5,
    F_6,
    F_7,
    F_8,
    F_9,
    F_0,
    F_MINUS,
    F_EQUAL,
    F_BACKSPACE,
    F_TAB,
    F_Q,
    F_W,
    F_E,
    F_R,
    F_T,
    F_Y,
    F_U,
    F_I,
    F_O,
    F_P,
    F_LEFT_BRACE,
    F_RIGHT_BRACE,
    F_ENTER,
    F_CTRL,
    F_A,
    F_S,
    F_D,
    F_F,
    F_G,
    F_H,
    F_J,
    F_K,
    F_L,
    F_SEMICOLON,
    F_QUOTE,
    F_ESC,
    F_SHIFT,
    F_BACKSLASH,
    F_Z,
    F_X,
    F_C,
    F_V,
    F_B,
    F_N,
    F_M,
    F_COMMA,
    F_PERIOD,
    F_SLASH,
    F_RSHIFT,
    F_PRTSC,
    F_ALT,
    F_SPACE,
    F_CAPS_LOCK,
    F_F1,
    F_F2,
    F_F3,
    F_F4,
    F_F5,
    F_F6,
    F_F7,
    F_F8,
    F_F9,
    F_F10,
    F_NUM_LOCK,
    F_SCROLL_LOCK,
    F_PAD_7,
    F_PAD_8,
    F_PAD_9,
    F_PAD_MINUS,
    F_PAD_4,
    F_PAD_5,
    F_PAD_6,
    F_PAD_PLUS,
    F_PAD_1,
    F_PAD_2,
    F_PAD_3,
    F_PAD_0,
    F_PAD_PERIOD,
    F_TOTAL
};

struct Command {
    enum { PASS_THROUGH = 0, TOGGLE_LAYER, HOLD_LAYER, REMAP_KEY, CALL_FUNC };
    uint16_t data;
    uint8_t command;
};

#define TOGGLE(LAYER) \
    Command { LAYER, Command::TOGGLE_LAYER }
#define HOLD(LAYER) \
    Command { LAYER, Command::HOLD_LAYER }
#define REMAP(KEY) \
    Command { KEY, Command::REMAP_KEY }
#define PASS() \
    Command { 0, Command::PASS_THROUGH }

extern unsigned runKey(unsigned key, bool released);
extern void initBaseCommands();

#define TOTAL_LAYERS 8
#define DEFINE_COMMAND_ARRAY() Command keymap[F_TOTAL][TOTAL_LAYERS]

// User Defined
extern DEFINE_COMMAND_ARRAY();
extern void initCommands();

