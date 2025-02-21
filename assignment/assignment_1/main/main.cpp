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
#define LED_ANALOG ADC_CHANNEL_3

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
        LedAnalog* led_analog_1 = new LedAnalog();

        button_1->init(BUTTON, false);
        button_1->setOnPressed(button_function);

        potentiometer_1->init(POTENTIOMETER);
        potentiometer_1->setOnThreshold(500, true, potentiometer_function);

        led_binary_1->init(LED_BINARY);
        led_binary_1->blink(1000, 1000);
        led_binary_1->settLed(1);

        led_analog_1->init(LED_ANALOG);
        led_analog_1->settSin(3000);
        led_analog_1->settLed(200);

        while(1) 
        {
            button_1->update();

            potentiometer_1->update();

            led_binary_1->update();

            led_analog_1->update();

            vTaskDelay(pdMS_TO_TICKS(10));
        }

    }
}
