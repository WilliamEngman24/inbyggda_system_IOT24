#pragma once

#ifndef MOTOR_H
#define MOTOR_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

class Motor 
{
    private:
    public:
    void init(int pin);
    void update(int left_light, int right_light);
};

#endif