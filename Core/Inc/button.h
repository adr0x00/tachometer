#ifndef  BUTTON_H
#define  BUTTON_H

#define  BUTTON_PIN     GPIO_PIN_0
#define  BUTTON_PORT    GPIOA
#define  BUTTON_EXTI    EXTI0_IRQn

#include "main.h"

void button_gpio_init(void);
#endif //BUTTON_H

