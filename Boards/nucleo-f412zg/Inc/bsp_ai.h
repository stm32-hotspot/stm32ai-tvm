/*
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 */

/*!
 * \file bsp_ai.h
 * \brief Link to board resources
 */

#ifndef BSP_H
#define BSP_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32f4xx.h"
#include "app_x-cube-ai.h"
#define UartHandle huart3
#define MX_UARTx_Init MX_USART3_UART_Init
void MX_USART3_UART_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_H */
