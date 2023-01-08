/*
 * Adc.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef ADC_H_
#define ADC_H_

#include "zf_driver_adc.h"

#define TRANS_P             1000.0
#define FILTER_TIMES        10

#define LIDAR_MIN_DISTANCE  0.08
#define LIDAR_MAX_DISTANCE  0.8

#define TranseAd(x)         ((x) * 0.0008056f)
#define Transe2Distance(x)  (0.276 * pow((x), -0.6629) * exp(-0.194 * (x)))

#define SONAR0_AD    ADC_IN3_A3
#define SONAR1_AD    ADC_IN2_A2
#define SONAR2_AD    ADC_IN1_A1
#define SONAR3_AD    ADC_IN0_A0
#define SONAR4_AD    ADC_IN13_C3
#define SONAR5_AD    ADC_IN12_C2
#define SONAR6_AD    ADC_IN11_C1
#define SONAR7_AD    ADC_IN10_C0
#define INPUT0_AD    ADC_IN6_A6
#define INPUT1_AD    ADC_IN7_A7
#define INPUT2_AD    ADC_IN14_C4
#define INPUT3_AD    ADC_IN15_C5

extern int16 sonar_data[8];
extern int16 input_adc[4];

void Adc_Init(void);
void Sonar_Adc_Get(void);
void Input_Adc_Get(void);
int16 Transe_Sonar_Data(int16 data);

#endif /* ADC_H_ */
