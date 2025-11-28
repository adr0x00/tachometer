#ifndef   I2C_H
#define   I2C_H

#define I2C_PORT    GPIOB
#define SDA         GPIO_PIN_7
#define SCL         GPIO_PIN_6

#define SET_SPEED   100000

#include "main.h"

extern I2C_HandleTypeDef hi2c1;

HAL_I2C_StateTypeDef i2c_init(void); 
void i2c_gpio_init(void);
/*
1) choose module headler 
2) define pins 
3) enable clock module 
*/
#endif // I2C_H 