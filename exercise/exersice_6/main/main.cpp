#include <iostream>

#include "esp_sleep.h"

#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "driver/gpio.h"

//implement "assignment_1" as component

using namespace std;

double current_time = 0;

void deep_sleep() 
{
    if ((xTaskGetTickCount() / 100) - current_time >= 1)
    current_time = (xTaskGetTickCount() / 100);

    cout << current_time << endl;

    if (current_time == 10) 
    {
        esp_deep_sleep(3000000);
    }

}
bool light_sleep_mode = false;

void light_sleep() //assign to button function
{
    //activete light sleep
    if (light_sleep_mode == false) // turn on light sleep
    {
        light_sleep_mode = true;
        esp_light_sleep_start();
    }
    else //turn off light sleep
    {
        light_sleep_mode = false;
        //wakeup
    }
}

extern "C" 
{
    void app_main(void)
    {
        //create button
        //create led_binary

        while (1)
        {
            deep_sleep();

            //update button
            //update led

            //if()

            vTaskDelay(10);
        }
    }
}