#include <stdio.h>

#include <iostream>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

#include "button.h"
#include "potentiometer.h"
#include "led_binary.h"
#include "led_analog.h"

#define BUTTON GPIO_NUM_7

using namespace std;

void button_function()
{
    cout << "Button was pressed" << endl;
}

extern "C"
{
    void app_main(void)
    {
        Button* button_1 = new Button();

        button_1->init(BUTTON, false);
        button_1->setOnPressed(button_function);

        while(1) 
        {
            button_1->update(BUTTON);
            //vTaskDelay(pdMS_TO_TICKS(10));
        }

    }
}
