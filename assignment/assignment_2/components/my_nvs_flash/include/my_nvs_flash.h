#pragma once

#ifndef MY_NVS_FLASH_H
#define MY_NVS_FLASH_H

#include "nvs_flash.h"
#include "nvs.h"

class Nvs
{
private:
    nvs_handle_t handle_NVS;

    char* namespace_NVS;
    
    char* key_device;
    char* key_serial;

    char* value_device = NULL;
    char* value_serial = NULL;

    char* device_ret = NULL;
    char* serial_ret = NULL;

    esp_err_t error;

public:

    nvs_handle_t* getHandle();
    char* getNameSpace();

    char* getDeviceValue();
    char* getSerialValue();

    bool init(char* nameSpace, char* device, char* serial);

    char* getDeviceName();
    char* getSerialNumber();

    char* getDeviceNVS();
    char* getSerialNVS();

    void setDeviceName(char* name);
    void setSerialNumber(char* number);
    
};

#endif
