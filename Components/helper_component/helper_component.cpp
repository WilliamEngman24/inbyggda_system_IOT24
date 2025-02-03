#include "helper_component.h"

void printNumbers(int start, int stop) 
{
    for (int i = start; i <= stop; i++) 
    {
        printf("%d\n", i);
    }
}

void takeTimeAndPrintEverySecond(int time) 
{

    int max_ticks = pdMS_TO_TICKS(time);
    int current_ticks = 0;
    int seconds = 0;
    if (!(time <= 0)) 
    {
        do 
        {
            current_ticks += pdMS_TO_TICKS(1000); //add time
            seconds = current_ticks/pdMS_TO_TICKS(1000);

            vTaskDelay(100); //delay one sec
            printf("%d\n", seconds); //print second
        } while (current_ticks < max_ticks);
    }
}

int multiply(int a, int b) 
{
    return a * b;
}

int colorFunc(int index, int size) 
 {
    return (index % size);
 }

 void rainbowPrint(string theWord) 
 {
    int size = theWord.length();

    char* colors[COLOR_AMOUNT] = {ANSI_RED, ANSI_GREEN, ANSI_YELLOW, ANSI_BLUE, ANSI_MAGENTA, 
    ANSI_CYAN};

    for(int i = 0; i < size-1; i++) 
    {
        char c[2] = {0};
        c[0] = theWord[i];
        PRINTF_COLOR(colors[colorFunc(i, COLOR_AMOUNT)], "%s", c);
    }
 }
