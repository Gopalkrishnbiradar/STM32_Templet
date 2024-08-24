/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "lwip.h"
#include "usb_device.h"
#include<stdio.h>
#include<string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern struct netif gnetif;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//UART_HandleTypeDef huart3;
void debugPrint(const char *msg)
{
    while(*msg)
    {
        ITM_SendChar(*msg++);
    }
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
osThreadId_t ledTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
void StartDefaultTask(void *argument);
void ledTask(void *argument);
/* USER CODE BEGIN PFP */

char ip_addr_str[16];

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//PUTCHAR_PROTOTYPE
//{
//  HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
//  return ch;
//}
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
  MX_GPIO_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
  ledTaskHandle = osThreadNew(ledTask, NULL, &defaultTask_attributes);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 224;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}
/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
//
//static void MX_USART3_UART_Init(void)
//{
//
//  /* USER CODE BEGIN USART3_Init 0 */
//
//  /* USER CODE END USART3_Init 0 */
//
//  /* USER CODE BEGIN USART3_Init 1 */
//
//  /* USER CODE END USART3_Init 1 */
//  huart3.Instance = USART3;
//  huart3.Init.BaudRate = 115200;
//  huart3.Init.WordLength = UART_WORDLENGTH_8B;
//  huart3.Init.StopBits = UART_STOPBITS_1;
//  huart3.Init.Parity = UART_PARITY_NONE;
//  huart3.Init.Mode = UART_MODE_TX_RX;
//  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
//  if (HAL_UART_Init(&huart3) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN USART3_Init 2 */
//
//  /* USER CODE END USART3_Init 2 */
//
//}
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ETH_NRST_Pin */
  GPIO_InitStruct.Pin = ETH_NRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ETH_NRST_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for LWIP */
  MX_LWIP_Init();

  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
//	  ethernetif_input(&gnetif);
//
//	  	   /* Handle periodic timers for the LWIP stack */
//	  	   sys_check_timeouts();
//
//	  	   /* USER CODE BEGIN 3 */
//	  	   // Get the IP address from gnetif
//	  	   ip4_addr_t ip = gnetif.ip_addr;
//
//	  	   // Convert IP address to string
//	  	   snprintf(ip_addr_str, sizeof(ip_addr_str), "%s", ip4addr_ntoa(&ip));
//
//	  	   // Send the IP address string over UART 3
//	  //	   HAL_UART_Transmit(&huart3, (uint8_t*)ip_addr_str, strlen(ip_addr_str), HAL_MAX_DELAY);
//	  printf("HIIIii  %s\n\r",ip4addr_ntoa(&ip));
	  printf("HELLOddddd\n");
	  debugPrint("Hello, SWO Debugging!\n");
//
////	  HAL_UART_Transmit(&huart6, buffer, sizeof(buffer), HAL_MAX_DELAY);
//	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//      osDelay(500);
  }
  /* USER CODE END 5 */
}

void ledTask(void *argument){
    for(;;)
    {

        // HAL_UART_Transmit(&huart6, buffer, sizeof(buffer), HAL_MAX_DELAY);
//        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        osDelay(500);

//  	  ethernetif_input(&gnetif);
    	MX_LWIP_Init();

//  		  	ethernet_link_check_state(gnetif);
  	//	  	ethernetif_notify_conn_changed(gnetif);
  		  	ip4_addr_t ip = gnetif.ip_addr;
  		  	char *Ip =ip4addr_ntoa(&ip);
  		  	snprintf(ip_addr_str, sizeof(ip_addr_str), "%s", ip4addr_ntoa(&ip));
//  		  	  ethernetif_input(&gnetif);
//  		  	  sys_check_timeouts();


  	  	   /* Handle periodic timers for the LWIP stack */
//  	  	   sys_check_timeouts();

  	  	   /* USER CODE BEGIN 3 */
  	  	   // Get the IP address from gnetif
//  	  	   ip4_addr_t ip = gnetif.ip_addr;

  	  	   // Convert IP address to string
//  	  	   snprintf(ip_addr_str, sizeof(ip_addr_str), "%s", ip4addr_ntoa(&ip));

  	  	   // Send the IP address string over UART 3
  	  //	   HAL_UART_Transmit(&huart3, (uint8_t*)ip_addr_str, strlen(ip_addr_str), HAL_MAX_DELAY);
//  	  printf("HIIIii  %s\n\r",ip4addr_ntoa(&ip));
//  	  debugPrint("Hello, SWO Debugging!\n");

  //	  HAL_UART_Transmit(&huart6, buffer, sizeof(buffer), HAL_MAX_DELAY);
//  	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        osDelay(500);

    }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM11 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM11) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
