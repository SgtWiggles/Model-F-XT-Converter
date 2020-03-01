#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

enum { PASS_THROUGH = 0, TOGGLE_LAYER, HOLD_LAYER, REMAP_KEY, CALL_FUNC };
struct Command {
    uint16_t data;
    uint8_t command;
};

#define TOGGLE(LAYER) \
    (struct Command) { LAYER, TOGGLE_LAYER }
#define HOLD(LAYER) \
    (struct Command) { LAYER, HOLD_LAYER }
#define REMAP(KEY) \
    (struct Command) { KEY, REMAP_KEY }
#define CALL(KEY) \
    (struct Command) { KEY, CALL_FUNC }

extern unsigned run_cmd(struct Command const* cmd, unsigned key, int released);
extern unsigned run_key(unsigned key, int released);
extern uint32_t layers;

extern uint8_t tap_count(unsigned key);
extern void tap_count_reset(unsigned key);

#define TOTAL_LAYERS 32
#define TOTAL_FUNCTIONS 512

// User defined
#define DEFINE_COMMAND_ARRAY() \
    struct Command const keymap[TOTAL_LAYERS][F_TOTAL] PROGMEM
#define DEFINE_FUNCTION_ARRAY() \
    unsigned (*funcmap[TOTAL_FUNCTIONS])(unsigned, int)

// User Defined
extern struct Command const keymap[TOTAL_LAYERS][F_TOTAL];
extern unsigned (*funcmap[TOTAL_FUNCTIONS])(unsigned, int);

#ifdef __cplusplus
}
#endif
