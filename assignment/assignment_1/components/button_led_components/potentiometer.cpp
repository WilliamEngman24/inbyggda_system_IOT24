#include "potentiometer.h"

class Potentiometer 
{
    void init(int pin);

    void update();

    int getValue();

    void setOnThreshold(void(*onThreshhold)(int pin));
};