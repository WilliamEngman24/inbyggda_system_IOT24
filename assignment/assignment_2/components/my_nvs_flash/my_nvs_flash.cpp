#include <stdio.h>
#include <iostream>
#include <string.h>

#include "esp_log.h"

#include "my_nvs_flash.h"

#define MAX_SIZE 100

nvs_handle_t* Nvs::getHandle()
{
    return &this->handle_NVS;
}
char* Nvs::getNameSpace()
{
    return this->name_namespace;
}
char* Nvs::getDeviceValue()
{
    return this->value_device;
}
char* Nvs::getSerialValue()
{
    return this->value_serial;
}

void Nvs::init() 
{
    esp_err_t new_NVS = nvs_flash_init(); //init the default

    this->error = new_NVS;

    // if partition was truncated vvv
    if (new_NVS == ESP_ERR_NVS_NO_FREE_PAGES || new_NVS == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        //erases default NVS
        ESP_ERROR_CHECK(nvs_flash_erase());

        //tries to reinitialize NVS after erase
        new_NVS = nvs_flash_init();
    }
    //checks if the NVS was created correctly vvv
    ESP_ERROR_CHECK(new_NVS); 

    this->name_namespace = "default_init";
    this->key_device = "device";
    this->key_serial = "serial";

    setDeviceName(getDeviceName());
    setSerialNumber(getSerialNumber());
}

char* Nvs::getDeviceName()
{
    
    this->error = nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in get device name\n");

        return "failed";
    }
    
    size_t max_size;

    this->error = nvs_get_str(this->handle_NVS, this->key_device, NULL, &max_size);

    if (max_size == 0) //if the nvm has no memory
    {
        return "";
    }

    char* ret = (char*)malloc(max_size * sizeof(char));

    this->error = nvs_get_str(this->handle_NVS, this->key_device, ret, &max_size);

    std::cout << "--------" << std::endl;
    std::cout << "Get device "<< std::endl;
    std::cout << "name: " << ret << std::endl;
    std::cout << "max size: " << max_size << std::endl;
    std::cout << "--------" << std::endl;

    if (this->error != ESP_OK) 
    {
        printf("get device name failed\n");
        return "failed\n";
    }

    free(ret);
    //nvs_close(this->handle_NVS);
    return this->value_device;
}
char* Nvs::getSerialNumber() 
{
    
    this->error = nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in get serial number\n");
        return "";
    }
    

    size_t max_size;

    this->error = nvs_get_str(this->handle_NVS, this->key_serial, NULL, &max_size);

    if (max_size == 0) 
    {
        return "";
    }

    char* ret = (char*)malloc(max_size * sizeof(char));

    this->error = nvs_get_str(this->handle_NVS, this->key_serial, ret, &max_size);

    std::cout << "--------" << std::endl;
    std::cout << "Get serial " << std::endl;
    std::cout << "name: " << ret << std::endl;
    std::cout << "max size: " << max_size << std::endl;
    std::cout << "--------" << std::endl;

    if (this->error != ESP_OK) 
    {
        printf("get serial number failed\n");
        return "failed\n";
    }

    free(ret);
    //nvs_close(this->handle_NVS);
    return this->value_serial;
}

void Nvs::setDeviceName(char* name) 
{
    
    this->error = nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in sett device name\n");
    }
    
    if (strlen(name) == 0) 
    {
        printf("Cannot store an empty value\n");
        return;
    }

    this->error = nvs_set_str(this->handle_NVS, this->key_device, name);

    if (this->error != ESP_OK) 
    {
        printf("sett device name failed\n");
    }
    else 
    {
        this->error = nvs_commit(this->handle_NVS);

        if (this->error != ESP_OK) 
        {
            printf("couldn't commit in set device\n");
        }
        else
        {
            this->value_device = (char*)malloc(strlen(name) * sizeof(char));
            strcpy(this->value_device, name);
        }
    }

    std::cout << "--------" << std::endl;
    std::cout << "Set device" << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "--------" << std::endl;

    //nvs_close(this->handle_NVS);

}
void Nvs::setSerialNumber(char* number) 
{    
    
    this->error = nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in sett serial number\n");
    }
    
    if (strlen(number) == 0) 
    {
        printf("Cannot store an empty value\n");
        return;
    }

    this->error = nvs_set_str(this->handle_NVS, this->key_serial, number); // try to set string to nvs
    
    if (this->error != ESP_OK)
    {
        printf("sett device serial failed\n");
    }
    else 
    {
        this->error = nvs_commit(this->handle_NVS);

        if (this->error != ESP_OK) 
        {
            printf("couldn't commit in set serial\n");
        }
        else
        {
            this->value_serial = (char*)malloc(strlen(number) * sizeof(char));
            strcpy(this->value_serial, number);
        }
    }

    std::cout << "--------" << std::endl;
    std::cout << "Set serial" << std::endl;
    std::cout << "number: " << number << std::endl;
    std::cout << "--------" << std::endl;

    //nvs_close(this->handle_NVS);

}
