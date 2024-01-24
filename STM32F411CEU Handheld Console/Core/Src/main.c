/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "STM32_Handheld_Console.h"
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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_SPI1_Init();
	MX_FATFS_Init();
	/* USER CODE BEGIN 2 */
	init_display();
	clear_screen();

	/*for(uint8_t y = 0; y < DISPLAY_HEIGHT; ++y)
	 {
	 for(uint8_t x = 0; x < DISPLAY_WIDTH; ++x)
	 {
	 draw_pixel(x, y, (y * DISPLAY_WIDTH + x) & 0xFF);
	 }
	 }*/
	//draw_rect(20, 10, 200, 90, rgb888_to_rgb332(255, 0, 0));
	draw_rect(20, 10, 200, 90, rgb888_to_rgb332(0, 200, 0));
	//fill_rect(40, 80, 100, 75, rgb888_to_rgb332(0, 200, 0));
	fill_rect(40, 80, 100, 75, rgb888_to_rgb332(255, 0, 0));
	set_text_area(157, 5, 227, 11);
	uint8_t assault_text_color = rgb888_to_rgb332(255, 255, 28);
	set_text_color(assault_text_color, rgb888_to_rgb332(0, 0, 0));
	set_text_wrap(1);

	const char *assault_text = "POLiS SALDIRISI  ///  @@@  ///  POLiS SALDIRISI";
	//print_str("STM32F411CEU Handheld Gaming Console Print String And Text Area Test");

	update_display();

	int16_t x = 200;
	uint32_t frames = 0, frames_to_draw_display = 0, ticks = 0;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		//ticks = HAL_GetTick();
		frames = HAL_GetTick();
		clear_screen();
		draw_v_line(151, 1, 3, assault_text_color);
		draw_v_line(151, 13, 3, assault_text_color);
		draw_v_line(227, 1, 3, assault_text_color);
		draw_v_line(227, 13, 3, assault_text_color);
		draw_h_line(151, 1, 3, assault_text_color);
		draw_h_line(151, 15, 3, assault_text_color);
		draw_h_line(225, 1, 3, assault_text_color);
		draw_h_line(225, 15, 3, assault_text_color);
		fill_rect(230, 1, 9, 9, assault_text_color);
		draw_pixel(234, 3, 0);
		draw_pixel(232, 6, 0);
		draw_pixel(236, 6, 0);
		draw_v_line(233, 4, 2, 0);
		draw_v_line(235, 4, 2, 0);
		draw_h_line(232, 7, 5, 0);
		set_text_area(157, 5, 227, 11);
		set_cursor(x, 5);
		print_str(assault_text);

		if (x < 151 - 32 * 6)
			x = 151;
		x -= 1;

		set_text_area(0, 0, 239, 159);
		print_str("TPF: ");
		frames = HAL_GetTick() - frames;
		print_int(frames);
		print_str(" ms\nDT: ");
		print_int(frames_to_draw_display);
		print_str(" ms");

		frames_to_draw_display = HAL_GetTick();

		update_display();

		frames_to_draw_display = HAL_GetTick() - frames_to_draw_display;

		//while(HAL_GetTick() <= ticks + 50);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
	RCC_OscInitStruct.PLL.PLLM = 12;
	RCC_OscInitStruct.PLL.PLLN = 96;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
			TFT_D0_Pin | TFT_D1_Pin | TFT_D2_Pin | TFT_D10_Pin | TFT_D12_Pin
					| TFT_D13_Pin | TFT_D14_Pin | TFT_D15_Pin | TFT_D3_Pin
					| TFT_D4_Pin | TFT_D5_Pin | TFT_D6_Pin | TFT_D7_Pin
					| TFT_D8_Pin | TFT_D9_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, TFT_WR_Pin | TFT_RS_Pin | TFT_RST_Pin | TFT_CS_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : TFT_D0_Pin TFT_D1_Pin TFT_D2_Pin TFT_D10_Pin
	 TFT_D12_Pin TFT_D13_Pin TFT_D14_Pin TFT_D15_Pin
	 TFT_D3_Pin TFT_D4_Pin TFT_D5_Pin TFT_D6_Pin
	 TFT_D7_Pin TFT_D8_Pin TFT_D9_Pin */
	GPIO_InitStruct.Pin = TFT_D0_Pin | TFT_D1_Pin | TFT_D2_Pin | TFT_D10_Pin
			| TFT_D12_Pin | TFT_D13_Pin | TFT_D14_Pin | TFT_D15_Pin | TFT_D3_Pin
			| TFT_D4_Pin | TFT_D5_Pin | TFT_D6_Pin | TFT_D7_Pin | TFT_D8_Pin
			| TFT_D9_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : TFT_WR_Pin TFT_RS_Pin TFT_RST_Pin TFT_CS_Pin */
	GPIO_InitStruct.Pin = TFT_WR_Pin | TFT_RS_Pin | TFT_RST_Pin | TFT_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
