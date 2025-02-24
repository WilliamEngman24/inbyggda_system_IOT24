#include <stdio.h>
#include <iostream>

#include "my_nvs_flash.h"

nvs_handle_t* Nvs::getHandle()
{
    return &this->handle_NVS;
}
char* Nvs::getNameSpace()
{
    return this->name_namespace;
}

void Nvs::init() 
{
    esp_err_t nvs_flash_deinit(); //deinit the default
    esp_err_t new_NVS = nvs_flash_init(); //init the default

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
    nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS);

    char ret [this->max_string_size + 1];

    size_t max_size = sizeof(ret);

    nvs_get_str(*this->key_device, this->name_namespace, ret, &max_size);
    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "serial: " << this->key_device << std::endl;
    std::cout << "max_size: " << &(this->max_string_size) << std::endl;
    std::cout << "return: " << ret << std::endl;
    std::cout << "--------" << std::endl;
    return ret;
}
char* Nvs::getSerialNumber() 
{
    ESP_ERROR_CHECK(nvs_open(this->name_namespace, NVS_READONLY, &this->handle_NVS));

    char ret[this->max_string_size + 1];

    size_t max_size = sizeof(ret);

    nvs_get_str(*this->key_serial, this->name_namespace, ret, &max_size);
    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "serial: " << this->key_serial << std::endl;
    std::cout << "max_size: " << &(this->max_string_size) << std::endl;
    std::cout << "return: " << ret << std::endl;
    std::cout << "--------" << std::endl;
    return ret;
}

void Nvs::settDeviceName(char* name) 
{
    ESP_ERROR_CHECK(nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS));

    nvs_set_str(*this->key_device, this->name_namespace, name);

    nvs_commit(this->handle_NVS);

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "name: " << name << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "serial: " << this->key_device << std::endl;
    std::cout << "max_size: " << &(this->max_string_size) << std::endl;
    std::cout << "--------" << std::endl;
}
void Nvs::settSerialNumber(char* number) 
{
    nvs_open(this->name_namespace, NVS_READWRITE, &this->handle_NVS);

    nvs_set_str(*this->key_serial, this->name_namespace, number);
    
    nvs_commit(this->handle_NVS);

    std::cout << "namespace: " << this->name_namespace << std::endl;
    std::cout << "name: " << number << std::endl;
    std::cout << "handle: " << this->handle_NVS << std::endl;
    std::cout << "serial: " << this->key_serial << std::endl;
    std::cout << "max_size: " << &(this->max_string_size) << std::endl;
    std::cout << "--------" << std::endl;
}
