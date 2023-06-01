#include <Arduino.h>
#include "Button.h"

Button::Button(uint8_t pin, boolean pullup, boolean invert): _pin(pin), _invert(invert) {
  _debounceTime = 50;
  if (pullup) {
    _invert = !invert;
    pinMode(pin, INPUT_PULLUP);
  } else {
    pinMode(pin, INPUT);
  }
  _lastReading = getRawValue();
  _lastState = _lastReading;
  _state = _lastState;
  _lastTime = millis();
  _pressedTime = _lastTime;
  _isLongPressing = false;
}

void Button::setDebounceTime(unsigned long time) {
  _debounceTime = time;
}

int Button::getRawValue() {
  return _invert ? !digitalRead(_pin) : digitalRead(_pin);
}

int Button::getValue() {
  return _state;
}

bool Button::isPressed() {
  if (_lastState == LOW && _state == HIGH) {
    return true;
  }
  return false;
}

bool Button::isReleased() {
  if (_lastState == HIGH && _state == LOW) {
    return true;
  }
  return false;
}

bool Button::isLongPressed(unsigned long time) {
  if (_isLongPressing && _pressDuration > time) {
    _isLongPressing = false;
    return true;
  }
  return false;
}

void Button::loop() {
  int reading = getRawValue();
  unsigned long currentTime = millis();
  if (reading != _lastReading) {
    _lastTime = currentTime;
    _lastReading = reading;
  }
  if ((currentTime - _lastTime) >= _debounceTime) {
    _lastState = _state;
    _state = reading;
  }
  if (isPressed()) {
    _pressedTime = currentTime;
  }
  if (isReleased()) {
    _releasedTime = currentTime;
    _pressDuration = _releasedTime - _pressedTime;
    _isLongPressing = true;
  }
}

ButtonLCD::ButtonLCD(uint8_t pin): _pin(pin) {
  _debounceTime = 50;
  _lastReading = _getRawOption();
  _lastState = _lastReading;
  _state = _lastState;
  _lastTime = millis();
}

void ButtonLCD::setDebounceTime(unsigned long time) {
  _debounceTime = time;
}

int ButtonLCD::_getRawValue() {
  return analogRead(_pin);
}

option ButtonLCD::_getRawOption() {
  int rawValue = _getRawValue();
  if (rawValue > OPTION_TRESHOLD_NONE) return NONE;
  if (rawValue < OPTION_TRESHOLD_RIGHT) return RIGHT;
  if (rawValue < OPTION_TRESHOLD_UP) return UP;
  if (rawValue < OPTION_TRESHOLD_DOWN) return DOWN;
  if (rawValue < OPTION_TRESHOLD_LEFT) return LEFT;
  if (rawValue < OPTION_TRESHOLD_SELECT) return SELECT;
  return NONE;
}

String ButtonLCD::getStringOption() {
  option value = getOption();
  if (value == RIGHT) return "RIGHT";
  if (value == UP) return "UP";
  if (value == DOWN) return "DOWN";
  if (value == LEFT) return "LEFT";
  if (value == SELECT) return "SELECT";
  return "NONE";
}

option ButtonLCD::getOption() {
  if (_lastState == NONE && _state != NONE) {
    return _state;
  }
  return NONE;
}

void ButtonLCD::loop() {
  option reading = _getRawOption();
  unsigned long currentTime = millis();
  if (reading != _lastReading) {
    _lastTime = currentTime;
    _lastReading = reading;
  }
  if ((currentTime - _lastTime) >= _debounceTime) {
    _lastState = _state;
    _state = reading;
  }
}
