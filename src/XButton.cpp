// change the counter to use millis instead
#include "XButton.h"

XButton::XButton(int buttonPin, int mode, int threshold)
    : _BUTTON_PIN(buttonPin), _MODE(mode), _THRESHOLD(threshold) {}

void XButton::setup() {
    Serial.begin(115200);
    pinMode(_BUTTON_PIN, _MODE);
}

void XButton::debug(bool enable) {
    _debugEnabled = enable;
}

void XButton::_debugPrint(const char* message) {
    if (_debugEnabled) {
        Serial.println(message);
    }
}

void XButton::_debugPrint(const char* message, int value) {
    if (_debugEnabled) {
        Serial.print(message);
        Serial.println(value);
    }
}

void XButton::loop() {
    unsigned long currentTime = millis();

    // Check for clicks
    if (currentTime - _lastClickTime > _click_time) {
        if (_counterClicked > 0) {
            _processClicks();
        }
        _counterClicked = 0;
        _lastClickTime = currentTime;
    }

    bool buttonPressed = digitalRead(_BUTTON_PIN) == LOW;
    unsigned long stateDuration = currentTime - (buttonPressed ? _pressStartTime : _releaseStartTime);

    switch (_currentState) {
        case State::IDLE:
            if (buttonPressed && stateDuration > _THRESHOLD) {
                _currentState = State::PRESSED;
                _pressStartTime = currentTime;
                _debugPrint("Button pressed!");
                if (_onPressCallback) _onPressCallback();
            }
            break;

        case State::PRESSED:
            if (stateDuration > _pressed_hold_time) {
                _currentState = State::HOLDING;
                _debugPrint("Button holding!");
                if (_onHoldCallback) _onHoldCallback();
            } else if (!buttonPressed && stateDuration > _THRESHOLD) {
                _currentState = State::RELEASED;
                _releaseStartTime = currentTime;
                _debugPrint("Button released!");
                if (_onReleaseCallback) _onReleaseCallback();
            }
            break;

        case State::HOLDING:
            _isHolding = true;
            if (!buttonPressed && stateDuration > _THRESHOLD) {
                _currentState = State::RELEASED;
                _releaseStartTime = currentTime;
                _debugPrint("Button released!");
                if (_onReleaseCallback) _onReleaseCallback();
            }
            break;

        case State::RELEASED:
            if (stateDuration > _THRESHOLD) {
                _currentState = State::IDLE;
                _counterClicked++;
            }
            break;
    }

    if (buttonPressed) {
        _pressStartTime = currentTime;
    } else {
        _releaseStartTime = currentTime;
    }
}

void XButton::_processClicks() {
    if (_counterClicked == 1) {
        _debugPrint("Single click detected!");
        if (_onSingleClickCallback) _onSingleClickCallback();

        if (_isHolding) {
            _debugPrint("Single Long Click detected!");
            if (_onSingleLongClickCallback) _onSingleLongClickCallback();
        } else {
            _debugPrint("Single Short Click detected!");
            if (_onSingleShortClickCallback) _onSingleShortClickCallback();
        }

    } else if (_counterClicked == 2) {
        _debugPrint("Double click detected!");
        if (_onDoubleClickCallback) _onDoubleClickCallback();
    } else if (_counterClicked >= 3) {
        _debugPrint("Multiple clicks detected: ", _counterClicked);
        if (_onTripleClickCallback) _onTripleClickCallback();
    }

    _isHolding = false;
}

XButton::State XButton::getCurrentState() const {
    return _currentState;
}

void XButton::setOnPressCallback(void (*callback)()) {
    _onPressCallback = callback;
}

void XButton::setOnHoldCallback(void (*callback)()) {
    _onHoldCallback = callback;
}

void XButton::setOnReleaseCallback(void (*callback)()) {
    _onReleaseCallback = callback;
}

void XButton::setOnSingleClickCallback(void (*callback)()) {
    _onSingleClickCallback = callback;
}

void XButton::setOnDoubleClickCallback(void (*callback)()) {
    _onDoubleClickCallback = callback;
}

void XButton::setOnTripleClickCallback(void (*callback)()) {
    _onTripleClickCallback = callback;
}

void XButton::setOnSingleLongClickCallback(void (*callback)()) {
    _onSingleLongClickCallback = callback;
}

void XButton::setOnSingleShortClickCallback(void (*callback)()) {
    _onSingleShortClickCallback = callback;
}

void XButton::setPressedHoldTime(unsigned int milliseconds) {
    _pressed_hold_time = milliseconds;
}

void XButton::setClickTime(unsigned int milliseconds) {
    _click_time = milliseconds;
}