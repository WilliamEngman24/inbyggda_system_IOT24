#include <stdio.h>
#include "esp_log.h"

const static char *const TAG = "MAIN"; 

void app_main(void)
{
    ESP_LOGI(TAG, "HELLO WORLD for my %d time", 1);
}