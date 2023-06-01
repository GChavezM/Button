#include <Arduino.h>
#include "Button.h"

Button button(43);

void heartbeat();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    // button.setDebounceTime(1000);
}

void loop() {
    button.loop();
    if (button.isPressed()) {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    if (button.isReleased()) {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
