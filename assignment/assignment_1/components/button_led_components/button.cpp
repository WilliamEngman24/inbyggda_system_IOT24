#include "button.h"
#include <iostream>

using namespace std;

void Button::settPressed(int level)
{
    this->button_state = level;
}

int Button::getPressed()
{
    return this->button_state;
}

void Button::init(int pin, bool isPulldown) 
{
    gpio_config_t button = 
    {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,                  //button value is read, input
        .pull_up_en = (gpio_pullup_t)1,           //make isPullDown int, do instead 1 - isPullDown        
        .pull_down_en = (gpio_pulldown_t)isPullDown,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    this->isPullDown = isPullDown;
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&button));
    this->pin = pin;
}

void Button::update()
{
    int level = gpio_get_level((gpio_num_t)this->pin);

    bool pressed = isPressed(level);

    if(this->getPressed()) // if level is high = button pressed " this->button_state "
    {
        if (this->getPressed() == 0) //if the previous state of the button is low " this->button_state "
        {
            last_pressed = xTaskGetTickCount(); //notes the time at button press
        }
        else if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10) && !this->latch) // if enough time has passed and latch is off
        {
            if (this->function != NULL) 
            {
                this->function();   //execute the function of button
                this->latch = true; //turn on latch
            }
        }
    }
    else 
    {
        this->latch = false;
    }

    this->settPressed(pressed); //always sett state to level value
}

bool Button::isPressed(bool level)
{
    bool pressed;
    if (this->isPullDown == true && level == 1) //pulldown when high
    {
        pressed = 1;
    }
    else if (this->isPullDown == true && level == 0) //pulldown when low
    {
        pressed = 0;
    }
    else if (level == false)
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