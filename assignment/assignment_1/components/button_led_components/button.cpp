#include "button.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

class Button
{
    public:
    
    void init(int pin) 
    {}

    void update()
    {}

    bool isPressed()
    {}

    void setOnPressed(void(*onPressed)(int pin))
    {
    }

};