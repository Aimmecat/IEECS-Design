/*
 * Dac.h
 *
 *  Created on: Nov 13, 2022
 *      Author: Aimmecat
 */

#ifndef DAC_H_
#define DAC_H_

#define DAC_OUTPUT1     TIM4_PWM_CH3_D14
#define DAC_OUTPUT2     TIM4_PWM_CH4_D15

#define KP_VOLTAGE    (int)(PWM_DUTY_MAX / 255)

void Dac_Init(void);
void Dac_Output(void);

#endif /* DAC_H_ */
