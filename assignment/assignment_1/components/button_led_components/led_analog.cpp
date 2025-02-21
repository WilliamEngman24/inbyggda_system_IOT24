#include "led_analog.h"

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
    double current_time = (double)xTaskGetTickCount() / (double)100.00; //takes current time and turns into seconds

    settLed(current_time); //sends time to the setting of the led
}

void LedAnalog::settLed(double time)
{
    this->current_duty = this->amp_or_vertical_shift * sin(this->period * time) + this->amp_or_vertical_shift; // A * sin(priod * time) + vertical shift

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, this->current_duty); //setts the duty to mimic sine curve at whatever x value
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void LedAnalog::settSin(double period) // takes milliseconds
{
    if (period == 0) 
    {
        period = 1000;
    }
    this->period = (1000 / period) * M_PI * 2;
}