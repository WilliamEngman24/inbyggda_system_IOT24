#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
class Button 
{
private:
    bool latch = false;
    bool isPullDown = false;
    void (*function)(void);
    TickType_t last_pressed;

    int button_state = 0;

public:

    void init(int pin, bool isPullDown);

    void update(gpio_num_t pin);

    bool isPressed(bool update);

    void setOnPressed(void(*onPresseed)(void));

};

#endif 