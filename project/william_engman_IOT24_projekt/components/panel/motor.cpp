#include "motor.h"

#define LIGHT_THRESHOLD 5

void Motor::init(int pin) 
{
    ledc_timer_config_t motor_timer =
    {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 4000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&motor_timer);
    
    ledc_channel_config_t motor_channel = 
    {
        .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&motor_channel);
}

void Motor::update(int light_left, int light_right)
{
    int light_difference;
    if(light_left > light_right) //if left is larger than right
    {
        light_difference = light_left - light_right;

        if (light_difference > LIGHT_THRESHOLD) 
        {
            //activates rotation to the left
            if () //as long as the button isn't pressed 
            {
                
            }
        }

    }
    else if(light_right > light_left) //if right is larger than left
    {
        light_difference = light_right - light_left;

        if (light_difference > LIGHT_THRESHOLD) 
        {
            //activates rotation to the right
            if () //as long as the button isn't pressed 
            {

            }
        }
    }
}

void Motor::rotation()
{
    
}