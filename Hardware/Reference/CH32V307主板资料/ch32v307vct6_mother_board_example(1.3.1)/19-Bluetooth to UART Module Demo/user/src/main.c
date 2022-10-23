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

uint8 send_dat_1[] = {0x11, 0x22, 0x33};
uint8 send_dat_2[] = {0x44, 0x66, 0x88};

uint8 read_dat_1[10];
uint8 read_dat_2[10];


int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

	// ����ģ��1��ʼ��
    bluetooth_ch9141_init_ch1();
    bluetooth_ch9141_init_ch2();


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        // �������ݡ�
        bluetooth_ch9141_send_buff_ch1(send_dat_1, 3);
        bluetooth_ch9141_send_buff_ch2(send_dat_2, 3);
        system_delay_ms(1000);
        // ͨ�����ߵ��ԣ��鿴 read_dat_1��read_dat_2 ���Բ鿴���յ����ݡ�

        // ��ȡFIFO���������
        bluetooth_ch9141_read_buff_ch1(read_dat_1, 10);
        bluetooth_ch9141_read_buff_ch2(read_dat_2, 10);

        // �����ݷ��ͳ�ȥ
        bluetooth_ch9141_send_buff_ch1(read_dat_1, 10);
        bluetooth_ch9141_send_buff_ch2(read_dat_2, 10);

        system_delay_ms(1000);
    }
}
