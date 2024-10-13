#include <Arduino.h>
#include <XButton.h>

const int BUTTON_PIN = 25;
XButton button(BUTTON_PIN);

void onButtonPress();
void onButtonHold();
void onButtonRelease();
void onButtonSingleClick();
void onButtonSingleLongClick();
void onButtonSingleShortClick();
void onButtonDoubleClick();


void setup() {
    Serial.begin(115200);

    button.setup();
    button.debug(false);
    button.setOnPressCallback(onButtonPress);
    button.setOnHoldCallback(onButtonHold);
    button.setOnReleaseCallback(onButtonRelease);
    button.setOnSingleClickCallback(onButtonSingleClick);
    button.setOnSingleLongClickCallback(onButtonSingleLongClick);
    button.setOnSingleShortClickCallback(onButtonSingleShortClick);
    button.setOnDoubleClickCallback(onButtonDoubleClick);
}

void loop() {
    button.loop();
    delay(50);
}

void onButtonPress() {
    Serial.println("Main loop: Button pressed");
}

void onButtonHold() {
    Serial.println("Main loop: Button held");
}

void onButtonRelease() {
    Serial.println("Main loop: Button released");
}

void onButtonSingleClick() {
    Serial.println("Main loop: Button single clicked");
}

void onButtonSingleLongClick() {
    Serial.println("Main loop: Button single long clicked");
}

void onButtonSingleShortClick() {
    Serial.println("Main loop: Button single short clicked");
}

void onButtonDoubleClick() {
    Serial.println("Main loop: Button double clicked");
}

