#include "main.h"

void SystemClock_Config(void);

int main(void)
{
  HAL_Init();

  SystemClock_Config();

/* 
  Manual GPIO configuration and LED toggle
  This section was implemented manually.
 */  

  RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
  GPIOB->MODER &= ~(GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1);
  GPIOB->MODER |= GPIO_MODER_MODE0_0;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDER_OSPEED0_0;
  GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD0_0 | GPIO_PUPDR_PUPD1_0);
  GPIOB->BSRR = GPIO_BSRR_BR_0;
  
  while (1)
  {
    HAL_Delay(1000);
    GPIOB->ODR ^= GPIO_ODR_OD0;
  }
}

// End of manual GPIO configuration and LED toggle 

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    while (1);
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1;

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    while (1);
  }
}

