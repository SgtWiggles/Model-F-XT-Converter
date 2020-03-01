#include "Command.h"

#include "Config.h"

#include <Arduino.h>
#include <Keyboard.h>

uint8_t tapCounter[F_TOTAL];
uint32_t tapLast[F_TOTAL];

uint32_t layers = 1;

uint8_t tap_count(unsigned key) {
    if (millis() - tapLast[key] > TAP_TIMEOUT)
        return 0;
    return tapCounter[key];
}

unsigned run_key(unsigned fkey, int released) {
    struct Command cmd;
    memcpy_P(&cmd, &keymap[0][fkey], sizeof(struct Command));

    if (!released) {
        tapCounter[fkey] = tap_count(fkey) + 1;
        tapLast[fkey] = millis();
    }

    for (int i = TOTAL_LAYERS - 1; i >= 0; --i) {
        struct Command c;
        memcpy_P(&c, &keymap[i][fkey], sizeof(struct Command));

        if ((layers & (1 << i)) && c.command != PASS_THROUGH) {
            cmd = c;
            break;
        }
    }

    return run_cmd(&cmd, fkey, released);
}

void tap_count_reset(unsigned key) {
    tapCounter[key] = 0;
    tapLast[key] = 0;
}

unsigned run_cmd(struct Command const* cmd, unsigned fkey, int released) {
    switch (cmd->command) {
        case TOGGLE_LAYER:
            if (!released)
                layers ^= (1 << cmd->data);
            return 0;

        case HOLD_LAYER: {
            uint8_t const mask = ~(1 << cmd->data);
            layers = (layers & mask);  // turn layer bit off
            layers |= (!released << cmd->data);
            return 0;
        }

        case REMAP_KEY:
            return cmd->data;

        case CALL_FUNC:
            return (funcmap[cmd->data])(fkey, released);

        default:
            return 0;
    }
    return 0;
}

