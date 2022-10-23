/*
 * Key.c
 *
 *  Created on: Aug 29, 2021
 *      Author: Aimmecat
 */

//ʹ��A0,B0,C0,D0���� nvic_init����Ӧ����дEXTI0_IRQn����Ӧ���жϺ���ΪEXTI0_IRQHandler
//ʹ��A1,B1,C1,D1���� nvic_init����Ӧ����дEXTI1_IRQn����Ӧ���жϺ���ΪEXTI1_IRQHandler
//ʹ��A2,B2,C2,D2���� nvic_init����Ӧ����дEXTI2_IRQn����Ӧ���жϺ���ΪEXTI2_IRQHandler
//ʹ��A3,B3,C3,D3���� nvic_init����Ӧ����дEXTI3_IRQn����Ӧ���жϺ���ΪEXTI3_IRQHandler
//ʹ��A4,B4,C4,D4���� nvic_init����Ӧ����дEXTI4_IRQn����Ӧ���жϺ���ΪEXTI4_IRQHandler
//ʹ��A5-A9,B5-B9,C5-C9,D5-D9���� nvic_init����Ӧ����дEXTI9_5_IRQn����Ӧ���жϺ���ΪEXTI9_5_IRQHandler
//ʹ��A10-A15,B10-B15,C10-C15,D10-D15���� nvic_init����Ӧ����дEXTI15_10_IRQn����Ӧ���жϺ���ΪEXTI15_10_IRQHandler

#include "myheadfile.h"

KEY_STATE key_state =  _KEY_NULL;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ������ʼ��
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
//  @brief              ��������demo
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
