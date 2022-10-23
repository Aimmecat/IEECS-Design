/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_driver_exti
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ3184284598)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         IAR 8.32.4 or MDK 5.28
* @Target core      MM32F3277
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-11
********************************************************************************************************************/

#include "zf_driver_exti.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       EXTI �жϳ�ʼ�� <ͬһ�±�����Ų���ͬʱ��ʼ��Ϊ�ⲿ�ж����� ���� A0 �� B0 ����ͬʱ��ʼ��Ϊ�ⲿ�ж�����>
// @param       pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// @param       trigger         ѡ�񴥷����źŷ�ʽ [EXTI_TRIGGER_RISING/EXTI_TRIGGER_FALLING/EXTI_TRIGGER_BOTH]
// @return      void
// Sample usage:                exti_init(A0, EXTI_TRIGGER_RISING);
//-------------------------------------------------------------------------------------------------------------------
void exti_init (gpio_pin_enum pin, exti_trigger_enum trigger)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                         // ����ʱ��ʹ��
    gpio_init(pin, GPI, GPIO_HIGH, GPI_PULL_UP);                                // ��ʼ��ѡ�е�����
    GPIO_EXTILineConfig(pin >> 5, pin & 0x1F);                                  // ѡ����һ��GPIO���ж�

    EXTI_InitTypeDef EXTI_InitStructure = {0};
    EXTI_InitStructure.EXTI_Line = 1 << (pin & 0x1F);                           // ���ź�����
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                         // ����ģʽ
    EXTI_InitStructure.EXTI_Trigger = trigger;                                  // ������ʽ
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                                   // ʹ�ܻ���ʧ��
    EXTI_Init(&EXTI_InitStructure);

    if((pin&0x1F) < 1)
       interrupt_enable(EXTI0_IRQn);                                             // ʹ�� Line0 ���ж���Ӧ
    else if((pin&0x1F) < 2)
       interrupt_enable(EXTI1_IRQn);                                             // ʹ�� Line1 ���ж���Ӧ
    else if((pin&0x1F) < 3)
       interrupt_enable(EXTI2_IRQn);                                             // ʹ�� Line2 ���ж���Ӧ
    else if((pin&0x1F) < 4)
       interrupt_enable(EXTI3_IRQn);                                             // ʹ�� Line3 ���ж���Ӧ
    else if((pin&0x1F) < 5)
       interrupt_enable(EXTI4_IRQn);                                             // ʹ�� Line4 ���ж���Ӧ
    else if((pin&0x1F) < 10)
       interrupt_enable(EXTI9_5_IRQn);                                           // ʹ�� Line5-9 ���ж���Ӧ
    else
       interrupt_enable(EXTI15_10_IRQn);                                         // ʹ�� Line10-15 ���ж���Ӧ
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       EXTI �ж�ʹ��
// @param       pin              ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// @return      void
// Sample usage:                exti_enable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_enable (gpio_pin_enum pin)
{
    EXTI->INTENR |= (0x00000001 << (pin&0x1F));
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       EXTI �ж�ʧ��
// @param       pin             ѡ�� EXTI ���� (��ѡ��Χ�� zf_driver_gpio.h �� gpio_pin_enum ö��ֵȷ��)
// @return      void
// Sample usage:                exti_disable(A0);
//-------------------------------------------------------------------------------------------------------------------
void exti_disable (gpio_pin_enum pin)
{
    EXTI->INTENR &= ~(0x00000001 << (pin&0x1F));
}
