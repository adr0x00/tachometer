#ifndef IR_SENSOR_H 
#define IR_SENSOR_H 

#define IR_PIN      GPIO_PIN_1
#define IR_PORT     GPIOA 

#define IR_EXTI     EXTI1_IRQn 

#include "main.h"

extern unsigned long ir_count; 

void ir_gpio_init(void);
#endif // IR_SENSOR_H 
