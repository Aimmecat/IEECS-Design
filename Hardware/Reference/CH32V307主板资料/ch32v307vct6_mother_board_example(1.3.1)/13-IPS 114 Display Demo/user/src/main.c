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

    ips114_init();     //��ʼ����Ļ

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        ips114_show_string(0,0,"seekfree");           //��ʾ�ַ���
        ips114_show_int(0, 20, -56, 4);                    //��ʾһ��8λ�з���������
        ips114_show_uint(0,40, 56, 4);                    //��ʾһ��8λ�޷���������
        ips114_show_float(0,60,56.356,2,2);            //��ʾһ�������� ȥ����Ч0λ  ����λ��ʾ5λ  С��λ��ʾ2λ

        system_delay_ms(2000);

        ips114_clear(RGB565_BLUE);
        system_delay_ms(500);
        ips114_clear(RGB565_RED);
        system_delay_ms(500);
        ips114_clear(RGB565_YELLOW);
        system_delay_ms(500);
        ips114_clear(RGB565_WHITE);
    }
}




