#include "i2c.h"

I2C_HandleTypeDef hi2c1;


HAL_I2C_StateTypeDef i2c_init(void)
{
    __HAL_RCC_I2C1_CLK_ENABLE();
    i2c_gpio_init();
    hi2c1.Instance = I2C1; 
    hi2c1.Init.ClockSpeed = SET_SPEED; 
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0x0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    return HAL_I2C_Init(&hi2c1);  /* retun status i2c bus */ 
}

/* Init GPIO for I2C module */ 
void i2c_gpio_init(void)
{
   __HAL_RCC_GPIOB_CLK_ENABLE();
   GPIO_InitTypeDef GPIO_InitStruct;
   GPIO_InitStruct.Pin      = SDA | SCL;
   GPIO_InitStruct.Mode     = GPIO_MODE_AF_OD; 
   GPIO_InitStruct.Speed    = GPIO_SPEED_FREQ_HIGH;
   HAL_GPIO_Init(I2C_PORT, &GPIO_InitStruct);
}