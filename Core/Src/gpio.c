#include "gpio.h"

void gpio_init(void)
{   // INIT LED PIN 
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin     = LED_PIN; 
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW; 
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}