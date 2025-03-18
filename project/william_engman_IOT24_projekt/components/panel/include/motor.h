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
    bool on = false;
    int pin;

    public:
    void init(int transistor, int h_bridge);
    void update(int light_left, int light_right, int btn_left, int btn_right);
    void rotation(int mode);
};

#endif