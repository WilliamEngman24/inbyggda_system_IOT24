#include <stdio.h>
#include <string.h>

#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/queue.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"

#include "driver/i2c_master.h"
#include "driver/i2c.h"


#define TX GPIO_NUM_5
#define RX GPIO_NUM_4

#define RTS GPIO_NUM_2
#define CTS GPIO_NUM_3

#define BUFFER_SIZE 2048
#define TAG "MAIN"
#define DATA_SIZE 128

#define SEND_PERIOD 2000

//
#define I2C_SCL GPIO_NUM_6
#define I2C_SDA GPIO_NUM_8
#define DATA_LENGTH 100

void app_main(void)
{
    while(1) 
    {
        i2c_master_bus_config_t i2c_mst_config = 
        {
            .clk_source = LP_I2C_SCLK_DEFAULT,
            .i2c_port = -1,
            .scl_io_num = I2C_SCL,
            .sda_io_num = I2C_SDA,
            .glitch_ignore_cnt = 7,
            .flags.enable_internal_pullup = true,
        };

        i2c_master_bus_handle_t bus_handle;
        ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

        i2c_device_config_t dev_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = 0x58,
            .scl_speed_hz = 100000,
        };

        i2c_master_dev_handle_t dev_handle;
        ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));

        uint8_t data_wr[DATA_LENGTH] = "Order: bla bla bla";

        ESP_ERROR_CHECK(i2c_master_transmit(dev_handle, data_wr, DATA_LENGTH, -1));

        uint8_t data_rd[DATA_LENGTH];
        i2c_master_receive(dev_handle, data_rd, DATA_LENGTH, -1);

        data_rd[DATA_LENGTH] = 0;
        printf("%s", data_rd);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }


    // UART
    /*
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
    */
}