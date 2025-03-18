idf_component_register(SRCS "light_sensor.cpp" "motor.cpp" "light_sleep.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES driver
                    REQUIRES esp_adc)
