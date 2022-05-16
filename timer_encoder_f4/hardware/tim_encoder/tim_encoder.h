#ifndef __TIM_ENCODER_H__
#define __TIM_ENCODER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

void TIM2_Init(void);
void TIM3_Init(void);
void TIM4_Init(void);
void TIM2_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_ENCODER_H__ */

