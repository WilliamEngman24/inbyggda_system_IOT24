#include "led_binary.h"

void LedBinary::init(int pin) 
{
    //inte pwm, slås av eller då
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
}

void LedBinary::update(int pin)
{
    //blink in here
    if (this->on) 
    {
        if (xTaskGetTickCount() - this->on_timer > this->milli_on) 
        {
            this->on = false;
            this->off_timer = xTaskGetTickCount();
        }
    }
    else 
    {
        if (xTaskGetTickCount() - this->off_timer > this->milli_off) 
        {
            this->on = true;
            this->on_timer = xTaskGetTickCount();
        }
    }

    settLed(pin, this->on);
}

void LedBinary::settLed(int pin, bool state) // on  and off
{
    int duty = 0;
    if (state) 
    {
        duty = 100;
    }
    else 
    {
        duty = 0;
    }
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, 0);
}
    
void LedBinary::blink(int on, int off) 
{
    this->milli_on = on;
    this->milli_off = off;
}