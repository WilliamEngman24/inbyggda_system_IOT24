#include <stdio.h>
#include <iostream>

#include "esp_log.h"

#include "my_nvs_flash.h"

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
}

char* Nvs::getDeviceName()
{
    this->error = nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in get device name\n");
    }

    char* ret = (char*)malloc(this->max_string_size * sizeof(char*));

    size_t max_size = sizeof(ret);

    this->error = nvs_get_str(this->handle_NVS, this->key_device, ret, &max_size);

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "device: " << this->key_device << std::endl;
    std::cout << "name: " << ret << std::endl;
    std::cout << "--------" << std::endl;

    if (this->error != ESP_OK) 
    {
        printf("get device serial failed\n");
    }
    else 
    {
        this->value_device = ret;
    }

    nvs_close(this->handle_NVS);

    return this->value_device;
}
char* Nvs::getSerialNumber() 
{
    this->error = nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in get serial number\n");
    }

    char* ret = (char*)malloc(this->max_string_size * sizeof(char*));

    size_t max_size = sizeof(ret);

    this->error = nvs_get_str(this->handle_NVS, this->key_serial, ret, &max_size);

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "device: " << this->key_serial << std::endl;
    std::cout << "name: " << ret << std::endl;
    std::cout << "--------" << std::endl;

    if (this->error != ESP_OK) 
    {
        printf("get device name failed\n");
    }
    else 
    {
        this->value_serial = ret;
    }

    nvs_close(this->handle_NVS);

    return this->value_serial;
}

void Nvs::settDeviceName(char* name) 
{
    this->error = nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in sett device name\n");
    }

    name = name + '\0';

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
            printf("couldn't commit");
        }
    }

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "device: " << this->key_device << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "--------" << std::endl;

    nvs_close(this->handle_NVS);

}
void Nvs::settSerialNumber(char* number) 
{    
    this->error = nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        printf("failed to open in sett serial number\n");
    }

    number = number + '\0';

    this->error = nvs_set_str(this->handle_NVS, this->key_serial, number);
    
    if (this->error != ESP_OK) 
    {
        printf("sett device serial failed\n");
    }
    else 
    {
        this->error = nvs_commit(this->handle_NVS);
        
        if (this->error != ESP_OK) 
        {
            printf("couldn't commit");
        }
    }

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "serial: " << this->key_serial << std::endl;
    std::cout << "number: " << number << std::endl;
    std::cout << "--------" << std::endl;

    nvs_close(this->handle_NVS);

}
