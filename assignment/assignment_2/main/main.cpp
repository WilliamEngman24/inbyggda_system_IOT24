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
        
        printf("before using NVS:\n");
        printf("no values if fresh start, should say second and 2 if not new\n");
        printf("Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceName(), new_nvs->getSerialNumber());

        new_nvs->settDeviceName("first");
        new_nvs->settSerialNumber("1");
        
        printf("after using set and get NVS:\n");
        printf("new values\n");
        printf("Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceName(), new_nvs->getSerialNumber());

        new_nvs->settDeviceName("fail_if_show");
        new_nvs->settSerialNumber("1337");

        printf("after using sett without get NVS:\n");
        printf("same values as before\n");
        printf("Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceValue(), new_nvs->getSerialValue());

        new_nvs->settDeviceName("second");
        new_nvs->settSerialNumber("2");

        printf("after using sett and get NVS:\n");
        printf("new values\n");
        printf("Device Name: %s | Serial Number: %s \n\n", new_nvs->getDeviceName(), new_nvs->getSerialNumber());
        //nvs_commit(*new_nvs->getHandle());
        //nvs_close(*new_nvs->getHandle());
    }
}