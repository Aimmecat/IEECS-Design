/*
 * Beep.c
 *
 *  Created on: Aug 23, 2021
 *      Author: Aimmecat
 */


#include "myheadfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief              蜂鸣器初始化
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
//  @brief              蜂鸣器响特定时间
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              time   ms数
//  @return             void
//  Sample usage:       Beep_Set_ms(100);
//-------------------------------------------------------------------------------------------------------------------
void Beep_Set_ms(int16 time){
    gpio_set(BEEP_PIN,1);
    systick_delay_ms(time);
    gpio_set(BEEP_PIN,0);
}
