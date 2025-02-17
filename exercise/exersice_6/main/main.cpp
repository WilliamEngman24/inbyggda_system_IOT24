#include <iostream>

#include "esp_sleep.h"

#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "driver/gpio.h"

using namespace std;

extern "C" 
{
    void app_main(void)
    {
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));

            double current_time = (xTaskGetTickCount() / 100);
            
            cout << current_time << endl;

            if (current_time == 10) 
            {
                esp_deep_sleep(3000000);
            }
        }
    }
}