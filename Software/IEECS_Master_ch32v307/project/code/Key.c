/*
 * Key.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

KEY_STATE key_state =  _KEY_NULL;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              °´¼ü³õÊ¼»¯
//  @author             Ji Xiaoyu
//  @update             2021-8-29
//  @param              None
//  @return             void
//  Sample usage:       Key_Init()
//-------------------------------------------------------------------------------------------------------------------
void Key_Init(void){
    exti_init(KEY_A_PORT, EXTI_TRIGGER_RISING);
    exti_init(KEY_B_PORT, EXTI_TRIGGER_RISING);
    exti_init(KEY_ENTER, EXTI_TRIGGER_RISING);

    exti_enable(KEY_A_PORT);
    exti_enable(KEY_B_PORT);
    exti_enable(KEY_ENTER);
}

