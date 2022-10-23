/*
 * Key.c
 *
 *  Created on: Aug 29, 2021
 *      Author: Aimmecat
 */

//使用A0,B0,C0,D0引脚 nvic_init里面应该填写EXTI0_IRQn，对应的中断函数为EXTI0_IRQHandler
//使用A1,B1,C1,D1引脚 nvic_init里面应该填写EXTI1_IRQn，对应的中断函数为EXTI1_IRQHandler
//使用A2,B2,C2,D2引脚 nvic_init里面应该填写EXTI2_IRQn，对应的中断函数为EXTI2_IRQHandler
//使用A3,B3,C3,D3引脚 nvic_init里面应该填写EXTI3_IRQn，对应的中断函数为EXTI3_IRQHandler
//使用A4,B4,C4,D4引脚 nvic_init里面应该填写EXTI4_IRQn，对应的中断函数为EXTI4_IRQHandler
//使用A5-A9,B5-B9,C5-C9,D5-D9引脚 nvic_init里面应该填写EXTI9_5_IRQn，对应的中断函数为EXTI9_5_IRQHandler
//使用A10-A15,B10-B15,C10-C15,D10-D15引脚 nvic_init里面应该填写EXTI15_10_IRQn，对应的中断函数为EXTI15_10_IRQHandler

#include "myheadfile.h"

KEY_STATE key_state =  _KEY_NULL;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              按键初始化
//  @author             Ji Xiaoyu
//  @update             2021-8-29
//  @param              None
//  @return             void
//  Sample usage:       Key_Init()
//-------------------------------------------------------------------------------------------------------------------
void Key_Init(void){
    gpio_init(KEY_ENTER, GPI, 1, GPIO_INT_CONFIG);
    gpio_init(KEY_B_PORT, GPI, 1, GPIO_INT_CONFIG);

    gpio_interrupt_init(KEY_A_PORT, BOTH, GPIO_INT_CONFIG);
    gpio_interrupt_init(KEY_ENTER, RISING, GPIO_INT_CONFIG);
    nvic_init(EXTI9_5_IRQn, 2, 2, ENABLE);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              按键触发demo
//  @author             Ji Xiaoyu
//  @update             2021-8-29
//  @param              null
//  @return             void
//  Sample usage:       Key_Happen(key_state)
//-------------------------------------------------------------------------------------------------------------------
void Key_Happen(void){
    if(key_state == _KEY_ROTATION_LEFT){
        uart_putchar(UART_1, key_state);
    }
    else if(key_state == _KEY_ROTATION_RIGHT){
        uart_putchar(UART_1, key_state);
    }
    else if(key_state == _KEY_ENTER){
        uart_putchar(UART_1, key_state);
    }
    key_state = _KEY_NULL;
}
