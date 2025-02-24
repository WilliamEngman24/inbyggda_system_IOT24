#include "button.h"
#include <iostream>

using namespace std;

void Button::settPressed(int level) //rename
{
    this->level = level;
}

bool Button::getPressed()
{
    if (this->button_state == 0 || this->button_state == 3) //if button is either in enum state 0 or 3, 
    {
        return false;
    }
    else //if button is in state 1 or 2
    {
        return true;
    }
}

void Button::init(int pin, bool isPulldown) 
{
    gpio_config_t button = 
    {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_INPUT,                  //button value is read, input
        .pull_up_en = (gpio_pullup_t)(1 - isPullDown),           //make isPullDown int, do instead 1 - isPullDown        
        .pull_down_en = (gpio_pulldown_t)isPullDown,
        .intr_type = GPIO_INTR_DISABLE,           //interupt is disabled
    };
    this->isPullDown = isPullDown;
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&button));
    this->pin = pin;
}

void Button::update()
{
   bool pressed = isPressed();

   // make a isPressed variableand use in each case where the button is High and low

    enum Case
    {
        BTN_OFF,
        DE_ON,
        BTN_ON,
        DE_OFF
    };

    switch(this->button_state)
    {
        case BTN_OFF:
        if (pressed != 0) //if button has been pressed
        //printf("is in button off\n");
        {
            this->last_pressed = xTaskGetTickCount();
            this->latch = false;
            this->button_state = DE_ON;
            this->settPressed(pressed);

            if (this->function != NULL) 
            {
                this->function();   //execute the function of button
            }
        }
        break;

        case DE_ON: // skipp till
        //printf("is in debounce on\n");
        if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10)) //when when bounce on is done
        {
            this->button_state = BTN_ON;
        }
        break;

        case BTN_ON: //preform the task
        //printf("is in button on\n");
        if (pressed == 1 && !this->latch) //if pressed is high and latch is off
        {
            this->latch = true;
            this->last_pressed = xTaskGetTickCount(); //start debounce off timer
            //printf("has pressed the button\n");
        }
        else if (pressed == 0) //when the button has been let go
        {
            this->button_state = DE_OFF;
            this->settPressed(pressed);
            //printf("has let go of button\n");
        }
        break;

        case DE_OFF:
        //printf("is in deboune off\n");
        if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10)) //when debounce off timer is done
        {
            this->button_state = BTN_OFF;
        }
        break;
    }
    /*
    if (this->button_state == false) 
{
    //printf("is in button off\n");
    if (pressed != 0 && !this->latch) //if button has been pressed
    {
        this->last_pressed = xTaskGetTickCount();
        this->latch = true;

        if (this->function != NULL) 
        {
            this->function();   //execute the function of button
        }
    }
    else if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10) && this->latch) //when bounce on is done
    {
        this->latch = false;
        this->settPressed(true); //move on to button is on
    }
    }
    else //preform the task
    {
    //printf("is in button on\n");
    if (!this->latch) //if latch is off
    {
        this->latch = true;
        this->last_pressed = xTaskGetTickCount(); //start debounce off timer
        //printf("has pressed the button\n");
    }
    else if (xTaskGetTickCount() - this->last_pressed > pdMS_TO_TICKS(10) && this->latch) //when the button has been let go
    {
        this->latch = false;
        this->settPressed(false); //move on to button off state
    }
}
    */

}

bool Button::isPressed()
{
    int level = gpio_get_level((gpio_num_t)this->pin);

    bool pressed;
    if (this->isPullDown == true && level == 1) //pulldown true when state is high
    {
        pressed = 1;
    }
    else if (this->isPullDown == true && level == 0) //pulldown true when state is low
    {
        pressed = 0;
    }
    else if (level == false) //pullup is true
    {
        pressed = 1;
    }
    else //pullup is false
    {
        pressed = 0;
    }

    return pressed;
}

void Button::setOnPressed(void(*onPressed)(void))
{
    this->function = *onPressed;
}