/*
 * Adc.h
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_ADC_H_
#define CODE_ADC_H_

#include "zf_adc.h"

#define TRANS_P             10

#define TranseAd(x)         (x * 0.0008056f)
#define Transe2Distance(x)  (-57.8f * x * x * x + 198.9f * x * x - 234.1f * x + 107.2)

#define SONAR0_AD   ADC_IN10_C0
#define SONAR1_AD   ADC_IN11_C1
#define SONAR2_AD   ADC_IN12_C2
#define SONAR3_AD   ADC_IN13_C3
#define SONAR4_AD   ADC_IN1_A1
#define SONAR5_AD   ADC_IN2_A2
#define SONAR6_AD   ADC_IN9_B1
#define SONAR7_AD   ADC_IN8_B0
#define INPUT0_AD   ADC_IN15_C5
#define INPUT1_AD   ADC_IN14_C4
#define INPUT2_AD   ADC_IN7_A7
#define INPUT3_AD   ADC_IN6_A6

void Adc_Init(void);
void Adc_Get(void);
int16 TranseData(int16 data);

#endif /* CODE_ADC_H_ */
