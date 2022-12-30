#ifndef Button_h
#define Button_h

#include <Arduino.h>
#include <inttypes.h>

enum types {
  SIMPLE,
  ANALOG
};

enum options {
  NONE,
  RIGHT,
  UP,
  DOWN,
  LEFT,
  SELECT
};

#define OPTION_TRESHOLD_NONE    1000
#define OPTION_TRESHOLD_RIGHT   60
#define OPTION_TRESHOLD_UP      200
#define OPTION_TRESHOLD_DOWN    400
#define OPTION_TRESHOLD_LEFT    600
#define OPTION_TRESHOLD_SELECT  800

class Button {
  public:
    Button(uint8_t pin, boolean pullup);
    Button(uint8_t pin, types type = SIMPLE, boolean pullup = true);

    int getRawValue();
    options getRawOption();
    String getStringValue();
    options getOption(uint16_t block_delay = 500,  uint16_t repeat_delay = 300);
    int getStatus(uint16_t block_delay = 500, uint16_t repeat_delay = 300);

  private:
    uint8_t _pin;
    uint32_t _block_time;
    types _type;
    options _last_option;
    boolean _invert;
    int _last_state;


};

#endif
