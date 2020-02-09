/* Copyright (C) 2016 Armando L. Montanez 
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
 
// Please note:
// One thing I learned is that, for some reason, you can't do
// statements like "if (target == KEY_Q)"
// You'll notice that instead I compare directly with the raw
// value of that respective key.
// EG, use
//    if (target == 83)
// Instead of
//    if (target == KEY_NUM_LOCK)
// Otherwise, the statement will always result in FALSE!

 
 
// I/O pins used
const int CLK_Pin = 2;       // Feel free to make this any unused digital pin (must be 5v tolerant!)
const int DATA_Pin = 1;      // Feel free to make this any unused digital pin (must be 5v tolerant!)
const int LED_Pin = 11;      // the number of the LED pin (for NumLock)


// Array tracks keys currently being held
uint8_t keysHeld[6] = {0, 0, 0, 0, 0, 0}; // 6 keys max


// global variables, track Ctrl, Shift, Alt, Gui (Windows), and NumLock key statuses.
int modifiers = 0;            // 1=c, 2=s, 3=sc, 4=a, 5=ac, 6=as, 7=asc, 8=g, 9=gc...
bool numLock = 0;              // so you have F11, F12, and the windows key (F8 when numlock is on)
bool astMode = 0;
bool fnMode = 0;

// variables utilized in main loop for reading data
int cycleReadYet = 0;        // was data read for this cycle?
int scanCode = 0;            // Raw XT scancode
int lastScanCode = 0;        // Used to ignore internal key repeating
int numBits = 0;             // How many bits of the scancode have been read?
int sigStart = 0;            // Used to bypass the first clock cycle of a scancode
int temp = 0;                // used to bitshift the read bit
int readCode = 0;            // 1 means we're being sent a scancode

enum FKeyCode {
	F_KEY_TILDE = 1,
	F_KEY_1,
	F_KEY_2,
	F_KEY_3,
	F_KEY_4,
	F_KEY_5,
	F_KEY_6,
	F_KEY_7,
	F_KEY_8,
	F_KEY_9,
	F_KEY_0,
	F_KEY_MINUS,
	F_KEY_EQUAL,
	F_KEY_BACKSPACE,
	F_KEY_TAB,
	F_KEY_Q,
	F_KEY_W,
	F_KEY_E,
	F_KEY_R,
	F_KEY_T,
	F_KEY_Y,
	F_KEY_U,
	F_KEY_I,
	F_KEY_O,
	F_KEY_P,
	F_KEY_LEFT_BRACE,
	F_KEY_RIGHT_BRACE,
	F_KEY_ENTER,
	F_MODIFIERKEY_CTRL,
	F_KEY_A,
	F_KEY_S,
	F_KEY_D,
	F_KEY_F,
	F_KEY_G,
	F_KEY_H,
	F_KEY_J,
	F_KEY_K,
	F_KEY_L,
	F_KEY_SEMICOLON,
	F_KEY_QUOTE,
	F_KEY_ESC,
	F_MODIFIERKEY_LSHIFT,
	F_KEY_BACKSLASH,
	F_KEY_Z,
	F_KEY_X,
	F_KEY_C,
	F_KEY_V,
	F_KEY_B,
	F_KEY_N,
	F_KEY_M,
	F_KEY_COMMA,
	F_KEY_PERIOD,
	F_KEY_SLASH,
	F_MODIFIERKEY_RSHIFT,
	F_KEYPAD_ASTERIX,
	F_MODIFIERKEY_ALT,
	F_KEY_SPACE,
	F_KEY_CAPS_LOCK,
	F_KEY_F1,
	F_KEY_F2,
	F_KEY_F3,
	F_KEY_F4,
	F_KEY_F5,
	F_KEY_F6,
	F_KEY_F7,
	F_KEY_F8,
	F_KEY_F9,
	F_KEY_F10,
	F_KEY_NUM_LOCK,
	F_KEY_SCROLL_LOCK,
	F_KEYPAD_7,
	F_KEYPAD_8,
	F_KEYPAD_9,
	F_KEYPAD_MINUS,
	F_KEYPAD_4,
	F_KEYPAD_5,
	F_KEYPAD_6,
	F_KEYPAD_PLUS,
	F_KEYPAD_1,
	F_KEYPAD_2,
	F_KEYPAD_3,
	F_KEYPAD_0,
	F_KEYPAD_PERIOD,
	F_KEYS_TOTAL
};

unsigned const gModelFMap[] = {
	0,
	KEY_TILDE,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_LEFT_BRACE,
	KEY_RIGHT_BRACE,
	KEY_ENTER,
	MODIFIERKEY_CTRL,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_SEMICOLON,
	KEY_QUOTE,
	KEY_ESC,
	MODIFIERKEY_SHIFT,
	KEY_BACKSLASH,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	MODIFIERKEY_RIGHT_SHIFT,
	KEYPAD_ASTERIX,
	MODIFIERKEY_ALT,
	KEY_SPACE,
	KEY_CAPS_LOCK,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_NUM_LOCK,
	KEY_SCROLL_LOCK,
	KEYPAD_7,
	KEYPAD_8,
	KEYPAD_9,
	KEYPAD_MINUS,
	KEYPAD_4,
	KEYPAD_5,
	KEYPAD_6,
	KEYPAD_PLUS,
	KEYPAD_1,
	KEYPAD_2,
	KEYPAD_3,
	KEYPAD_0,
	KEYPAD_PERIOD
};


void setup() {
  pinMode(CLK_Pin, INPUT); 
  pinMode(DATA_Pin, INPUT);
  pinMode(LED_Pin, OUTPUT);    // LED is on when NumLock is enabled
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
	if(isMediaKey(target)) {
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
	if(isMediaKey(target)) {
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
	switch(modkey) {
		case MODIFIERKEY_SHIFT:
		case MODIFIERKEY_RIGHT_SHIFT:
		case MODIFIERKEY_CTRL:
		case MODIFIERKEY_RIGHT_CTRL:
		case MODIFIERKEY_ALT:
		case MODIFIERKEY_RIGHT_ALT:
		case MODIFIERKEY_GUI:
		case MODIFIERKEY_RIGHT_GUI:
			return true;
		default: return false;
	}
}

unsigned remap(unsigned key, bool isRelease) {
#define REMAP(BASE_KEY, TARGET_KEY) case BASE_KEY: return TARGET_KEY
#define ACMAP(BASE_KEY) case BASE_KEY:
#define ON_MODE(MODE, KEY) if(MODE) return KEY;
#define ON_MDEF(KEY)       return KEY;
	switch(key) {
		REMAP(MODIFIERKEY_ALT , MODIFIERKEY_CTRL);
		REMAP(MODIFIERKEY_CTRL, KEY_ESC);
		REMAP(KEY_CAPS_LOCK   , MODIFIERKEY_RIGHT_ALT);
		ACMAP(KEY_SCROLL_LOCK){ if(astMode && fnMode) { _reboot_Teensyduino_(); return 0; }
														return KEY_PAUSE; }
		ACMAP(KEYPAD_ASTERIX) { astMode = !isRelease; return 0; }
		ACMAP(KEY_NUM_LOCK)   { if (!isRelease) numLock = !numLock;   return astMode ? 0 : KEY_NUM_LOCK; }
		ACMAP(KEY_F8)         { return numLock ? KEY_F8  : MODIFIERKEY_GUI; }
		ACMAP(KEY_F10)        { return numLock ? KEY_F10 : MODIFIERKEY_ALT; }
		ACMAP(KEY_ESC)        { fnMode = !isRelease; if(isRelease) { Keyboard.set_media(0); } return 0; }
		ACMAP(KEY_1)          { ON_MODE(fnMode, KEY_F1);
														ON_MDEF(KEY_1); }
		ACMAP(KEY_2)          { ON_MODE(fnMode, KEY_F2);
														ON_MDEF(KEY_2); }
		ACMAP(KEY_3)          { ON_MODE(fnMode, KEY_F3);
														ON_MDEF(KEY_3); }
		ACMAP(KEY_4)          { ON_MODE(fnMode, KEY_F4);
														ON_MDEF(KEY_4); }
		ACMAP(KEY_5)          { ON_MODE(fnMode, KEY_F5);
														ON_MDEF(KEY_5); }
		ACMAP(KEY_6)          { ON_MODE(fnMode, KEY_F6);
														ON_MDEF(KEY_6); }
		ACMAP(KEY_7)          { ON_MODE(fnMode, KEY_F7);
														ON_MDEF(KEY_7); }
		ACMAP(KEY_8)          { ON_MODE(fnMode, KEY_F8);
														ON_MDEF(KEY_8); }
		ACMAP(KEY_9)          { ON_MODE(fnMode, KEY_F9);
														ON_MDEF(KEY_9); }
		ACMAP(KEY_0)          { ON_MODE(fnMode, KEY_F10);
														ON_MDEF(KEY_0); }
		ACMAP(KEY_MINUS)      { ON_MODE(fnMode, KEY_F11);
														ON_MDEF(KEY_MINUS); }
		ACMAP(KEY_EQUAL)      { ON_MODE(fnMode, KEY_F12);
														ON_MDEF(KEY_EQUAL); }
		ACMAP(KEY_BACKSPACE)  { ON_MODE(fnMode, KEY_DELETE);
														ON_MDEF(        KEY_BACKSPACE); }
		ACMAP(KEY_H)          { ON_MODE(fnMode, KEY_LEFT);
														ON_MDEF(        KEY_H); }
		ACMAP(KEY_J)          { ON_MODE(fnMode, KEY_DOWN);
														ON_MDEF(        KEY_J); }
		ACMAP(KEY_K)          { ON_MODE(fnMode, KEY_UP);
														ON_MDEF(        KEY_K); }
		ACMAP(KEY_L)          { ON_MODE(fnMode, KEY_RIGHT);
														ON_MDEF(        KEY_L); }

		ACMAP(KEY_LEFT_BRACE) { ON_MODE(fnMode, KEY_MEDIA_VOLUME_DEC);
														ON_MDEF(        KEY_LEFT_BRACE); }
		ACMAP(KEY_RIGHT_BRACE){ ON_MODE(fnMode, KEY_MEDIA_VOLUME_INC);
														ON_MDEF(        KEY_RIGHT_BRACE); }
		ACMAP(KEY_COMMA)      { ON_MODE(fnMode, KEY_MEDIA_PREV_TRACK);
														ON_MDEF(        KEY_COMMA); }
		ACMAP(KEY_PERIOD)     { ON_MODE(fnMode, KEY_MEDIA_NEXT_TRACK);
														ON_MDEF(        KEY_PERIOD); }
		ACMAP(KEY_P)          { ON_MODE(fnMode, KEY_MEDIA_PLAY_PAUSE);
														ON_MDEF(        KEY_P) }
		ACMAP(KEY_M)          { ON_MODE(fnMode, KEY_MEDIA_MUTE);
														ON_MDEF(        KEY_M) }

		ACMAP(KEY_U)          { ON_MODE(fnMode, KEY_PAGE_UP);
														ON_MDEF(        KEY_U); }
		ACMAP(KEY_D)          { ON_MODE(fnMode, KEY_PAGE_DOWN);
														ON_MDEF(        KEY_D); }

		default: return key;
	}
}

// This function translates scan codes to proper key events
// First half are key presses, second half are key releases.
// setOpenKey()/clearKey() are used for siple keypresses (optimized)
// modKeyPress()/modKeyRel() are used for ctrl,shift,alt,windows (optimized)
// pressKey()/releaseKey() are used for keys that are potentially affected by NumLock (semi-optimized. buggy?)
void handleKeyEvent(unsigned value) {
	const unsigned numKeys = sizeof(gModelFMap) / sizeof(gModelFMap[0]);
	bool isRelease = value >= 128;
	if(isRelease)
		value -= 128;

	if(value >= numKeys)
		return;

	const unsigned ckey = remap(gModelFMap[value], isRelease);
	if(ckey == 0) 
		return;
	
	if (isModifier(ckey)) {
		if(isRelease) modKeyRel(ckey);
		else modKeyPress(ckey);
	} else {
		if(isRelease) clearKey(ckey);
		else setOpenKey(ckey);
	}
}


void loop() {
  // This catches a LOW in clock, signaling the start of a scan code 
  if (readCode == 0 && digitalRead(CLK_Pin) == 0) {
    readCode = 1;
  }
  
  // Note how numbits must be 9 instead of 8.
  // If we ignore the 9th pulse, it re-triggers readCode,
  // causing invalid scancodes.
  // The the 9th value should always be 0, so it 
  // shouldn't change the scan code.
  if (numBits == 9) {
    if (scanCode != lastScanCode) {
      handleKeyEvent(scanCode);    // Disable this line and enable the following line
			// Serial.println(scanCode);

      lastScanCode = scanCode;     // This is the magic that prevents key repeating.
    }
    // Reset all after successfully sending scanCode.
    sigStart = 0;
    scanCode = 0;
    numBits = 0;
    readCode = 0;
  }
  
  // since the code detects the rising edge of clock,
  // we use readCode to filter out the fact that
  // clock rests HIGH.
  if (readCode == 1) {
    // On each rising edge, get the respective DATA.
    // cycleReadYet prevents multiple reads on the same cycle.
    if (digitalRead(CLK_Pin) == 1 && cycleReadYet == 0) {
      
      // The first clock pulse signals the start of a scan code.
      // This means it has no relevant data.
      if (sigStart == 0){
        sigStart = 1;
      } else {
        // after the first cycle, read data.
        temp = digitalRead(DATA_Pin);
        temp = temp << numBits;
        scanCode = scanCode | temp;
        numBits++;
      }
      cycleReadYet = 1;
    }
    // once the clock drops again, we can reset cycleReadYet
    // since DATA is only read when clock is HIGH.
    if (digitalRead(CLK_Pin) == 0) {
      cycleReadYet = 0;
    }
  } 
}
