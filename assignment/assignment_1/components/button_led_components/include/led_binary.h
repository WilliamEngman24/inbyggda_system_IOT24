#pragma once

#ifndef LED_BINARY_H
#define LED_BINARY_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


//#include "driver/ledc.h"

class LedBinary
{
    private:
    double on_timer;
    double off_timer;

    double milli_on;
    double milli_off;

    bool on;

    public:
    void init(int pin);

    void update(int pin);

    void settLed(int pin, bool state);

    void blink(double on, double off);
};

#endif 