#include "led_binary.h"

#include <iostream>

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
    if (this->mode == 0) 
    {
        settLed(this->on);
    }
    else 
    {
        blink(this->milli_on, this->milli_off);
    }
}

void LedBinary::settLed(bool level) // on and off with mode to determinate state of led
{
    this->mode = 0;
    this->on = level;
    gpio_set_level((gpio_num_t)this->pin, level); //sends a signal equal to state
}
    
void LedBinary::blink(double on, double off) //takes milliseconds
{
    this->mode = 1;
    this->milli_on = on;
    this->milli_off = off;

    if(this->switch_to == false && (double)this->off_timer == 0) //will only happen the first time when the off function hasn't been triggered once
    {
        this->off_timer = (double)xTaskGetTickCount() /100; // start off timer
    }

    if (this->switch_to) 
    {
        //std::cout << xTaskGetTickCount() << " " << this->on_timer << " " << this->milli_on << std::endl;
        if (((double)xTaskGetTickCount() /100) - (double)this->on_timer >= this->milli_on / 1000) 
        {
            this->switch_to = false;
            this->off_timer = (double)xTaskGetTickCount() /100; //starts off timer
        }
    }
    else 
    {
        if (((double)xTaskGetTickCount() /100) - (double)this->off_timer >= this->milli_off / 1000) 
        {
            this->switch_to = true;
            this->on_timer = (double)xTaskGetTickCount() /100; //starts on timer
        }
    }
    //std::cout << ((double)xTaskGetTickCount() /100) - (double)this->off_timer << " " << (double)this->milli_on/1000 << " " <<(double)this->milli_off/1000 << std::endl;
    gpio_set_level((gpio_num_t)this->pin, this->switch_to); //sends a signal to led, turns on or off
}