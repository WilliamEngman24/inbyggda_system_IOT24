#include <stdio.h>
#include <iostream>

#include "my_nvs_flash.h"
#include "esp_log.h"

#define TAGI "INFO"

extern "C"
{
    void app_main(void)
    {
        Nvs* new_nvs = new Nvs();

        esp_err_t error;

        nvs_flash_erase();

        if (new_nvs->init("default_init", "device", "serial"))
        {
            printf("---------------------------------\n");

            ESP_LOGI(TAGI, "    Get from NVS before set:");
            ESP_LOGI(TAGI, "    Device Name: %s | Serial Number: %s", new_nvs->getDeviceName(), new_nvs->getSerialNumber());

            printf("---------------------------------\n");

            ESP_LOGI(TAGI, "    Set and get:");
            new_nvs->setDeviceName("first");
            new_nvs->setSerialNumber("111");
            ESP_LOGI(TAGI, "    Device Name: %s | Serial Number: %s", new_nvs->getDeviceName(), new_nvs->getSerialNumber());

            printf("---------------------------------\n");

            ESP_LOGI(TAGI, "    Set without values:");
            new_nvs->setDeviceName("");
            new_nvs->setSerialNumber("");
            ESP_LOGI(TAGI, "    Device Name: %s | Serial Number: %s", new_nvs->getDeviceValue(), new_nvs->getSerialValue());
            
            printf("---------------------------------\n");

            ESP_LOGI(TAGI, "    Set and get new values:");
            new_nvs->setDeviceName("second");
            new_nvs->setSerialNumber("22222");
            ESP_LOGI(TAGI, "    Device Name: %s | Serial Number: %s", new_nvs->getDeviceName(), new_nvs->getSerialNumber());
            //nvs_commit(*new_nvs->getHandle());
            nvs_close(*new_nvs->getHandle());
        }
    }
}