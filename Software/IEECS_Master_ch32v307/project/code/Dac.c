/*
 * Dac.c
 *
 *  Created on: Nov 13, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//PWMÄ£ÄâDacÊä³ö

void Dac_Init(void){
    pwm_init(DAC_OUTPUT1,17000,0);
    pwm_init(DAC_OUTPUT1,17000,0);
}

void Dac_Output(void){
    pwm_set_duty(DAC_OUTPUT1, (int)(voltage * KP_VOLTAGE));
    pwm_set_duty(DAC_OUTPUT2, (int)(voltage * KP_VOLTAGE));
}
