/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 

/*
 *@Note
 输入捕获例程：
 TIM1_CH1(PA8)
 本例程演示 TIM_CH1(PA8) 引脚浮空输入，该引脚检测到边沿跳变触发 TIM1 捕获中断，
 上升沿触发 TIM_IT_CC1 中断，下降沿触发 TIM_IT_CC2 中断。

*/

#include "debug.h"

/*********************************************************************
 * @fn      Input_Capture_Init
 *
 * @brief   Initializes TIM1 input capture.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void Input_Capture_Init( u16 arr, u16 psc )
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_ICInitTypeDef TIM_ICInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( GPIOA, &GPIO_InitStructure );
    GPIO_ResetBits( GPIOA, GPIO_Pin_8 );

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure );

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_PWMIConfig( TIM1, &TIM_ICInitStructure );

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    TIM1->INTFR = 0;
    TIM_ITConfig( TIM1, TIM_IT_CC1 | TIM_IT_CC2, ENABLE );

    TIM_SelectInputTrigger( TIM1, TIM_TS_TI1FP1 );
    TIM_SelectSlaveMode( TIM1, TIM_SlaveMode_Reset );
    TIM_SelectMasterSlaveMode( TIM1, TIM_MasterSlaveMode_Enable );
    TIM_Cmd( TIM1, ENABLE );
}

/*********************************************************************
 * @fn      TIM1_CC_IRQHandler
 *
 * @brief   This function handles TIM1  Capture Compare Interrupt exception.
 *
 * @return  none
 */
void TIM1_CC_IRQHandler( void )
{
    if( TIM_GetITStatus( TIM1, TIM_IT_CC1 ) != RESET )
    {
        printf( "CH1_Val:%d\r\n", TIM_GetCapture1( TIM1 ) );
        TIM_SetCounter( TIM1, 0 );
    }

    if( TIM_GetITStatus( TIM1, TIM_IT_CC2 ) != RESET )
    {
        printf( "CH2_Val:%d\r\n", TIM_GetCapture2( TIM1 ) );
    }

    TIM_ClearITPendingBit( TIM1, TIM_IT_CC1 | TIM_IT_CC2 );
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main( void )
{
    USART_Printf_Init( 115200 );
    printf( "SystemClk:%d\r\n", SystemCoreClock );

    Input_Capture_Init( 0xFFFF, 48000 - 1 );

    while( 1 );
}

