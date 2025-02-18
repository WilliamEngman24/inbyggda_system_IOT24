#include "led_analog.h"

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

    this->amp_or_vertical_shift = 0b111111111111;
}

void LedAnalog::update()
{
    double current_time = (double)xTaskGetTickCount() / (double)100.00;
    double current_duty = settLed(current_time);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, current_duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

double LedAnalog::settLed(int time)
{
    int period = this->sin_period * 3.14 * 2;

    return this->amp_or_vertical_shift * sin(period * time) + this->amp_or_vertical_shift;
}

void LedAnalog::settSin(double period)
{
    this->sin_period = period;
}