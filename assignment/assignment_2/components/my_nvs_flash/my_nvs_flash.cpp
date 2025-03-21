#include <stdio.h>
#include <iostream>
#include <string.h>

#include "esp_log.h"

#include "my_nvs_flash.h"

#define MAX_SIZE 100
#define MAX_KEY_NAME 14

#define TAGE "ERROR"
#define TAGW "WARNING"

//vvv help functions used in main
nvs_handle_t* Nvs::getHandle()
{
    return &this->handle_NVS;
}
char* Nvs::getNameSpace()
{
    return this->namespace_NVS;
}
//^^^ may not be usefull

bool Nvs::init(char* nameSpace, char* device, char* serial) 
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

    if (strlen(nameSpace) <= MAX_KEY_NAME && strlen(device) <= MAX_KEY_NAME && strlen(serial) <= MAX_KEY_NAME)
    { 
        this->namespace_NVS = nameSpace;
        this->key_device = device;
        this->key_serial = serial;

        setDeviceName(getDeviceNVS());
        setSerialNumber(getSerialNVS());

        return true;
    }
    else
    {
        ESP_LOGE(TAGE, "Key names cannot be larger than 14");
        ESP_LOGE(TAGE, "Keys have not been assigned, init failed");

        return false;
    }
}

char* Nvs::getDeviceNVS()
{
    this->error = nvs_open(this->namespace_NVS, NVS_READWRITE, &this->handle_NVS);

    if(this->error == ESP_ERR_NVS_NOT_FOUND) 
    {
        ESP_LOGW(TAGW, "nvs not found");
    }

    if (this->error != ESP_OK) 
    {
        ESP_LOGE(TAGE, "Failed to open in get device name");
    }
    else
    {
        size_t max_size;

        this->error = nvs_get_str(this->handle_NVS, this->key_device, NULL, &max_size);

        if (max_size == 0) //if the nvm has no memory
        {
            ESP_LOGW(TAGW, "No memory of device key was found on NVS");
        }
        else 
        {
            if(this->error == ESP_ERR_NVS_NOT_FOUND) 
            {
                setDeviceName(" ");
                this->error = nvs_get_str(this->handle_NVS, this->key_device, NULL, &max_size);
            }

            if (this->device_ret != NULL)
            {
                free(this->device_ret);
            }
            this->device_ret = (char*)malloc(max_size * sizeof(char));

            this->error = nvs_get_str(this->handle_NVS, this->key_device, this->device_ret, &max_size);

            if (this->error != ESP_OK) 
            {
                ESP_LOGE(TAGE, "Get device name failed");
            }
            else 
            {
                return this->device_ret;
            }
        }
    }

    return " ";
}
char* Nvs::getSerialNVS() 
{
    this->error = nvs_open(this->namespace_NVS, NVS_READWRITE, &this->handle_NVS);

    if(this->error == ESP_ERR_NVS_NOT_FOUND) 
    {
        ESP_LOGW(TAGW, "nvs not found");
    }
    if (this->error != ESP_OK) 
    {
        ESP_LOGE(TAGE, "Failed to open in get serial number");
    }
    else 
    {
        size_t max_size;

        this->error = nvs_get_str(this->handle_NVS, this->key_serial, NULL, &max_size);

        if (max_size == 0) 
        {
            ESP_LOGW(TAGW, "No memory of serial key was found on NVS");
        }
        else
        {
            if (this->error == ESP_ERR_NVS_NOT_FOUND)
            {
                setSerialNumber(" ");
                this->error = nvs_get_str(this->handle_NVS, this->key_serial, NULL, &max_size);
            }

            if (this->serial_ret != NULL)
            {
                free(this->serial_ret);
            }

            this->serial_ret = (char*)malloc(max_size * sizeof(char));

            this->error = nvs_get_str(this->handle_NVS, this->key_serial, this->serial_ret, &max_size);

            if (this->error != ESP_OK) 
            {
                ESP_LOGE(TAGE, "Get serial number failed");
            }
            else
            {
                return this->serial_ret;
            }
        }
    }

    return " ";
}

char* Nvs::getDeviceName()
{
    return this->value_device;
}

char* Nvs::getSerialNumber()
{
    return this->value_serial;
}

void Nvs::setDeviceName(char* name) 
{
    this->error = nvs_open(this->namespace_NVS, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        ESP_LOGE(TAGE, "Failed to open in sett device name");
    }
    else 
    {
        if (strlen(name) == 0) 
        {
            ESP_LOGW(TAGW, "Cannot store an empty value in device name");
        }
        else 
        {
            this->error = nvs_set_str(this->handle_NVS, this->key_device, name);

            if (this->error != ESP_OK) 
            {
                ESP_LOGE(TAGE, "Set device name failed");
            }
            else 
            {
                this->error = nvs_commit(this->handle_NVS);

                if (this->error != ESP_OK) 
                {
                    ESP_LOGE(TAGE, "Couldn't commit in set device");
                }
                else
                {
                    if (this->value_device != NULL)
                    {
                        free(this->value_device);
                    }
                    this->value_device = (char*)malloc(strlen(name) * sizeof(char)); //getDeviceName()
                    strcpy(this->value_device, name);
                }
            }
        }
    }
}
void Nvs::setSerialNumber(char* number) 
{    
    this->error = nvs_open(this->namespace_NVS, NVS_READWRITE, &this->handle_NVS);

    if (this->error != ESP_OK) 
    {
        ESP_LOGE(TAGE, "Failed to open in sett serial number");
    }
    else
    {
        if (strlen(number) == 0) 
        {
            ESP_LOGW(TAGW, "Cannot store an empty value in serial number");
        }
        else
        {
            this->error = nvs_set_str(this->handle_NVS, this->key_serial, number); // try to set string to nvs
            
            if (this->error != ESP_OK)
            {
                ESP_LOGE(TAGE, "Set device serial failed");
            }
            else 
            {
                this->error = nvs_commit(this->handle_NVS);

                if (this->error != ESP_OK) 
                {
                    ESP_LOGE(TAGE, "Couldn't commit in set serial");
                }
                else
                {
                    if (this->value_serial != NULL)
                    {
                        free(this->value_serial);
                    }
                    this->value_serial = (char*)malloc(strlen(number) * sizeof(char)); //getSerialNumber()
                    strcpy(this->value_serial, number);
                }
            }
        }
    }
}

/* Used in getting data from nvs
                this->value_device = (char*)malloc(strlen(ret) * sizeof(char));
                strcpy(this->value_device, ret);

                free(ret);
*/
