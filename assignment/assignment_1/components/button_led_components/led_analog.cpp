#include "led_analog.h"


void LedAnalog::init(int pin) 
{
    ledc_timer_config_t led_timer =
    {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_12_BIT,
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

    this->normal_duty = ledc_find_suitable_duty_resolution(LEDC_AUTO_CLK, 4000) / 2;
}

void LedAnalog::update()
{
    int current_time = (int)xTaskGetTickCount;
    int current_duty = settLed(current_time) * this->normal_duty;

    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty, 0);
}

double LedAnalog::settLed(int value)
{
    //call on sin func with
    return sin(this->sin_period * value) + 1;
}

void LedAnalog::settSin(double period)
{
    this->sin_period = period;
}