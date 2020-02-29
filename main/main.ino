/* Copyright (C) 2020 Niran Pon
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define STR_PRODUCT L"IBM Model F XT"

#include <Arduino.h>
#include <Keyboard.h>

#define TEENSY_KEYBOARD_DEFINES
#include "Keymap.h"

#include "Layout.h"

#include "Config.h"

// Array tracks keys currently being held
uint8_t keysHeld[6] = {0, 0, 0, 0, 0, 0};  // 6 keys max

// global variables, track Ctrl, Shift, Alt, Gui (Windows), and NumLock key
// statuses.
int modifiers = 0;  // 1=c, 2=s, 3=sc, 4=a, 5=ac, 6=as, 7=asc, 8=g, 9=gc...

// so you have F11, F12, and the windows key (F8 when numlock is on)
bool numLock = 0;
bool astMode = 0;
bool fnMode = 0;

void interrupt();

void setup() {
    pinMode(CLK_PIN, INPUT_PULLUP);
    pinMode(DATA_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    attachInterrupt(CLK_PIN, interrupt, RISING);
}

// These handle press/release of Ctrl, Shift, Alt, and Gui keys
// We don't combine these as a single toggle (using XOR ^) because
// if the key press state between teensy and computer get out of sync,
// you would be stuck with the key state being reversed (up=down, down=up)
// (Okay, I'm paranoid)
void modKeyPress(uint8_t target) {
    modifiers = modifiers | target;
    updateModifiers();
}
void modKeyRel(uint8_t target) {
    modifiers = modifiers ^ target;
    updateModifiers();
}
void updateModifiers() {
    Keyboard.set_modifier(modifiers);
    Keyboard.send_now();
}

bool isMediaKey(uint16_t c) {
    return c >= 0xE400 && c <= 0xE7FF;
}

// Finds an open slot to place the key press signal in. (6 keys max)
// Ignores built-in key repeating.
void setOpenKey(uint16_t target) {
    if (isMediaKey(target)) {
        Keyboard.set_media(target);
        return;
    }

    target = target & 0xff;
    for (int i = 0; i < 6; i++) {
        //    if (keysHeld[i] == target)
        //      break;
        if (keysHeld[i] == 0) {
            switch (i) {
                case 0:
                    Keyboard.set_key1(target);
                    break;
                case 1:
                    Keyboard.set_key2(target);
                    break;
                case 2:
                    Keyboard.set_key3(target);
                    break;
                case 3:
                    Keyboard.set_key4(target);
                    break;
                case 4:
                    Keyboard.set_key5(target);
                    break;
                case 5:
                    Keyboard.set_key6(target);
                    break;
                default:
                    break;
            }
            keysHeld[i] = target;
            Keyboard.send_now();
            break;
        }
    }
}

// Clears a key from the buffer if it's there. Otherwise, ignores.
void clearKey(uint16_t target) {
    if (isMediaKey(target)) {
        Keyboard.set_media(0);
        return;
    }

    target = target & 0xff;
    for (int i = 0; i < 6; i++) {
        if (keysHeld[i] == target) {
            switch (i) {
                case 0:
                    Keyboard.set_key1(0);
                    break;
                case 1:
                    Keyboard.set_key2(0);
                    break;
                case 2:
                    Keyboard.set_key3(0);
                    break;
                case 3:
                    Keyboard.set_key4(0);
                    break;
                case 4:
                    Keyboard.set_key5(0);
                    break;
                case 5:
                    Keyboard.set_key6(0);
                    break;
                default:
                    break;
            }
            keysHeld[i] = 0;
            Keyboard.send_now();
        }
    }
}

bool isModifier(unsigned modkey) {
    switch (modkey) {
        case MODIFIERKEY_SHIFT:
        case MODIFIERKEY_RIGHT_SHIFT:
        case MODIFIERKEY_CTRL:
        case MODIFIERKEY_RIGHT_CTRL:
        case MODIFIERKEY_ALT:
        case MODIFIERKEY_RIGHT_ALT:
        case MODIFIERKEY_GUI:
        case MODIFIERKEY_RIGHT_GUI:
            return true;
        default:
            return false;
    }
}

unsigned remap(unsigned key, bool isRelease) {
#define REMAP(BASE_KEY, TARGET_KEY) \
    case BASE_KEY:                  \
        return TARGET_KEY
#define ACMAP(BASE_KEY) case BASE_KEY:
#define ON_MODE(MODE, KEY) \
    if (MODE)              \
        return KEY;
#define ON_MDEF(KEY) return KEY;
    switch (key) {
        REMAP(MODIFIERKEY_ALT, MODIFIERKEY_CTRL);
        REMAP(MODIFIERKEY_CTRL, KEY_ESC);
        REMAP(KEY_CAPS_LOCK, MODIFIERKEY_RIGHT_ALT);
        ACMAP(KEY_SCROLL_LOCK) {
            if (astMode && fnMode) {
                _reboot_Teensyduino_();
                return 0;
            }
            return KEY_PAUSE;
        }
        ACMAP(KEYPAD_ASTERIX) {
            astMode = !isRelease;
            return 0;
        }
        ACMAP(KEY_NUM_LOCK) {
            if (!isRelease)
                numLock = !numLock;
            return astMode ? 0 : KEY_NUM_LOCK;
        }
        ACMAP(KEY_F8) { return numLock ? KEY_F8 : MODIFIERKEY_GUI; }
        ACMAP(KEY_F10) { return numLock ? KEY_F10 : MODIFIERKEY_ALT; }
        ACMAP(KEY_ESC) {
            fnMode = !isRelease;
            if (isRelease) {
                Keyboard.set_media(0);
            }
            return 0;
        }
        ACMAP(KEY_1) {
            ON_MODE(fnMode, KEY_F1);
            ON_MDEF(KEY_1);
        }
        ACMAP(KEY_2) {
            ON_MODE(fnMode, KEY_F2);
            ON_MDEF(KEY_2);
        }
        ACMAP(KEY_3) {
            ON_MODE(fnMode, KEY_F3);
            ON_MDEF(KEY_3);
        }
        ACMAP(KEY_4) {
            ON_MODE(fnMode, KEY_F4);
            ON_MDEF(KEY_4);
        }
        ACMAP(KEY_5) {
            ON_MODE(fnMode, KEY_F5);
            ON_MDEF(KEY_5);
        }
        ACMAP(KEY_6) {
            ON_MODE(fnMode, KEY_F6);
            ON_MDEF(KEY_6);
        }
        ACMAP(KEY_7) {
            ON_MODE(fnMode, KEY_F7);
            ON_MDEF(KEY_7);
        }
        ACMAP(KEY_8) {
            ON_MODE(fnMode, KEY_F8);
            ON_MDEF(KEY_8);
        }
        ACMAP(KEY_9) {
            ON_MODE(fnMode, KEY_F9);
            ON_MDEF(KEY_9);
        }
        ACMAP(KEY_0) {
            ON_MODE(fnMode, KEY_F10);
            ON_MDEF(KEY_0);
        }
        ACMAP(KEY_MINUS) {
            ON_MODE(fnMode, KEY_F11);
            ON_MDEF(KEY_MINUS);
        }
        ACMAP(KEY_EQUAL) {
            ON_MODE(fnMode, KEY_F12);
            ON_MDEF(KEY_EQUAL);
        }
        ACMAP(KEY_BACKSPACE) {
            ON_MODE(fnMode, KEY_DELETE);
            ON_MDEF(KEY_BACKSPACE);
        }
        ACMAP(KEY_H) {
            ON_MODE(fnMode, KEY_LEFT);
            ON_MDEF(KEY_H);
        }
        ACMAP(KEY_J) {
            ON_MODE(fnMode, KEY_DOWN);
            ON_MDEF(KEY_J);
        }
        ACMAP(KEY_K) {
            ON_MODE(fnMode, KEY_UP);
            ON_MDEF(KEY_K);
        }
        ACMAP(KEY_L) {
            ON_MODE(fnMode, KEY_RIGHT);
            ON_MDEF(KEY_L);
        }

        ACMAP(KEY_LEFT_BRACE) {
            ON_MODE(fnMode, KEY_MEDIA_VOLUME_DEC);
            ON_MDEF(KEY_LEFT_BRACE);
        }
        ACMAP(KEY_RIGHT_BRACE) {
            ON_MODE(fnMode, KEY_MEDIA_VOLUME_INC);
            ON_MDEF(KEY_RIGHT_BRACE);
        }
        ACMAP(KEY_COMMA) {
            ON_MODE(fnMode, KEY_MEDIA_PREV_TRACK);
            ON_MDEF(KEY_COMMA);
        }
        ACMAP(KEY_PERIOD) {
            ON_MODE(fnMode, KEY_MEDIA_NEXT_TRACK);
            ON_MDEF(KEY_PERIOD);
        }
        ACMAP(KEY_P) {
            ON_MODE(fnMode, KEY_MEDIA_PLAY_PAUSE);
            ON_MDEF(KEY_P)
        }
        ACMAP(KEY_M) {
            ON_MODE(fnMode, KEY_MEDIA_MUTE);
            ON_MDEF(KEY_M)
        }

        ACMAP(KEY_U) {
            ON_MODE(fnMode, KEY_PAGE_UP);
            ON_MDEF(KEY_U);
        }
        ACMAP(KEY_D) {
            ON_MODE(fnMode, KEY_PAGE_DOWN);
            ON_MDEF(KEY_D);
        }

        default:
            return key;
    }
}

void handleKeyEvent(unsigned value) {
    bool isRelease = value >= 128;
    if (isRelease)
        value -= 128;

    if (value >= totalKeys)
        return;

    const unsigned ckey = remap(getKey(value), isRelease);
    if (ckey == 0)
        return;

    if (isModifier(ckey)) {
        if (isRelease)
            modKeyRel(ckey);
        else
            modKeyPress(ckey);
    } else {
        if (isRelease)
            clearKey(ckey);
        else
            setOpenKey(ckey);
    }
}

void interrupt() {
    enum { BIT_START = 255, BIT_END = 8 };
    static uint8_t state = BIT_START;
    static unsigned keyCode = 0;   // Raw XT scancode
    static unsigned lastCode = 0;  // Used to ignore internal key repeating

    auto rbit = digitalRead(DATA_PIN);
    if (state == BIT_START && !rbit) {
        return;
    } else {
        if (state != BIT_START) {
            keyCode |= (rbit << state);
        }
        ++state;

        if (state == BIT_END) {
            if (keyCode != lastCode) {
                handleKeyEvent(keyCode);
                lastCode = keyCode;
            }

            keyCode = 0;
            state = BIT_START;
        }
    }
}

void loop() {}

