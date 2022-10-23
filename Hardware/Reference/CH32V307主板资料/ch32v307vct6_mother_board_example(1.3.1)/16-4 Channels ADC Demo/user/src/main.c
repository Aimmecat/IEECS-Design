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



uint16 dat[8];



int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // ADC��ʼ��
    adc_init(ADC_IN7_A7);               // ADC��ʼ�� ����A7
    adc_init(ADC_IN9_B1);               // ADC��ʼ�� ����B1
    adc_init(ADC_IN10_C0);              // ADC��ʼ�� ����C0
    adc_init(ADC_IN11_C1);              // ADC��ʼ�� ����C1


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        dat[0] = adc_convert(ADC_IN7_A7, ADC_12BIT);    // ADCȡֵ ����A7 ,�ֱ���12λ
        dat[1] = adc_convert(ADC_IN9_B1, ADC_8BIT);    // ADCȡֵ ����B1 ,�ֱ���8λ
        dat[2] = adc_convert(ADC_IN10_C0, ADC_10BIT);   // ADCȡֵ ����C0 ,�ֱ���10λ
        dat[3] = adc_convert(ADC_IN11_C1, ADC_12BIT);   // ADCȡֵ ����C1 ,�ֱ���12λ
        printf("ADC_0 = %d\r\n", dat[0]);
        printf("ADC_1 = %d\r\n", dat[1]);
        printf("ADC_2 = %d\r\n", dat[2]);
        printf("ADC_3 = %d\r\n", dat[3]);


        system_delay_ms(100);
    }
}
