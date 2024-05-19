
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file            motor_driver.c
  * @brief           Class that allows user to easily set the bi-directional duty cycle of a motor
  *
  *                  Created on: Apr 25, 2024
  *                  Author: Johnathan Waldmire
  ******************************************************************************
  */
/* USER CODE END Header */
#include <motor_driver.h>
#include <stdint.h>

//!function to enable the motor channels to be pwm'd
void enable_channel(motor *p_mot, uint32_t channel){
	if (channel == 1){
		HAL_TIM_PWM_Start(p_mot->tim, p_mot->ch1);
	}
	if (channel == 2){
		HAL_TIM_PWM_Start(p_mot->tim, p_mot->ch2);
	}
}

//!function to disable the motor channels
void disable_channel(motor *p_mot, uint32_t channel){
	if (channel == 1){
		HAL_TIM_PWM_Stop(p_mot->tim, p_mot->ch1);
	}
	if (channel == 2){
		HAL_TIM_PWM_Stop(p_mot->tim, p_mot->ch2);
	}
}

//! function to set the duty cycle
void set_duty_cycle(motor *p_mot, int32_t duty){

	if (duty > 0){
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch1,duty);
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch2,0);
	}
	if (duty < 0){
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch1,0);
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch2,-duty);
	}
	if (duty == 0){
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch1,4000);
		__HAL_TIM_SET_COMPARE(p_mot->tim,p_mot->ch2,4000);
	}
}
