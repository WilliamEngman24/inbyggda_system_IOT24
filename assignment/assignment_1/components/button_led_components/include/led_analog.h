#pragma once

#ifndef LED_ANALOG_H
#define LED_ANALOG_H

#include <cmath>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

class LedAnalog
{
    private:
    double sin_period;
    int normal_duty;

    public:
    void init(int pin);

    void update();

    double settLed(int value);

    void settSin(double period);
};

#endif 