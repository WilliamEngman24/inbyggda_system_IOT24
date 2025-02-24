#include <stdio.h>
#include <iostream>

#include "my_nvs_flash.h"

extern "C"
{
    void app_main(void)
    {
        Nvs* new_nvs = new Nvs();

        new_nvs->init();

        //nvs_open(new_nvs->getNameSpace(), NVS_READWRITE, new_nvs->getHandle());

        printf("not init\n");
        new_nvs->getDeviceName();

        new_nvs->settDeviceName("test");

        printf("not set device\n");
        new_nvs->getSerialNumber();

        new_nvs->settSerialNumber("123");

        //nvs_commit(*new_nvs->getHandle());

        //nvs_close(*new_nvs->getHandle());

        printf("Device Name: %s | Serial Number: %s \n");
    }
}