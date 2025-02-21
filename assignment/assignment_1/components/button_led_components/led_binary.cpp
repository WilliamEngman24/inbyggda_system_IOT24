#include "led_binary.h"

void LedBinary::init(int pin) 
{
    gpio_config_t binary_led = 
    {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,                  //button value is write, output
        .pull_up_en = (gpio_pullup_t)0,           
        .pull_down_en = (gpio_pulldown_t)0,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&binary_led));
    this->pin = pin;
}

void LedBinary::update()
{
    if (!this->on == true) 
    {
        if(this->switch_to == false && (double)this->off_timer == 0) //will only happen the first time when the off function hasn't been triggered once
        {
            this->off_timer = (double)xTaskGetTickCount() / 100;
        }

        if (this->switch_to) 
        {
            if (((double)xTaskGetTickCount()/ 100) - (double)this->on_timer >= this->milli_on) 
            {
                this->switch_to = false;
                this->off_timer = (double)xTaskGetTickCount()/ 100;
            }
        }
        else 
        {
            //printf("%d %d %d \n ", (int)xTaskGetTickCount()/ 100, (int)this->off_timer, (int)this->milli_off );
            if (((double)xTaskGetTickCount()/ 100) - (double)this->off_timer >= this->milli_off) 
            {
                this->switch_to = true;
                this->on_timer = (double)xTaskGetTickCount() / 100;
        }
        }
        settLed(false);
    }
    else 
    {
        settLed(true);
    }
}

void LedBinary::settLed(bool state) // on  and off
{
    if (state) 
    {
        this->on = true;
        gpio_set_level((gpio_num_t)this->pin, 1); //sends a high signal to led, turns on
    }
    else 
    {
        this->on = false;
        
        if (this->switch_to == 1) 
        {
            gpio_set_level((gpio_num_t)this->pin, 1); //sends a high signal to led, turns on
        }
        else 
        {
            gpio_set_level((gpio_num_t)this->pin, 0); //sends a high signal to led, turns on
        }
    }
}
    
void LedBinary::blink(double on, double off) //takes milliseconds
{
    this->milli_on = on / 1000;
    this->milli_off = off / 1000;
}