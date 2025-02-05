#include <stdio.h>

#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

#include "esp_log.h"

#define TWDT_MS 3000
#define WATCHDOG_BUTTON GPIO_NUM_4

#define IDLE_CORE_0_BIT 0b11
#define IDLE_CORE_1_BIT 0b10

void handler(void* arg);

void app_main(void)
{
    bool latch_on = false;

    bool interrupt = false;

    TickType_t btn_pressed_time = xTaskGetTickCount();

    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_install_isr_service(0));
    gpio_isr_handler_add(WATCHDOG_BUTTON, handler, &latch_on);

    esp_task_wdt_config_t watchdog = 
    {
        .timeout_ms = TWDT_MS, //3 sek
        .idle_core_mask = IDLE_CORE_0_BIT | IDLE_CORE_1_BIT,
        .trigger_panic = true,
    };
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_task_wdt_reconfigure(&watchdog)); //create/initiate TWDT to 3 seconds

    esp_task_wdt_add(NULL); //adds dog to current task

    gpio_config_t watchdog_button = 
    {
        .pin_bit_mask = (1ULL << WATCHDOG_BUTTON),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 1,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_ERROR_CHECK_WITHOUT_ABORT(gpio_config(&watchdog_button));

    //esp_task_wdt_deinit();

    while(1)
    {
        /*
        int level = gpio_get_level(WATCHDOG_BUTTON);
        if(level == 0)
        {
            latch_on = true;
        }
        */
        if (latch_on) 
        {
            latch_on = false;
            printf("Watchdog was triggered\n");
            btn_pressed_time = xTaskGetTickCount();
            interrupt = false;
            esp_task_wdt_reset();
        }
        if (interrupt) 
        {
            TickType_t time_elapsed = xTaskGetTickCount() - btn_pressed_time;
            if(time_elapsed > pdMS_TO_TICKS(40)) 
            {
                gpio_isr_handler_add(WATCHDOG_BUTTON, handler, &latch_on);
                interrupt = true;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(30)); //delays task
        
    }

    esp_task_wdt_delete(NULL);
}

void handler(void* arg)
{
    bool button;
    gpio_isr_handler_remove(WATCHDOG_BUTTON);
    bool* button_change = (bool*)arg;
    button = true;                                             //change here
    esp_task_wdt_reset();
}