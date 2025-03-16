#include <iostream>
#include "potentiometer.h"

#define FILTER 10
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
    this->adc = adc;
}

void Potentiometer::update()
{
    int value = getValue();

    if(value != -1) //if enough values have been collected
    {   

        //cout << value << endl;

        if (this->risingEdge) //if the function is supposed to react to when value goes OVER the threshold
        {
            if (value > this->threshold) //when does go over
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
    
}

int Potentiometer::getValue()
{
    int sum = 0;
    int value;
    ESP_ERROR_CHECK(adc_oneshot_read(this->handle, this->adc, &value));

    this->values.push_back(value);
    if ( this->values.size() == FILTER) 
    {
        for (int e : this->values) 
        {
            sum += e;
        }
        value = (sum / this->values.size()); //procure median

        this->values.clear();

        return value;
    }
    return -1;
}

void Potentiometer::setOnThreshold(int threshold, bool risingEdge, void(*onThreshold)(adc_channel_t adc, int value))
{
    this->threshold = threshold;
    this->risingEdge = risingEdge;
    this->function = *onThreshold;
}