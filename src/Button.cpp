#include <Arduino.h>
#include "Button.h"

Button::Button(uint8_t pin, boolean pullup): Button(pin, SIMPLE, pullup) {}

Button::Button(uint8_t pin, types type, boolean pullup) {
  _pin = pin;
  _block_time = 0;
  _type = type;
  _last_option = NONE;
  if (_type == SIMPLE) {
    _invert = false;
    if (pullup) {
      pinMode(_pin, INPUT_PULLUP);
      _invert = true;      
    } else {
      pinMode(_pin, INPUT);
    }
    _last_state = getRawValue();
  } 
}

int Button::getRawValue() {
  if (_type == LCD_KEYPAD) {
    return analogRead(_pin);
  }
  return _invert ? !digitalRead(_pin) : digitalRead(_pin);
}

options Button::getRawOption() {
  if (_type == LCD_KEYPAD) {
    int rawValue = getRawValue();
    if (rawValue > OPTION_TRESHOLD_NONE) return NONE;
    if (rawValue < OPTION_TRESHOLD_RIGHT) return RIGHT;
    if (rawValue < OPTION_TRESHOLD_UP) return UP;
    if (rawValue < OPTION_TRESHOLD_DOWN) return DOWN;
    if (rawValue < OPTION_TRESHOLD_LEFT) return LEFT;
    if (rawValue < OPTION_TRESHOLD_SELECT) return SELECT;
    return NONE;
  }
  return NONE;
}

String Button::getStringValue(options option) {
  if (option == RIGHT) return "RIGHT";
  if (option == UP) return "UP";
  if (option == DOWN) return "DOWN";
  if (option == LEFT) return "LEFT";
  if (option == SELECT) return "SELECT";
  return "";
}

options Button::getOption(uint16_t block_delay, uint16_t repeat_delay) {
  if (_type == SIMPLE) return NONE;
  if (millis() < _block_time) return NONE;
  options current = getRawOption();
  if (current != NONE) {
    _block_time = millis() + (current == _last_option ? repeat_delay : block_delay);
  }
  _last_option = current;
  return current;
}

int Button::getStatus(uint16_t block_delay, uint16_t repeat_delay) {
  if (_type == LCD_KEYPAD) return NONE;
  if (millis() < _block_time) return NONE;
  int current = getRawValue();
  if (current != NONE) {
    _block_time = millis() + (current == _last_state ? repeat_delay : block_delay);
  }
  _last_state = current;
  return current;
}
