#ifndef  BUTTON_H
#define  BUTTON_H

#define  BUTTON_PIN     GPIO_PIN_9
#define  BUTTON_PORT    GPIOA

#include "main.h"

void button_gpio_init(void);
#endif //BUTTON_H

