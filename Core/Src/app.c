#include "app.h"

unsigned long tmr = 0;
unsigned int  rpm = 0;

void app_run(void)
{
    while (1)
  {
    /* USER CODE END WHILE */

    if (ir_detect_flag){
        ir_detect_flag = RESET; 
        ir_count++;
    }

    if (HAL_GetTick() - tmr >= TIME) {  // выполняется раз в секунду.
        tmr = HAL_GetTick();
        // тут должны произойти рассчеты полученных данных. 
        rpm = RESET; // last value 
        rpm = (ir_count * MINUTE); // get RPM  
        ir_count = RESET; // reset for next cycle 
    }
    /* USER CODE BEGIN 3 */
    //display_digital_with_bar(rpm);  // favorite 
    //display_compact_rpm( rpm);
      display_minimal_rpm(rpm);
  }
}