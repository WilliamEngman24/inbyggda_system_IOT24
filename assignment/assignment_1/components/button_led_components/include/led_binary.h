#pragma once

#ifndef LED_BINARY_H
#define LED_BINARY_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

class LedBinary
{
    private:
    TickType_t on_timer;
    TickType_t off_timer;

    int milli_on;
    int milli_off;

    bool on;

    public:
    void init(int pin);

    void update(int pin);

    void settLed(int pin, bool state);

    void blink(int on, int off);
};

#endif 