#ifndef IR_SENSOR_H 
#define IR_SENSOR_H 

#define IR_EXTI     EXTI1_IRQn      /* interrupt */ 
#define IR_PIN      GPIO_PIN_1      /* pin */ 
#define IR_PORT     GPIOA           /* port */ 

/* state flag */
#define DEBOUNCE_DELAY  2 // MS 
#define IR_RESET        0
#define IR_SET          1

#include "main.h"

extern unsigned long ir_count; 
extern bool ir_detect_flag;

void ir_gpio_init(void);
bool ir_detect(void);     /* return 1 when detected object (with debounce) */ 
#endif // IR_SENSOR_H 
