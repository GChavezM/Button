#ifndef Button_h
#define Button_h

enum option {
  NONE,
  RIGHT,  
  UP,
  DOWN,
  LEFT,
  SELECT,
};

constexpr int OPTION_TRESHOLD_NONE{1000};
constexpr int OPTION_TRESHOLD_RIGHT{60};
constexpr int OPTION_TRESHOLD_UP{200};
constexpr int OPTION_TRESHOLD_DOWN{400};
constexpr int OPTION_TRESHOLD_LEFT{600};
constexpr int OPTION_TRESHOLD_SELECT{800};

class Button {
  public:
    Button(uint8_t pin, boolean pullup = true, boolean invert = false);
    void setDebounceTime(unsigned long time);
    int getRawValue();
    int getValue();
    bool isPressed();
    bool isReleased();
    bool isLongPressed(unsigned long time = 1000);
    void loop();

  private:
    uint8_t _pin;
    uint8_t _invert;
    uint8_t _lastReading;
    uint8_t _lastState;
    uint8_t _state;
    bool _isLongPressing;
    bool _isPressing;
    unsigned long _debounceTime;
    unsigned long _lastTime;
    unsigned long _pressedTime;
    unsigned long _releasedTime;
    unsigned long _pressDuration;
};

class ButtonLCD {
  public:
    ButtonLCD(uint8_t pin);
    void setDebounceTime(unsigned long time);
    option getOption();
    String getStringOption();
    option getValue();
    void loop();
  private:
    uint8_t _pin;
    option _lastReading;
    option _lastState;
    option _state;
    unsigned long _debounceTime;
    unsigned long _lastTime;
    int _getRawValue();
    option _getRawOption();
};

#endif
