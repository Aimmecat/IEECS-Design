/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             main
* @company          �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"


#define S_MOTOR_PIN   TIM2_PWM_CH1_A15       // ����������
uint16_t duty = 500;

int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���


    // ��ʼ�������������A15, Ƶ��50hz, ռ�ձ� 500/10000 * 100% (10000��PWM����ռ�ձ�ʱ���ֵ��
    pwm_init(S_MOTOR_PIN, 50, 500);


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        // ������λ�ö��λ��   ��0.5ms - 2.5ms��ms/20ms * 10000��10000��PWM����ռ�ձ�ʱ���ֵ��
        // �����СֵΪ250   ���ֵΪ1250
        // �����20 ��20��Ϊ����Сת�������򣬲�Ҫת�����ڼ���λ�ã��еĶ���ڼ���λ�����׿�ס
        duty += 2;
        if((1250-20) < duty) duty = (250+20);

        // ���ƶ���ﵽָ��λ��
        pwm_set_duty(S_MOTOR_PIN,duty);

        if((250+20) >= duty)    system_delay_ms(1000); // ����1250��λ��   ��ת��250��λ��ʱ   Ӧ��ʹ�ýϳ�����ʱ�ȵ�����ﵽָ��λ��
        else                    system_delay_ms(3);    //
    }
}




