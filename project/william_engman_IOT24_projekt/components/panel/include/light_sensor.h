#pragma once

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <list>

#include "driver/gpio.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"

#define FILTER 10

class LightSensor
{
    private:
    //void (*function)(adc_channel_t adc, int value);
    adc_channel_t adc;
    adc_oneshot_unit_handle_t handle;

    int value;
    
    //filter
    std::list<int> values;
    int counter;

    public:
    void init(adc_channel_t adc);

    void update();

    int getValue();
};

#endif 
