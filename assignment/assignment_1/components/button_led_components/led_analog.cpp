#include "led_analog.h"

#include <iostream>

#define RES 0b111111111111

void LedAnalog::init(int pin) 
{
    ledc_timer_config_t led_timer =
    {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 4000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&led_timer);
    
    
    ledc_channel_config_t led_channel = 
    {
        .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&led_channel);

    this->amp_or_vertical_shift = RES;
}

void LedAnalog::update()
{
    if (this->mode == 0) 
    {
        settLed(this->current_duty);
    }
    else 
    {
        settSin(this->period); //sends time to the setting of the led
    }
}

void LedAnalog::settLed(double duty)//takes constant duty time and mode
{
    this->mode = 0;
    this->current_duty = duty;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty); //setts the duty to mimic sine curve at whatever x value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    
}

void LedAnalog::settSin(double period) // takes milliseconds
{
    if (period == 0) 
    {
        period = 1000;
    }
    this->period = period;

    this->mode = 1;

    double current_time = (double)xTaskGetTickCount() / (double)100.00; //takes current time and turns into seconds

    this->current_duty = this->amp_or_vertical_shift * sin(((1000 / period) * M_PI * 2) * current_time) + this->amp_or_vertical_shift; // A * sin(priod * time) + vertical shift
    std::cout << this->current_duty << " " << current_time <<std::endl;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, this->current_duty); //setts the duty to mimic sine curve at whatever x value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}