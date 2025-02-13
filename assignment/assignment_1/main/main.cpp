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
#define POTENTIOMETER ADC_CHANNEL_6

using namespace std;

void button_function()
{
    cout << "Button was pressed" << endl;
}

void potentiometer_function(int pin, int value) 
{
    
}

extern "C"
{
    void app_main(void)
    {
        Button* button_1 = new Button();
        Potentiometer* potentiometer_1 = new Potentiometer();

        button_1->init(BUTTON, false);
        button_1->setOnPressed(button_function);

        potentiometer_1->init(POTENTIOMETER);
        potentiometer_1->setOnThreshold(100, true, potentiometer_function);

        while(1) 
        {
            button_1->update(BUTTON);

            potentiometer_1->update(POTENTIOMETER);

            vTaskDelay(pdMS_TO_TICKS(100));
        }

    }
}
