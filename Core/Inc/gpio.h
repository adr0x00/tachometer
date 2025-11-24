#ifndef  GPIO_H
#define  GPIO_h

#define LED_PIN        GPIO_PIN_13
#define LED_PORT       GPIOC

#define BUTTON_PIN     GPIO_PIN_10
#define BUTTON_PORT    GPIOC

#include "stm32f1xx_hal.h"
void gpio_init(void); 
#endif// GPIO_H