#include "led.h"

void led_gpio_init(void)
{   
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOC_CLK_ENABLE(); 
    // INIT LED 
    GPIO_InitStruct.Pin     = LED_PIN; 
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP; 
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW; 
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}


