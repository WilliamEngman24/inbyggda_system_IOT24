#pragma once

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

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

    public:
    void init(adc_channel_t adc);

    void update(adc_channel_t adc);

    int getValue(adc_channel_t adc);

    void setOnThreshold(int threshold, bool risingEdge, void(*onThreshhold)(adc_channel_t adc, int value));
};

#endif 