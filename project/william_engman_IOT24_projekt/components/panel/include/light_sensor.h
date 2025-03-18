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

    int value = 0;
    
    //filter
    std::list<int> values;
    int counter;

    public:
    int getValue();
    
    void init(adc_channel_t adc);

    void update();

    int processedInfo();
};

#endif 
