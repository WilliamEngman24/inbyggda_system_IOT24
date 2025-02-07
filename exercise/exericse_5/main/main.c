#include <stdio.h>
#include <string.h>

#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"


#define TX GPIO_NUM_5
#define RX GPIO_NUM_4

#define RTS GPIO_NUM_2
#define CTS GPIO_NUM_3

#define BUFFER_SIZE 2048
#define TAG "MAIN"
#define DATA_SIZE 128

#define SEND_PERIOD 2000

void app_main(void)
{
    //config UART to port 1
    const uart_port_t uart_num = UART_NUM_1;

    uart_config_t uart_config = 
    {
        .baud_rate = 115200, //standard
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122, 
    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    //set pinns
    ESP_ERROR_CHECK(uart_set_pin(uart_num, TX, RX, RTS, CTS)); //UART_PIN_NO_CHANGE

    //driver
    QueueHandle_t uart_queue;

    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUFFER_SIZE, BUFFER_SIZE, 10, &uart_queue, 0));

    TickType_t sentTimer = xTaskGetTickCount();

    char* test_str = "brrrrrrrrrrrrrrrrrrrrr'\n";

    while (1)
    {
        TickType_t elapsedTime = xTaskGetTickCount();

        //write data
        if(elapsedTime > pdMS_TO_TICKS(SEND_PERIOD)) 
        {
            sentTimer += pdMS_TO_TICKS(SEND_PERIOD); 
            //write to UART

            int bytes_sent = uart_write_bytes(uart_num, (const char*) test_str, strlen(test_str));
            if (bytes_sent < 0) 
            {
                ESP_LOGE(TAG, "error");
            }
            else if (bytes_sent > 0)
            {
                ESP_LOGI(TAG, "sent");
            }
            else 
            {
                ESP_LOGE(TAG, "idk");
            }
        }

        //receive data
        uint8_t data[DATA_SIZE];
        int length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
        if (length > DATA_SIZE - 1) 
        {
            ESP_LOGI(TAG, "Bytes in buffer: %d", length);
            length = uart_read_bytes(uart_num, data, DATA_SIZE -1, pdMS_TO_TICKS(1000));
        }
        else if (length > 0)
        {
            ESP_LOGI(TAG, "Bytes in buffer: %d", length);
            length = uart_read_bytes(uart_num, data, length, pdMS_TO_TICKS(1000));
        }
        else
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        if (length < 0) 
        {
            ESP_LOGE(TAG, "error");
        }
        else if (length > 0)
        {
            data[length] = 0;
            printf("%s", data);
            ESP_LOGI(TAG, "Got %d bytes and the string: %s", length, data);
        }
        else 
        {
            ESP_LOGE(TAG, "error, the length is 0");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}