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


int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    oled_init();     //��ʼ��OLED��Ļ

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        oled_show_string(0,0,"seekfree.taobao.com");//��ʾ�ַ���
        oled_show_int(0, 1, -56, 3);                    //��ʾһ��8λ�з���������
        oled_show_uint(0, 2, 56, 3);                    //��ʾһ��8λ�޷���������
        oled_show_float(0, 3, 56.356, 2, 2);            //��ʾһ�������� ȥ����Ч0λ  ����λ��ʾ5λ  С��λ��ʾ2λ

        //������ʾ��X Y����������������һ�£�������ʾ��������x y����������Ϊ��λ
        //��������ʹ��λ�õ��ڸ�������
        oled_show_chinese(0,4,16,oled_16x16_chinese[0],4);

        system_delay_ms(100);
    }
}




