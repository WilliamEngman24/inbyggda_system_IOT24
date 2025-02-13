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
#define LED_BINARY GPIO_NUM_2

using namespace std;

void button_function()
{
    cout << "Button was pressed" << endl;
}

void potentiometer_function(adc_channel_t adc, int value) 
{
    cout << "Channel: " << adc << " | Value: " << value << " | Threshold reached!" <<endl;
}

extern "C"
{
    void app_main(void)
    {
        Button* button_1 = new Button();
        Potentiometer* potentiometer_1 = new Potentiometer();
        LedBinary* led_binary_1 = new LedBinary();

        button_1->init(BUTTON, false);
        button_1->setOnPressed(button_function);

        potentiometer_1->init(POTENTIOMETER);
        potentiometer_1->setOnThreshold(500, true, potentiometer_function);

        led_binary_1->init(LED_BINARY);
        led_binary_1->blink(1, 2);

        while(1) 
        {
            button_1->update(BUTTON);

            potentiometer_1->update(POTENTIOMETER);

            led_binary_1->update(LED_BINARY);

            vTaskDelay(pdMS_TO_TICKS(10));
        }

    }
}
