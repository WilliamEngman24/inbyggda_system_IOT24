#include <stdio.h>
#include "helper_component.h"
#include "printer.h"
#include "esp_log.h"

extern "C" 
{
    void app_main(void)
    {
        takeTimeAndPrintEverySecond(5000);
    }
}