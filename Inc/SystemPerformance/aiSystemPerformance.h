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
 * \file aiSystemPerformance.h
 * \brief Entry points for AI system performance application
 */

#ifndef __AI_SYSTEM_PERFORMANCE_H__
#define __AI_SYSTEM_PERFORMANCE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int aiSystemPerformanceInit(void);
int aiSystemPerformanceProcess(void);
void aiSystemPerformanceDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __AI_SYSTEM_PERFORMANCE_H__ */
