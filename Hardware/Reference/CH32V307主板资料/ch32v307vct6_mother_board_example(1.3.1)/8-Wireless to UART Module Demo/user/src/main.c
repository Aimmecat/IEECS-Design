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

uint8 send_dat[] = {0x11, 0x22, 0x33};
uint8 read_dat[10];

int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    wireless_uart_init();

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        // �������ݡ�
        wireless_uart_send_buff(send_dat, 3);
        system_delay_ms(1000);

        // ��ȡFIFO���������
        wireless_uart_read_buff(read_dat, 10);
        // �����ݷ��ͳ�ȥ
        wireless_uart_send_buff(read_dat, 10);
        system_delay_ms(1000);

    }
}




