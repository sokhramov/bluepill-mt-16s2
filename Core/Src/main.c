/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
const char Text1_1[Len1]={0x20, 0x20, 0x20, 0x20, 0xCC, 0xDD, 0xCB, 0xD2, 0x20, 0x31, 0x36, 0x53, 0x32, 0x20, 0x20, 0x20};
const char Text2_1[Len2]={0x20, 0x20, 0x49, 0x43, 0x20, 0x4E, 0x52, 0x4E, 0x55, 0x20, 0x4D, 0x45, 0x50, 0x48, 0x49, 0x20};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void Clear_Display(void);
void Display_Init(void);
void LCD_D(uint8_t DATA);

void WriteCmd(uint8_t b);
void WriteData(uint8_t b);
void WriteByte(uint8_t b, uint8_t cd);
/* USER CODE BEGIN PFP */

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
  //int i;
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
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  Display_Init();  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    for(uint8_t i = 1; i <= 16; i++)
    {
      HAL_Delay(10);
      Clear_Display();
      WriteCmd(0x80);
      for(uint8_t j = Len1 - i; j < Len1; j++)
      {
        WriteData(Text1_1[j]);
      }
      
      WriteCmd(0x80 + 0x40);
      for(uint8_t k = Len2 - i; k < Len2; k++)
      {
        WriteData(Text2_1[k]);
      }
    }
    for(uint8_t i = 1; i <= 16; i++)
    {
      HAL_Delay(10);
      Clear_Display();
      WriteCmd(0x80 + i);
      for(uint8_t j = 0; j < Len1 - i; j++)
      {
        WriteData(Text1_1[j]);
      }
      
      WriteCmd(0x80 + 0x40 + i);
      for(uint8_t k = 0; k < Len2 - i; k++)
      {
        WriteData(Text2_1[k]);
        HAL_Delay(2);
      }
    }
  }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Display_Init(void)
{

  HAL_GPIO_WritePin(E_PORT, E_PIN, 0); 
	WriteCmd(0x2A);		//SET 4-bit mode
	WriteCmd(0x0C);		//SET cursor mode
	WriteCmd(0x01);		//CLEAR display
	WriteCmd(0x06);		//SET cursor direction
}

//set data pins values
void LCD_D(uint8_t DATA)
{
  HAL_GPIO_WritePin(B4_PORT, B4_PIN, 0x01 & DATA);
  HAL_GPIO_WritePin(B5_PORT, B5_PIN, 0x01 & (DATA >> 1));
  HAL_GPIO_WritePin(B6_PORT, B6_PIN, 0x01 & (DATA >> 2));
  HAL_GPIO_WritePin(B7_PORT, B7_PIN, 0x01 & (DATA >> 3));
}
void WriteCmd(uint8_t b)
{
  WriteByte(b,0);
}

void WriteData(uint8_t b)
{
  WriteByte(b,1);
}

void WriteByte(uint8_t b, uint8_t cd) {

	HAL_GPIO_WritePin(RW_PORT, RW_PIN, 0);
  HAL_GPIO_WritePin(A0_PORT, A0_PIN, cd); 
  
  //write bits 7-4
  LCD_D(b>>4); 
	HAL_Delay(1);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1); 
  HAL_Delay(1);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0); 
  HAL_Delay(1);
  
  //write bits 3-0
	LCD_D(b&0x0F);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 1); 
  HAL_Delay(1);
	HAL_GPIO_WritePin(E_PORT, E_PIN, 0); 
  HAL_Delay(1);
}

void Clear_Display(void)
{
  WriteCmd(0x01);
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

#ifdef  USE_FULL_ASSERT
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

