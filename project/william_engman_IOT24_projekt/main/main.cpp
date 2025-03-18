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

#define LIGHT_SENSOR_RIGHT ADC_CHANNEL_0
#define LIGHT_SENSOR_LEFT ADC_CHANNEL_1


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
        /*
        Button* btn_sleep = new Button;
        btn_sleep->init(BUTTON_RIGHT, true);

        Button* btn_left = new Button;
        btn_left->init(BUTTON_LEFT, true);

        Button* btn_right = new Button;
        btn_right->init(BUTTON_RIGHT, true);

        LightSensor* light_left = new LightSensor;
        light_left->init(LIGHT_SENSOR_LEFT);

        LightSensor* light_right = new LightSensor;
        light_right->init(LIGHT_SENSOR_RIGHT);
        */
        Motor* motor = new Motor;
        motor->init(MOTOR_PWM, MOTOR_ROTATION);


        while(1)
        {
            /*
            btn_sleep->update();

            btn_right->update();
            btn_left->update();

            light_right->update();
            light_left->update();
            */
           // light_left->getValue(), light_right->getValue(), btn_left->getPressed(), btn_right->getPressed()
            motor->update(1,1,1,1);

            vTaskDelay(10);
        }
    }
}