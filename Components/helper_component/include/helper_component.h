#pragma once

#include <iostream>
#include <string>

#include "freertos/FreeRTOS.h"

#define ANSI_RED "\033[0;31m"
#define ANSI_GREEN "\033[0;32m"
#define ANSI_YELLOW "\033[0;33m"
#define ANSI_BLUE "\033[0;34m"
#define ANSI_MAGENTA "\033[0;35m"
#define ANSI_CYAN "\033[0;36m"
#define ANSI_RESET "\033[0m"
#define WORLD_COUNT 1
#define NEW_LINE "\n"
#define COLOR_AMOUNT 6

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

using std::string;

void printNumbers(int start, int stop);

void takeTimeAndPrintEverySecond(int time);

int multiply(int a, int b);

void rainbowPrint(string theWord);

