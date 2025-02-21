#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
class Button 
{
private:
    int pin;
    bool latch = false;
    bool isPullDown = false;
    void (*function)(void) = NULL;
    TickType_t last_pressed;

    int counter = 1;

    int button_state = 0;

    void settPressed(int level);

public:

    int getPressed();

    void init(int pin, bool isPullDown);

    void update();

    bool isPressed(bool update);

    void setOnPressed(void(*onPresseed)(void));

};

#endif 