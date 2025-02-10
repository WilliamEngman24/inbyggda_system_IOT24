#pragma once

#ifndef BUTTON_H
#define BUTTON_H

void init(int pin);

void update();

bool isPressed();

void setOnPressed(void(*onPressed)(int pin));

#endif 