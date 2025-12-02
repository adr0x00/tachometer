/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "led.h"
#include "button.h"
#include "ir_sensor.h"
#include "timer.h"
#include "i2c.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "app.h"

/* FreeRTOS includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>
/*
    Проблемы 
    FreeRTOS использует systick 
    а микроконтроллеру нужно тактироваться от другого мк 
*/ 
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void display_digital_with_bar(int rpm);
void display_compact_rpm(int rpm);
void display_minimal_rpm(int rpm);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  led_gpio_init();
  button_gpio_init();
  ir_gpio_init(); 
  i2c_init();
  /* USER CODE END 2 */ 
  ssd1306_Init();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  app_run();
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // не забудь поставить условие выбора пина , что бы кнопка не поднимала флаг 
  ir_detect_flag = IR_SET; 
}

void display_digital_with_bar(int rpm)
{
    char tmp_buffer[8];
    int max_rpm = 8000;
    
    ssd1306_Fill(White);
    
    // Большие цифры RPM
    ssd1306_SetCursor(20, 0);
    itoa(rpm, tmp_buffer, 10);
    ssd1306_WriteString(tmp_buffer, Font_16x26, Black);
    
    // Подпись под цифрами
    ssd1306_SetCursor(55, 30);
    ssd1306_WriteString("RPM", Font_7x10, Black);
    
    // Прогресс-бар
    ssd1306_DrawRectangle(10, 45, 118, 55, Black);
    
    // Заполнение прогресс-бара
    int bar_width = (rpm * 108) / max_rpm;
    if (bar_width > 108) bar_width = 108;
    if (bar_width < 0) bar_width = 0;
    
    ssd1306_FillRectangle(11, 46, 11 + bar_width, 54, Black);
    
    // Деления на прогресс-баре
    for (int i = 0; i <= 4; i++) {
        int x_pos = 10 + i * 27;
        ssd1306_Line(x_pos, 55, x_pos, 60, Black);
        
        // Подписи делений
        ssd1306_SetCursor(x_pos - 5, 62);
        char mark[4];
        itoa(i * (max_rpm/4), mark, 10);
        ssd1306_WriteString(mark, Font_6x8, Black);
    }
    
    ssd1306_UpdateScreen();
}

void display_compact_rpm(int rpm)
{
    char tmp_buffer[8];
    int max_rpm = 8000;
    
    ssd1306_Fill(White);
    
    // Рисуем круговой индикатор
    int radius = 20;
    int center_x = 20;
    int center_y = 32;
    
    // Внешний круг
    ssd1306_DrawCircle(center_x, center_y, radius, Black);
    
    // Заливка в зависимости от RPM (имитация цвета)
    int fill_angle = (rpm * 360) / max_rpm;
    if (fill_angle > 360) fill_angle = 360;
    
    // Рисуем заполненную часть
    for (int r = 1; r < radius; r++) {
        // Это упрощенная версия - для реального использования лучше использовать DrawArc
        // Здесь рисуем линии от центра к краю
        for (int angle = 0; angle < fill_angle; angle += 5) {
            float rad = angle * 3.14159 / 180;
            int x = center_x + r * cos(rad);
            int y = center_y - r * sin(rad);
            ssd1306_DrawPixel(x, y, Black);
        }
    }
    
    // Большие цифры
    ssd1306_SetCursor(50, 10);
    itoa(rpm, tmp_buffer, 10);
    ssd1306_WriteString(tmp_buffer, Font_16x26, Black);
    
    // Статусная строка
    ssd1306_SetCursor(50, 40);
    ssd1306_WriteString("RPM", Font_11x18, Black);
    
    // Индикатор зоны (текстовый)
    ssd1306_SetCursor(50, 55);
    if (rpm < max_rpm * 0.6) {
        ssd1306_WriteString("NORMAL", Font_6x8, Black);
    } else if (rpm < max_rpm * 0.8) {
        ssd1306_WriteString("WARNING", Font_6x8, Black);
    } else {
        ssd1306_WriteString("DANGER!", Font_6x8, Black);
    }
    
    ssd1306_UpdateScreen();
}

void display_minimal_rpm(int rpm)
{
    char tmp_buffer[8];
    
    ssd1306_Fill(Black); // Инвертируем цвета для стиля
    
    // Очень большие цифры
    ssd1306_SetCursor(10, 5);
    itoa(rpm, tmp_buffer, 10);
    
    // Центрируем цифры
    int len = strlen(tmp_buffer);
    int x_pos = (128 - len * 16) / 2; // Для Font_16x26 примерно
    ssd1306_SetCursor(x_pos > 0 ? x_pos : 0, 5);
    
    ssd1306_WriteString(tmp_buffer, Font_16x26, White);
    
    // Тонкая линия под цифрами
    ssd1306_Line(20, 40, 108, 40, White);
    
    // Текст внизу
    ssd1306_SetCursor(52, 45);
    ssd1306_WriteString("RPM", Font_11x18, White);
    
    // Небольшая дополнительная информация
    ssd1306_SetCursor(0, 58);
    char info[16];
    sprintf(info, "~%d%%", (rpm * 100) / 8000);
    ssd1306_WriteString(info, Font_6x8, White);
    
    ssd1306_UpdateScreen();
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/*
  while button is pressed , we're measuring rpm. - it's main logic. 
  Traning EXTI complete.. 
  Traning I2C 
  Traning Timer

  alghoritm , we need count rev per second. 
  how count rev per second ? 
  Алгоритмы для измерения
  Frequency Measurement - измеряем кол-во импульсов за 1 с и * 60 с для получения в минуту. 
  Period Measurement    - измеряем период между импульсами
  
  super loop = ОПРАШИВАЕМ ДАТЧИКИ -> РАССЧИТЫВАЕМ ОБОРОТЫ -> ОТОБРАЖАЕМ ПОЛЬЗОВАТЕЛЮ
*/ 