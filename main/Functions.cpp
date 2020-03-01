#include "Functions.h"

#include <Arduino.h>
#include <Keyboard.h>

#include "Command.h"

#ifdef __cplusplus
extern "C" {
#endif

void serial_print_str(char const* string) {
    Serial.print(string);
}
void serial_print_int(int string) {
    Serial.print(string);
}

#ifdef __cplusplus
}
#endif
