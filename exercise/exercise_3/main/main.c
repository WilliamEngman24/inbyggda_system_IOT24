#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

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

    //latch

    while(1) 
    {
        int inc_level = gpio_get_level(BUTTON_INC);
        int dec_level = gpio_get_level(BUTTON_DEC);

        //if button == low (inc)
        if (inc_level == 0)  // && latch
        {
            printf("increase");
                /*
                //if (inc amount + pwm current >= pwm max)
                if () 
                {
                    //debounce if
                    //sett pwm to max pwm
                }
                    
                //else if , med latch
                else 
                {
                    //add more pwm
                }
                */
        }
                    
        if (dec_level == 0) 
        {
            printf("decrease");
                /*
                //if button == low (dec)
                //if (dec amount <= pwm max)
                if() 
                {
                    //turn pwm off/no value
                }

                //else
                else 
                {
                    //add less pwm
                }
                */
        } 
            //pwm for led execute

    }
}