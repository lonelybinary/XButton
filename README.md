# XButton

XButton is a versatile Arduino library for handling button inputs with advanced features such as debouncing, multiple click detection, and callback support.

## Features

- Easy to use with Arduino projects
- Supports various button states: IDLE, PRESSED, HOLDING, RELEASED
- Detects single, double, and triple clicks
- Distinguishes between short and long clicks
- Customizable hold time and click detection window
- Callback support for different button events
- Debug mode for easy troubleshooting

## Installation

1. Download the XButton library
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library
3. Choose the downloaded XButton library file
4. The library is now ready to use

## Usage

```cpp
#include <XButton.h>
// Create an XButton instance
XButton myButton(2); // Button connected to pin 2

void onSingleClick() {
// Handle single click event
}

void setup() {
    myButton.setup();
    myButton.setOnSingleClickCallback(onSingleClick);
}

void loop() {
    myButton.loop();
}
```

## Public Methods

### Constructor



```cpp
XButton(int buttonPin, int mode = INPUT, int threshold = 30)
```

- `buttonPin`: The pin number where the button is connected
- `mode`: Pin mode (INPUT or INPUT_PULLUP)
- `threshold`: Debounce threshold in milliseconds

### Basic Methods

```cpp
void setup()
```
Initializes the button. Call this in your `setup()` function.

```cpp
void loop()
```

Handles button state updates. Call this in your `loop()` function.


```cpp
State getCurrentState() const
```

Returns the current state of the button.

### Callback Methods

```cpp
void setOnPressCallback(void (callback)())
void setOnHoldCallback(void (callback)())
void setOnReleaseCallback(void (callback)())
void setOnSingleClickCallback(void (callback)())
void setOnSingleLongClickCallback(void (callback)())
void setOnSingleShortClickCallback(void (callback)())
void setOnDoubleClickCallback(void (callback)())
void setOnTripleClickCallback(void (callback)())
```

Set callbacks for different button events.

### Customization

```cpp
void setPressedHoldTime(unsigned int milliseconds)
```

Sets the duration (in milliseconds) required for a press to be considered a "hold".

```cpp
void setClickTime(unsigned int milliseconds)
```

Sets the duration (in milliseconds) required for a press to be considered a "click".

### Debug Mode

```cpp
void debug(bool enable)
```

Enables or disables debug mode, which prints button events to the Serial monitor.

## Example

```cpp
#include <XButton.h>

XButton myButton(2);

void onSingleClick() {
    Serial.println("Single click detected!");
}
void onDoubleClick() {
    Serial.println("Double click detected!");
}
void onHold() {
    Serial.println("Button is being held!");
}

void setup() {
    Serial.begin(115200);
    myButton.setup();
    myButton.setOnSingleClickCallback(onSingleClick);
    myButton.setOnDoubleClickCallback(onDoubleClick);
    myButton.setOnHoldCallback(onHold);
}

void loop() {
    myButton.loop();
}


```

## License

MIT License

Copyright (c) 2024 Lonely Binary

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
