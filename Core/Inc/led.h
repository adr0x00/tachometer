#ifndef  GPIO_H
#define  GPIO_h

#define LED_PIN        GPIO_PIN_13
#define LED_PORT       GPIOC

#include "main.h"

void led_gpio_init(void); 
#endif// GPIO_H