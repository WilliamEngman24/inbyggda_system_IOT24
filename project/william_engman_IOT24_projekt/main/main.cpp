#include <stdio.h>
#include "freertos/FreeRTOS.h"

#include "button.h"

#include "light_sensor.h"
#include "motor.h"

#define BUTTON_RIGHT 1
#define BUTTON_LEFT 2
#define BUTTON_SLEEP 3

#define MOTOR_PWM 4
#define MOTOR_ROTATION 5

#define LIGHT_SENSOR_RIGHT 6
#define LIGHT_SENSOR_LEFT 7

void stop_going_right()
{
    //motor cannot go right
}
void stop_going_left()
{
    //motor cannot go left
}
void light_sleep_mode() 
{
    //if sleep is true
        //turn sleep off
    
    //else
        //turn sleep on (wake up 10 sec interval)
}

extern "C"
{
    void app_main(void)
    {
        Button* btn_sleep = new Button;
        btn_sleep->init(BUTTON_RIGHT, true);

        Button* btn_right = new Button;
        btn_right->init(BUTTON_RIGHT, true);
        btn_right->setOnPressed(stop_going_right);

        Button* btn_left = new Button;
        btn_left->init(BUTTON_LEFT, true);
        btn_left->setOnPressed(stop_going_left);

        LightSensor* light_right = new LightSensor;
        LightSensor* light_left = new LightSensor;


        while(1)
        {
            btn_sleep->update();

            btn_right->update();
            btn_left->update();
            vTaskDelay(10);
        }

    }
}