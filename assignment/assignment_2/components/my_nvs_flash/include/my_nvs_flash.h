#pragma once

#ifndef MY_NVS_FLASH_H
#define MY_NVS_FLASH_H

#include "nvs_flash.h"
#include "nvs.h"

class Nvs
{
private:
    nvs_handle_t handle_NVS;

    char* name_namespace;
    
    char* key_device;
    char* key_serial;

    char* value_device;
    char* value_serial;

    esp_err_t error;

public:

    nvs_handle_t* getHandle();
    char* getNameSpace();

    char* getDeviceValue();
    char* getSerialValue();

    void init();
    char* getDeviceName();
    char* getSerialNumber();
    void setDeviceName(char* name);
    void setSerialNumber(char* number);
    
};

#endif
