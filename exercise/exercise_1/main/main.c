#include <stdio.h>
#include <string.h>
#include "esp_log.h"

#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_MAGENTA "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RESET "\033[0m"
#define WORLD_COUNT 1
#define NEW_LINE "\n"
#define COLOR_AMOUNT 7

#define PRINTF_COLOR(color, format_string, ...) \
    printf("%s" format_string "%s", color, ##__VA_ARGS__, ANSI_RESET)

#define PRINTF_GROUP_1(format, ...)      \
    PRINTF_COLOR(ANSI_GREEN, "Group 1 "); \
    PRINTF_COLOR(ANSI_RESET, format, ##__VA_ARGS__)

#define PRINTF_COLOR_LINE(color, format_string, ...) \
    PRINTF_COLOR(ANSI_MAGENTA, "[%s,%d]", __FILE__, __LINE__); \
    PRINTF_COLOR(ANSI_RESET, format_string, ##__VA_ARGS__)

#define PRINTF_COLOR_READY(string_1, string_2, string_3, ...) \
    PRINTF_COLOR(ANSI_RED, string_1);                  \
    PRINTF_COLOR(ANSI_YELLOW, string_2);               \
    PRINTF_COLOR(ANSI_GREEN, string_3)       

const static char *const TAG = "MAIN"; 

 int colorFunc(int index, int size) 
 {
    return (index % size);
 }

void app_main(void)
{
    ESP_LOGI(TAG, "HELLO WORLD for my %d time\n", WORLD_COUNT);

    const char* test_string =  "test";

    PRINTF_COLOR(ANSI_CYAN, "%s" NEW_LINE, test_string); 

    PRINTF_GROUP_1("Hello World %d" NEW_LINE, WORLD_COUNT);

    PRINTF_COLOR_LINE(ANSI_YELLOW, "Hello World %d" NEW_LINE, WORLD_COUNT);

    PRINTF_COLOR_READY("STOP ", " READY ", "GO" NEW_LINE);

    char * colors[] = {ANSI_RED, ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, ANSI_MAGENTA, 
    ANSI_CYAN, ANSI_RESET};

    char* theWord = "pneumonoultramicroscopicsilicovolcanoconiosis";

    int size = strlen(theWord);

    for(int i = 0; i < size; i++) 
    {
        char c[2] = {0};
        c[0] = theWord[i];
        PRINTF_COLOR(colors[colorFunc(i, COLOR_AMOUNT - 1)], "%s", c);
    }
}