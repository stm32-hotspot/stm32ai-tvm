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
 * \file aiTestTvmHelper.h
 * \brief STM32 Helper functions for STM32 AI test application
 */

#ifndef __AI_TEST_TVM_HELPER_H__
#define __AI_TEST_TVM_HELPER_H__

#include <stdint.h>

#include "ai_runtime_api.h"
#include "ai_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

void aiPlatformVersion(void);

void aiLogErr(const char *fct, const char *err);
void aiPrintLayoutBuffer(const char *msg, int idx, ai_tensor * tensor);
void aiPrintNetworkInfo(ai_model_info *nn, ai_handle hdl);

#if defined(NO_X_CUBE_AI_RUNTIME) && NO_X_CUBE_AI_RUNTIME == 1
#include "ai_platform.h"
void aiTvmToReport(ai_model_info *nn, ai_handle hdl, ai_network_report *report);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AI_TEST_TVM_HELPER_H__ */
