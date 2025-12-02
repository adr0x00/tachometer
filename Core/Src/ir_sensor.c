#include "ir_sensor.h"

/* gloal counter var for ir sensor */
unsigned long ir_count = 0; 
unsigned long last_debounce_time = 0;

/* gloal ir detected flag */
bool ir_detect_flag  = IR_RESET; 
bool last_detect = false; // 0


void ir_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin     = IR_PIN; 
    GPIO_InitStruct.Mode    = GPIO_MODE_IT_RISING; 
    GPIO_InitStruct.Speed   = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Pull    = GPIO_PULLDOWN; 
    HAL_GPIO_Init(IR_PORT, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(IR_EXTI); // Enable interrupt
}


