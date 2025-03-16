#include <stdio.h>
#include "light_sensor.h"

void LightSensor::init(adc_channel_t adc)
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

void LightSensor::update()
{
    int value = getValue();

    if(value != -1) //if enough values have been collected 
    {
        this->value = value;
        //this->function(adc, value);
    }
}

int LightSensor::getValue()
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
