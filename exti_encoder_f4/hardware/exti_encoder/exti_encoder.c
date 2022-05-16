#include "exti_encoder.h"

void EXTI_GPIO_Init(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE6);

  LL_EXTI_DisableEvent_0_31(LL_EXTI_LINE_6);
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6);
  LL_EXTI_DisableFallingTrig_0_31(LL_EXTI_LINE_6);
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_6);

  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);

  /* EXTI interrupt init*/
  NVIC_SetPriority(EXTI9_5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void GPIO_Input(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_INPUT);
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_INPUT);

  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);
  LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);
}

/**
 * @brief encoder connected to pins: PA6 and PA7, pin PA5 button switch
 * @param None
 * @retval None
 */
void EXTI_Callbac(void)
{
  delay_us(1); // anti-tinkling
  LL_EXTI_DeInit();
  GPIO_Input();

  static int32_t count = 0;
  if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_7)) count++;
  else count--;

  LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
  printf("encoder: %d\r\n", count);
  EXTI_GPIO_Init();
}

