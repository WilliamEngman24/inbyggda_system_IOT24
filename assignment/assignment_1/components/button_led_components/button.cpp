#include "button.h"
#include <iostream>

using namespace std;

void Button::init(int pin, bool isPulldown) 
{
    gpio_config_t button = 
    {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,                  //button value is read, input
        .pull_up_en = (gpio_pullup_t)1,           //pullup is enabled
        .pull_down_en = (gpio_pulldown_t)isPullDown,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    this->isPullDown = isPullDown;
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&button));
}

void Button::update(gpio_num_t pin)
{

    int level = gpio_get_level(pin);

    bool pressed = isPressed(level);

    if(pressed) //if level is high = button pressed
    {
        if (button_state == 0) //if the previous state of the button is low
        {
            last_pressed = xTaskGetTickCount(); //notes the time at button press
        }
        else if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10) && !this->latch) 
        {
            this->function(); //execute the function of button
            this->latch = 1;
        }
    }
    else 
    {
        this->latch = false;
    }

    this->button_state = pressed;
}

bool Button::isPressed(bool update)
{
    bool pressed;
    if (this->isPullDown == true && update == 1) //pulldown when high
    {
        pressed = 1;
    }
    else if (this->isPullDown == true && update == 0) //pulldown when low
    {
        pressed = 0;
    }
    else if (update == 0)
    {
        pressed = 1;
    }
    else 
    {
        pressed = 0;
    }

    return pressed;
}

void Button::setOnPressed(void(*onPressed)(void))
{
    this->function = *onPressed;
}