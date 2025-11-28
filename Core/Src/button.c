#include "button.h"

void button_gpio_init(void){
    // INIT BUTTON 
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin     = BUTTON_PIN; 
    GPIO_InitStruct.Mode    = GPIO_MODE_IT_FALLING; 
    GPIO_InitStruct.Pull    = GPIO_PULLUP; 
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW; 
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
 
    HAL_NVIC_EnableIRQ(BUTTON_EXTI); // Enable interrupt
}

