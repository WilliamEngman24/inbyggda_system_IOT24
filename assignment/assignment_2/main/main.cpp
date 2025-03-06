#include <stdio.h>
#include <iostream>

#include "my_nvs_flash.h"

extern "C"
{
    void app_main(void)
    {
        Nvs* new_nvs = new Nvs();

        esp_err_t error;

        nvs_flash_erase();

        new_nvs->init();

        error = nvs_open(new_nvs->getNameSpace(), NVS_READWRITE, new_nvs->getHandle());
        if (error != ESP_OK) 
        {
            printf("failed to open in sett device name\n");
        }
        else 
        {
            new_nvs->setDeviceName("first");
            new_nvs->setSerialNumber("111");

            printf("    Set and get\n");
            printf("    Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceName(), new_nvs->getSerialNumber());

            new_nvs->setDeviceName("second");
            new_nvs->setSerialNumber("2222");
    
            printf("    Set without get\n");
            printf("    Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceValue(), new_nvs->getSerialValue());

            new_nvs->setDeviceName("third");
            new_nvs->setSerialNumber("33");

            printf("    Set and get\n");
            printf("    Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceName(), new_nvs->getSerialNumber());
            //nvs_commit(*new_nvs->getHandle());
            nvs_close(*new_nvs->getHandle());
        }
    }
}