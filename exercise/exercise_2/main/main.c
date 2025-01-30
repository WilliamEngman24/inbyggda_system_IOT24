#include <stdio.h>
#include "helper_component.h"
#include "printer.h"
#include "esp_log.h"

void app_main(void)
{
    int a = func();

    ESP_LOGI("MAIN", "got value %d", a);
}