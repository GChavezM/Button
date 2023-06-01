#include <Arduino.h>
#include "Button.h"

ButtonLCD button(A0);

void setup() {
    Serial.begin(9600);
    Serial.println();
    pinMode(LED_BUILTIN, OUTPUT);
    // button.setDebounceTime(1000);
}

void loop() {
    if (button.getOption()) {
        Serial.println(button.getStringOption());
        if (button.getOption() == UP) {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        if (button.getOption() == DOWN) {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}
