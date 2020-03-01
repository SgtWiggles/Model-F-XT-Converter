#include "Command.h"

#include <keylayouts.h>

#define BASE 0

uint32_t layers = 1;

unsigned runKey(unsigned fkey, int released) {
    struct Command cmd;
    memcpy_P(&cmd, &keymap[0][fkey], sizeof(struct Command));

    for (int i = TOTAL_LAYERS - 1; i >= 0; --i) {
        struct Command c;
        memcpy_P(&c, &keymap[0][fkey], sizeof(struct Command));

        if ((layers & (1 << i)) && c.command != PASS_THROUGH) {
            cmd = c;
            break;
        }
    }

    switch (cmd.command) {
        case TOGGLE_LAYER:
            if (!released)
                layers ^= (1 << cmd.data);
            return 0;
        case HOLD_LAYER: {
            uint8_t const mask = ~(1 << cmd.data);
            layers = (layers & mask);  // turn layer bit off
            layers |= (!released << cmd.data);
            return 0;
        }
        case REMAP_KEY:
            return cmd.data;

        default:
            return 0;
    }

    return 0;
}

