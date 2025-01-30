#include <stdio.h>
#include "helper_component.h"
#include "printer.h"
#include "esp_log.h"

extern "C" 
{
    void app_main(void)
    {
        int a = exercise_2::func();

        ESP_LOGI("MAIN", "got value %d", a);

        a = inbyggda_IOT24::func();

        ESP_LOGI("MAIN", "got value %d", a);
    }
}