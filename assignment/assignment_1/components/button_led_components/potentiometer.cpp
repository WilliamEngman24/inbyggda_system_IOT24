#include <iostream>
#include "potentiometer.h"

using namespace std;

void Potentiometer::init(adc_channel_t adc)
{
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = 
    {
        .unit_id = ADC_UNIT_1,
        .clk_src = (adc_oneshot_clk_src_t)0,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = 
    {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, adc, &config));

    this->handle = adc1_handle;
}

void Potentiometer::update(adc_channel_t adc)
{
    int value = getValue(adc);

    if (this->risingEdge) 
    {
        if (value > this->threshold) 
        {
            if (!this->isOverThreshold) 
            {
                this->function(adc, value);
                this->isOverThreshold = true;
            }
        }
        else
        {
            this->isOverThreshold = false;
        }
    }
    else 
    {
        if(value < this->threshold) 
        {
            if (!this->isOverThreshold) 
            {
                this->function(adc, value);
                this->isOverThreshold = true;
            }
        }
        else 
        {
            this->isOverThreshold = false;
        }
    }
    
}

int Potentiometer::getValue(adc_channel_t adc)
{
    int value;

    ESP_ERROR_CHECK(adc_oneshot_read(this->handle, adc, &value));

    return value;
}

void Potentiometer::setOnThreshold(int threshold, bool risingEdge, void(*onThreshold)(adc_channel_t adc, int value))
{
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->function = *onThreshold;
}