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

#define LIGHT_THRESHOLD 5

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
        light_right->init(LIGHT_SENSOR_RIGHT);

        LightSensor* light_left = new LightSensor;
        light_left->init(LIGHT_SENSOR_LEFT);

        int light_difference = 0;


        while(1)
        {
            btn_sleep->update();

            btn_right->update();
            btn_left->update();

            light_right->update();
            light_left->update();

            if(light_left->getValue() > light_right->getValue()) //if left is larger than right
            {
                light_difference = light_left->getValue() - light_right->getValue();

                if (light_difference > LIGHT_THRESHOLD) 
                {
                    //activates rotation to the left
                    if (!btn_right->getPressed()) //as long as the button isn't pressed 
                    {
                        
                    }
                }

            }
            else if(light_right->getValue() > light_left->getValue()) //if right is larger than left
            {
                light_difference = light_right->getValue() - light_left->getValue();

                if (light_difference > LIGHT_THRESHOLD) 
                {
                    //activates rotation to the right
                    if (!btn_right->getPressed()) //as long as the button isn't pressed 
                    {

                    }

                }

            }
            vTaskDelay(10);
        }

    }
}