
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            RC_driver.c
  * @brief           Class that can be used to read a PWM signal from an RC controller
  *
  *                  Created on: May 17, 2024
  *                  Author: Johnathan Waldmire
  ******************************************************************************
  */
/* USER CODE END Header */

#include <RC_driver.h>
#include <stdint.h>

//!function that measures the active pulse width of the RC signal in microseconds
void RC_callback(RC_Signal *p_RC){
	if (p_RC->tim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		p_RC->IC_Start = HAL_TIM_ReadCapturedValue(p_RC->tim, p_RC->ch1); // read the first value
		if (p_RC->IC_Start)
		{
			p_RC->IC_PWM = HAL_TIM_ReadCapturedValue(p_RC->tim, p_RC->ch2);
		}
	}
}

//! function that saturates erroneous pulse width values then returns the pulse width in microseconds
uint32_t RC_Pulse(RC_Signal *p_RC){
	if (p_RC->IC_PWM > 2000)
	{
		p_RC->IC_PWM = 2000;
		return p_RC->IC_PWM;
	}
	if (p_RC->IC_PWM < 	1000)
	{
		p_RC->IC_PWM = 1000;
		return p_RC->IC_PWM;
	}
	else
	{
		return p_RC->IC_PWM;
	}
}


