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

int16_t encoder_data[4];
int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // һ����ʱ��ֻ����һ�����顣�������������������PWM������Ͳ��������������ˡ�
    // ʹ�ö�ʱ��1������������(��������ģʽ)
    encoder_init_quad(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11);
    // ʹ�ö�ʱ��3������������(��������ģʽ)
    encoder_init_quad(TIM3_ENCOEDER, TIM3_CH1_ENCOEDER_C6, TIM3_CH2_ENCOEDER_C7);
    // ʹ�ö�ʱ��9������������(��������ģʽ)
    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH1_ENCOEDER_D9, TIM9_CH2_ENCOEDER_D11);
    // ʹ�ö�ʱ��10������������(��������ģʽ)
    encoder_init_quad(TIM10_ENCOEDER, TIM10_CH1_ENCOEDER_D1, TIMER10_CH2_ENCOEDER_D3);

    interrupt_global_enable();            // ���ж������
    while(1)
    {

        encoder_data[0] = encoder_get_count(TIM1_ENCOEDER);     // ��ʱ��ȡֵ
        encoder_clear_count(TIM1_ENCOEDER);                     // ��ʱ�����

        encoder_data[1] = encoder_get_count(TIM3_ENCOEDER);     // ��ʱ��ȡֵ
        encoder_clear_count(TIM3_ENCOEDER);                     // ��ʱ�����

        encoder_data[2] = encoder_get_count(TIM9_ENCOEDER);     // ��ʱ��ȡֵ
        encoder_clear_count(TIM9_ENCOEDER);                     // ��ʱ�����

        encoder_data[3] = encoder_get_count(TIM10_ENCOEDER);    // ��ʱ��ȡֵ
        encoder_clear_count(TIM10_ENCOEDER);                    // ��ʱ�����

        printf("encoder_1 = %d\r\n", encoder_data[0]);
        printf("encoder_2 = %d\r\n", encoder_data[1]);
        printf("encoder_3 = %d\r\n", encoder_data[2]);
        printf("encoder_4 = %d\r\n", encoder_data[3]);

        system_delay_ms(100);
    }
}




