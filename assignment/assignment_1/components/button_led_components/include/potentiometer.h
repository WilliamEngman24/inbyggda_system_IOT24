#pragma once

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer 
{
    void init(int pin);

    void update();

    int getValue();

    void setOnThreshold(void(*onThreshhold)(void));
};

#endif 