#include "led_binary.h"

void LedBinary::init(int pin) 
{
    gpio_config_t binary_led = 
    {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,                  //button value is read, input
        .pull_up_en = (gpio_pullup_t)0,           //pullup is enabled
        .pull_down_en = (gpio_pulldown_t)0,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&binary_led));
}

void LedBinary::update(int pin)
{
    if(this->on == false && (double)this->off_timer == 0) //will only happen the first time when the off function hasn't been triggered once
    {
        this->off_timer = (double)xTaskGetTickCount() / 100;
    }

    if (this->on) 
    {
        if (((double)xTaskGetTickCount()/ 100) - (double)this->on_timer >= this->milli_on) 
        {
            this->on = false;
            this->off_timer = (double)xTaskGetTickCount()/ 100;
        }
    }
    else 
    {
        //printf("%d %d %d \n ", (int)xTaskGetTickCount()/ 100, (int)this->off_timer, (int)this->milli_off );
        if (((double)xTaskGetTickCount()/ 100) - (double)this->off_timer >= this->milli_off) 
        {
            this->on = true;
            this->on_timer = (double)xTaskGetTickCount() / 100;
        }
    }

    settLed(pin, this->on);
}

void LedBinary::settLed(int pin, bool state) // on  and off
{
    if (state) 
    {
        gpio_set_level((gpio_num_t)pin, 1); //sends a high signal to led, turns on
    }
    else 
    {
        gpio_set_level((gpio_num_t)pin, 0); // sends low signal to led, turns off
    }
}
    
void LedBinary::blink(double on, double off) 
{
    this->milli_on = on;
    this->milli_off = off;
}