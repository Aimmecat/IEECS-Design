/*
 * Beep.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ��������ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-9-1
//  @param              None
//  @return             void
//  Sample usage:       Beep_Init();
//-------------------------------------------------------------------------------------------------------------------
void Beep_Init(void){
    gpio_init(BEEP_PIN,GPO,0,GPIO_PIN_CONFIG);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ���������ض�ʱ��
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              time   ms��
//  @param              duty   ռ�ձ�(0~100%)
//  @return             void
//  Sample usage:       Beep_Set_ms(100,50);
//-------------------------------------------------------------------------------------------------------------------
void Beep_Set_ms(int16 time){
    gpio_set(BEEP_PIN,1);
    system_delay_ms(time);
    gpio_set(BEEP_PIN,0);
}
