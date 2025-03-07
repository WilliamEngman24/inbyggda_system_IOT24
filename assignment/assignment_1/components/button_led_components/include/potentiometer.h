#pragma once

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <list>

#include "driver/gpio.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

class Potentiometer 
{
    private:
    void (*function)(adc_channel_t adc, int value);
    adc_oneshot_unit_handle_t handle;
    int threshold;
    bool risingEdge;
    bool isOverThreshold;

    int value;

    adc_channel_t adc;

    std::list<int> values;
    int counter;

    public:
    void init(adc_channel_t adc);

    void update();

    int getValue();

    void setOnThreshold(int threshold, bool risingEdge, void(*onThreshhold)(adc_channel_t adc, int value));
};

#endif 