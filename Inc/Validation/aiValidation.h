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
 * \file aiValidation.h
 * \brief AI Validation application
 */

#ifndef __AI_VALIDATION_H__
#define __AI_VALIDATION_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int aiValidationInit(void);
int aiValidationProcess(void);
void aiValidationDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __AI_VALIDATION_H__ */
