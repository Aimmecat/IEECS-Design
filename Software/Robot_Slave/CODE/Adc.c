/*
 * Adc.c
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#include "myheadfile.h"

void Adc_Init(void){
    adc_init(SONAR0_AD);
    adc_init(SONAR1_AD);
    adc_init(SONAR2_AD);
    adc_init(SONAR3_AD);
    adc_init(SONAR4_AD);
    adc_init(SONAR5_AD);
    adc_init(SONAR6_AD);
    adc_init(SONAR7_AD);
    adc_init(INPUT0_AD);
    adc_init(INPUT1_AD);
    adc_init(INPUT2_AD);
    adc_init(INPUT3_AD);
}

void Adc_Get(void){

    //°ËÂ·sonar
    sonar_data[0] = TranseData(adc_convert(SONAR0_AD ,ADC_12BIT));
    sonar_data[1] = TranseData(adc_convert(SONAR1_AD ,ADC_12BIT));
    sonar_data[2] = TranseData(adc_convert(SONAR2_AD ,ADC_12BIT));
    sonar_data[3] = TranseData(adc_convert(SONAR3_AD ,ADC_12BIT));
    sonar_data[4] = TranseData(adc_convert(SONAR4_AD ,ADC_12BIT));
    sonar_data[5] = TranseData(adc_convert(SONAR5_AD ,ADC_12BIT));
    sonar_data[6] = TranseData(adc_convert(SONAR6_AD ,ADC_12BIT));
    sonar_data[7] = TranseData(adc_convert(SONAR7_AD ,ADC_12BIT));
}

int16 TranseData(int16 data){
    float v = TranseAd(data);
    float distance = Transe2Distance(v);
    if(distance > 80.0){
        distance = 80.0;
    }
    else if(distance < 15.0){
        distance = 15.0;
    }
    return (int16)(distance * TRANS_P);
}
