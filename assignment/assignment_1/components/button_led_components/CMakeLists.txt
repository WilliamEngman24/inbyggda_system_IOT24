idf_component_register(SRCS "button.cpp" "led_analog.cpp" "led_binary.cpp" "potentiometer.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES driver
                    REQUIRES esp_adc
                    REQUIRES esp_driver_ledc)
