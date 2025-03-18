#include "motor.h"

#define LIGHT_THRESHOLD 5
#define DUTY 5000

void Motor::init(int transistor, int h_bridge) 
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
        .gpio_num = transistor,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&motor_channel);

    gpio_config_t rotation = 
    {
        .pin_bit_mask = (1ULL << h_bridge),
        .mode = GPIO_MODE_OUTPUT,                  //button value is write, output
        .pull_up_en = (gpio_pullup_t)0,           
        .pull_down_en = (gpio_pulldown_t)0,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    gpio_config(&rotation);

    this->pin =h_bridge;
}

void Motor::update(int light_left, int light_right, int btn_left, int btn_right)
{
    this->on = true;
    rotation(1);
    /*
    int light_difference;
    if(light_left > light_right) //if left is larger than right
    {
        light_difference = light_left - light_right;

        if (light_difference > LIGHT_THRESHOLD) 
        {
            //activates rotation to the left
            if (!btn_left) //as long as the button isn't pressed 
            {
                this->on = true;
                rotation(1);
            }
        }
        else 
        {
            this->on = false;
        }
    }
    else if(light_right > light_left) //if right is larger than left
    {
        light_difference = light_right - light_left;

        if (light_difference > LIGHT_THRESHOLD) 
        {
            //activates rotation to the right
            if (!btn_right) //as long as the button isn't pressed 
            {
                this->on = true;
                rotation(0);
            }
        }
        else
        {
            this->on = false;
        }
    }
    */
}

void Motor::rotation(int mode)
{
    gpio_set_level((gpio_num_t)this->pin, mode);

    if (this->on) 
    {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, DUTY); //sets constant duty
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    }
}