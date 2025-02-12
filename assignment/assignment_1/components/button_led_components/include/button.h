#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
class Button 
{
private:
    int latch = 0;
    bool isPullDown = false;
    void (*function)(void);
    TickType_t last_pressed;

public:

    void init(int pin, bool isPullDown);

    void update(gpio_num_t pin);

    bool isPressed(bool update);

    void setOnPressed(void(*onPresseed)(void));

};

#endif 