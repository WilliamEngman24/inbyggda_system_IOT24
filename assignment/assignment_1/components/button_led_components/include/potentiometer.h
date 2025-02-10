#pragma once

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

void init(int pin);

void update();

int getValue();

void setOnThreshold(void(*onThreshhold)(int pin));

#endif 