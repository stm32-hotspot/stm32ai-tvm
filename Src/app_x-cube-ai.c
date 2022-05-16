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
 * \file app_x-cube-ai.c
 * \brief AI program body
 */

#ifdef __cplusplus
 extern "C" {
#endif

#include <string.h>
#include "app_x-cube-ai.h"
#include "bsp_ai.h"
#ifdef USE_VALID
#include "aiValidation.h"
#else
#include "aiSystemPerformance.h"
#endif

/* USER CODE BEGIN includes */

/* USER CODE END includes */

/*************************************************************************
  *
  */
void MX_X_CUBE_AI_Init(void)
{
    MX_UARTx_Init();
#ifdef USE_VALID
    aiValidationInit();
#else
    aiSystemPerformanceInit();
#endif
    /* USER CODE BEGIN 0 */
    /* USER CODE END 0 */
}

void MX_X_CUBE_AI_Process(void)
{
#ifdef USE_VALID
    aiValidationProcess();
#else
    aiSystemPerformanceProcess();
#endif
    HAL_Delay(1000); /* delay 1s */
    /* USER CODE BEGIN 1 */
    /* USER CODE END 1 */
}
