#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define BUTTON_INC GPIO_NUM_4
#define BUTTON_DEC GPIO_NUM_5
#define LED GPIO_NUM_7

void app_main(void)
{
    gpio_config_t button_inc = {};
    button_inc.pin_bit_mask = (1ULL << BUTTON_INC);
    button_inc.mode = GPIO_MODE_INPUT;
    button_inc.pull_up_en = 1;
    button_inc.pull_down_en = 0;
    button_inc.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&button_inc);

    gpio_config_t button_dec = {};
    button_dec.pin_bit_mask = (1ULL << BUTTON_DEC);
    button_dec.mode = GPIO_MODE_INPUT;
    button_dec.pull_up_en = 1;
    button_dec.pull_down_en = 0;
    button_dec.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&button_dec);

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
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&led_channel);


    int latch = 0;

    int max_duty = ledc_find_suitable_duty_resolution(LEDC_AUTO_CLK, 4000);

    int duty = 0;

    while(1) 
    {

        int inc_level = gpio_get_level(BUTTON_INC);
        int dec_level = gpio_get_level(BUTTON_DEC);

        //if button == low (inc)
        if (inc_level == 0 && latch == 0)  // && latch
        {

            printf("increased");
                
            if (duty + 1000 >= max_duty)
            {
                //debounce if
                //sett pwm to max pwm
                duty = max_duty;
            }
                    
            //else if , med latch
            else 
            {
                duty += 1000;
                //add more pwm
            }

            latch = 1;

            //task delay

        }
        else if (inc_level == 0 && latch == 1) 
        {

        }
                    
        if (dec_level == 0) 
        {
            printf("decreased");
            //if (dec amount <= pwm max)
            if(duty - 1000 <= 0) 
            {
                //turn pwm off/no value
                duty = 0;
            }

            else 
            {
                //add less pwm
                duty -= 1000;
            }
        } 
            //pwm for led execute

        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, 0);
        vTaskDelay(1000/ portTICK_PERIOD_MS);

    }
}