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
    double amp_or_vertical_shift;
    double period;

    double current_duty;

    double mode;

    public:
    void init(int pin);

    void update();

    void settLed(double duty);

    void settSin(double period);
};

#endif 