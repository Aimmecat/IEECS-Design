/*
 * Adc.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

int16 sonar_data[8] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};
int16 input_adc[4] = {0, 0, 0, 0};

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

void Sonar_Adc_Get(void){

    //八路sonar
    sonar_data[0] = Transe_Sonar_Data(adc_mean_filter(SONAR0_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[1] = Transe_Sonar_Data(adc_mean_filter(SONAR1_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[2] = Transe_Sonar_Data(adc_mean_filter(SONAR2_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[3] = Transe_Sonar_Data(adc_mean_filter(SONAR3_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[4] = Transe_Sonar_Data(adc_mean_filter(SONAR4_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[5] = Transe_Sonar_Data(adc_mean_filter(SONAR5_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[6] = Transe_Sonar_Data(adc_mean_filter(SONAR6_AD ,ADC_12BIT,FILTER_TIMES));
    sonar_data[7] = Transe_Sonar_Data(adc_mean_filter(SONAR7_AD ,ADC_12BIT,FILTER_TIMES));
}

void Input_Adc_Get(void){
    //四路AD输入
    input_adc[0] = adc_mean_filter(INPUT0_AD ,ADC_10BIT,FILTER_TIMES);
    input_adc[1] = adc_mean_filter(INPUT1_AD ,ADC_10BIT,FILTER_TIMES);
    input_adc[2] = adc_mean_filter(INPUT2_AD ,ADC_10BIT,FILTER_TIMES);
    input_adc[3] = adc_mean_filter(INPUT3_AD ,ADC_10BIT,FILTER_TIMES);
}

int16 Transe_Sonar_Data(int16 data){
    double v = (TranseAd(data) - 0.78) / 0.38;
    double distance = Transe2Distance(v);
    if(distance > LIDAR_MAX_DISTANCE){
        distance = LIDAR_MAX_DISTANCE;
    }
    if(distance < LIDAR_MIN_DISTANCE){
        distance = LIDAR_MIN_DISTANCE;
    }
    return (int16)(distance * TRANS_P);
}

