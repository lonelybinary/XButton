#ifndef XBUTTON_H
#define XBUTTON_H

#include <Arduino.h>

class XButton {
public:
    enum class State {
        IDLE,
        PRESSED,
        HOLDING,
        RELEASED
    };

    XButton(int buttonPin, int mode = INPUT, int threshold = 30);
    void setup();
    void loop();
    State getCurrentState() const;

    // Add these new method declarations
    void setOnPressCallback(void (*callback)());
    void setOnHoldCallback(void (*callback)());
    void setOnReleaseCallback(void (*callback)());

    void setOnSingleClickCallback(void (*callback)());
    void setOnSingleLongClickCallback(void (*callback)());
    void setOnSingleShortClickCallback(void (*callback)());
    void setOnDoubleClickCallback(void (*callback)());
    void setOnTripleClickCallback(void (*callback)());

    void setPressedHoldTime(unsigned int milliseconds);
    void setClickTime(unsigned int milliseconds);

    void debug(bool enable);

private:
    void _processClicks();

    const int _BUTTON_PIN;
    const int _THRESHOLD;
    const int _MODE;
    int _counterClicked = 0;

    bool _isHolding = false;

    unsigned int _pressed_hold_time = 500;
    unsigned int _click_time = 1000;

    unsigned long _pressStartTime = 0;
    unsigned long _releaseStartTime = 0;
    unsigned long _lastClickTime = 0;

    State _currentState = State::IDLE;

    // Add these new private members
    void (*_onPressCallback)() = nullptr;
    void (*_onHoldCallback)() = nullptr;
    void (*_onReleaseCallback)() = nullptr;
    void (*_onSingleClickCallback)() = nullptr;
    void (*_onSingleLongClickCallback)() = nullptr;
    void (*_onSingleShortClickCallback)() = nullptr;
    void (*_onDoubleClickCallback)() = nullptr;
    void (*_onTripleClickCallback)() = nullptr;

    bool _debugEnabled = true;
    void _debugPrint(const char* message);
    void _debugPrint(const char* message, int value);
};

#endif // XBUTTON_H
