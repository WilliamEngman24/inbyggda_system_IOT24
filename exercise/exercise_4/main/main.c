#include <stdio.h>

#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define TWDT_MS 3000
#define WATCHDOG_BUTTON GPIO_NUM_4


void app_main(void)
{
    esp_task_wdt_deinit();

    esp_task_wdt_config_t watchdog = 
    {
        .timeout_ms = TWDT_MS, //3 sek
        .idle_core_mask = (1 << CONFIG_FREERTOS_NUMBER_OF_CORES) - 1,
        .trigger_panic = true,
    };
    esp_task_wdt_init(&watchdog); //create/initiate TWDT to 3 seconds

    esp_task_wdt_add(NULL); //adds dog to current task

    gpio_config_t watchdog_button = 
    {
        .pin_bit_mask = (1ULL << WATCHDOG_BUTTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 1,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&watchdog_button);

    //esp_task_wdt_deinit();

    while(1)
    {
        int level = gpio_get_level(WATCHDOG_BUTTON);
        //latch
        //debounce
        if (level == 0) 
        {
            printf("Watchdog was triggered\n");
            esp_task_wdt_reset();
        }

        vTaskDelay(pdMS_TO_TICKS(30)); //delays task
        
    }

}