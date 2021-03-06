/**
 ******************************************************************************
 * @file         stm32f4xx_hal_msp.c
 * @brief        This file provides code for the MSP Initialization
 *               and de-Initialization codes.
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

#include "stm32f4xx_hal.h"

#include "board_config.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init */
}

/**
 * @brief CRC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
    if (hcrc->Instance == CRC) {
        /* Peripheral clock enable */
        __HAL_RCC_CRC_CLK_ENABLE();
    }
}

/**
 * @brief CRC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcrc: CRC handle pointer
 * @retval None
 */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
    if (hcrc->Instance == CRC) {
        /* Peripheral clock disable */
        __HAL_RCC_CRC_CLK_DISABLE();
    }
}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hi2c->Instance == I2C1) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /*
         * I2C1 GPIO Configuration
         * PB7     ------> I2C1_SDA
         * PB8     ------> I2C1_SCL
         */
        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();

    } else if (hi2c->Instance==I2C2) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /*
         * I2C2 GPIO Configuration
         * PB10     ------> I2C2_SCL
         * PB9     ------> I2C2_SDA
         */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_I2C2;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();

    }
}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
    if (hi2c->Instance == I2C1) {
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /*
         * I2C1 GPIO Configuration
         * PB7     ------> I2C1_SDA
         * PB8     ------> I2C1_SCL
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    } else if (hi2c->Instance == I2C2) {
        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /*
         * I2C2 GPIO Configuration
         * PB10     ------> I2C2_SCL
         * PB9      ------> I2C2_SDA
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

    }
}

/**
 * @brief SPI MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (hspi->Instance == SPI1) {
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /*
         * SPI1 GPIO Configuration
         * PA5     ------> SPI1_SCK
         * PA7     ------> SPI1_MOSI
         */
        GPIO_InitStruct.Pin = DISP_SCK_Pin|DISP_MOSI_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    } else if(hspi->Instance == SPI2) {
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /*
         * SPI2 GPIO Configuration
         * PB15     ------> SPI2_MOSI
         * PC7      ------> SPI2_SCK
         */
        GPIO_InitStruct.Pin = LED_SDI_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(LED_SDI_GPIO_Port, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = LED_CLK_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
        HAL_GPIO_Init(LED_CLK_GPIO_Port, &GPIO_InitStruct);

    }
}

/**
 * @brief SPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
    if (hspi->Instance == SPI1) {
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /*
         * SPI1 GPIO Configuration
         * PA5     ------> SPI1_SCK
         * PA7     ------> SPI1_MOSI
         */
        HAL_GPIO_DeInit(GPIOA, DISP_SCK_Pin|DISP_MOSI_Pin);

    } else if(hspi->Instance == SPI2) {
        /* Peripheral clock disable */
        __HAL_RCC_SPI2_CLK_DISABLE();

        /*
         * SPI2 GPIO Configuration
         * PB15     ------> SPI2_MOSI
         * PC7      ------> SPI2_SCK
         */
        HAL_GPIO_DeInit(LED_SDI_GPIO_Port, LED_SDI_Pin);

        HAL_GPIO_DeInit(LED_CLK_GPIO_Port, LED_CLK_Pin);

    }
}

/**
 * @brief TIM_Encoder MSP Initialization
 * This function configures the hardware resources used in this example
 * @param htim_encoder: TIM_Encoder handle pointer
 * @retval None
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* htim_encoder)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (htim_encoder->Instance == TIM1) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /*
         * TIM1 GPIO Configuration
         * PA8     ------> TIM1_CH1
         * PA9     ------> TIM1_CH2
         */
        GPIO_InitStruct.Pin = ENC_CH1_Pin|ENC_CH2_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* TIM1 interrupt Init */
        HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
        HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
        HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

    }
}

/**
 * @brief TIM_PWM MSP Initialization
 * This function configures the hardware resources used in this example
 * @param htim_pwm: TIM_PWM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
    if (htim_pwm->Instance == TIM3) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM3_CLK_ENABLE();

    } else if(htim_pwm->Instance == TIM9) {
        /* Peripheral clock enable */
        __HAL_RCC_TIM9_CLK_ENABLE();

    }
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (htim->Instance == TIM3) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
        /*
         * TIM3 GPIO Configuration
         * PC6     ------> TIM3_CH1
         */
        GPIO_InitStruct.Pin = LED_OE_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
        HAL_GPIO_Init(LED_OE_GPIO_Port, &GPIO_InitStruct);

    } else if(htim->Instance == TIM9) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /*
         * TIM9 GPIO Configuration
         * PA2     ------> TIM9_CH1
         */
        GPIO_InitStruct.Pin = BUZZ_DIN_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF3_TIM9;
        HAL_GPIO_Init(BUZZ_DIN_GPIO_Port, &GPIO_InitStruct);

    }
}

/**
 * @brief TIM_Encoder MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param htim_encoder: TIM_Encoder handle pointer
 * @retval None
 */
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* htim_encoder)
{
    if (htim_encoder->Instance == TIM1) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM1_CLK_DISABLE();

        /*
         * TIM1 GPIO Configuration
         * PA8     ------> TIM1_CH1
         * PA9     ------> TIM1_CH2
         */
        HAL_GPIO_DeInit(GPIOA, ENC_CH1_Pin|ENC_CH2_Pin);

        /* TIM1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
        HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM11_IRQn);
        HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);

    }
}

/**
 * @brief TIM_PWM MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param htim_pwm: TIM_PWM handle pointer
 * @retval None
 */
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{
    if (htim_pwm->Instance == TIM3) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM3_CLK_DISABLE();

    } else if(htim_pwm->Instance == TIM9) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM9_CLK_DISABLE();

    }
}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (huart->Instance == USART1) {
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /*
         * USART1 GPIO Configuration
         * PA10     ------> USART1_RX
         * PB6      ------> USART1_TX
         */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    }
}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1) {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /*
         * USART1 GPIO Configuration
         * PA10     ------> USART1_RX
         * PB6      ------> USART1_TX
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    }
}
