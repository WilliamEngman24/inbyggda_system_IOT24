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
    int button_state = 0;

    TickType_t last_pressed;

    bool latch = false;
    bool isPullDown = false;
    bool level;

    void (*function)(void) = NULL;

    void settPressed(int level);

public:

    bool getPressed();

    void init(int pin, bool isPullDown);

    void update();

    bool isPressed();

    void setOnPressed(void(*onPresseed)(void));

};

#endif 