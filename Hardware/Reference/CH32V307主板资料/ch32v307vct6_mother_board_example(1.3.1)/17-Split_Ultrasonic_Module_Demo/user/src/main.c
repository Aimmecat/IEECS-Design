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


#define SPLIT_ULTRASONIC_UART       UART_8
#define SPLIT_ULTRASONIC_BAUD       115200
#define SPLIT_ULTRASONIC_RX         UART8_TX_E14        // ������ȥ�� UART-RX ���� Ҫ���ڵ�Ƭ�� TX ��
#define SPLIT_ULTRASONIC_TX         UART8_RX_E15        // ������ȥ�� UART-TX ���� Ҫ���ڵ�Ƭ�� RX ��

#define SEND_PORT_PIN               D10                 // ���ö�Ӧ�˿� ��ȥģ�鷢�� ������ʵ���Բ��ÿ���


uint16 ranging_counter = 0;                             // �������
uint8 ranging_flage = 0x00;                             // ���״̬

uint8 receipt_data;
uint8 dat[3];
uint8 num;


int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    //�˴���д�û�����(���磺�����ʼ�������)
    gpio_init(SEND_PORT_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);         // ��ʼ����ȥģ��ʹ������
    uart_init(SPLIT_ULTRASONIC_UART, SPLIT_ULTRASONIC_BAUD, SPLIT_ULTRASONIC_RX, SPLIT_ULTRASONIC_TX);
    uart_rx_interrupt(SPLIT_ULTRASONIC_UART, ENABLE);

    gpio_set_level(SEND_PORT_PIN, GPIO_HIGH);                       // ����ʹ�� ��ȥģ�鷢�� ʵ�ʽ��ϵ������Ϳ�ʼ���� ������Բ��ÿ���

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        //�˴���д��Ҫѭ��ִ�еĴ���
        if(ranging_flage)                                                 // �ȴ�������
        {
            printf("\r\nRanging counter us is %d.", ranging_counter);     // ��������Ϣ
            ranging_flage = 0x00;
        }
        system_delay_ms(100);                                             // ��ʱ
        //�˴���д��Ҫѭ��ִ�еĴ���
    }
}

//�˺�����Ҫ�ڴ���8�ж�������е��á�
//������������������ranging_counter ��ֵ��Զ����0
void uart_handler (void)
{
    uart_query_byte(SPLIT_ULTRASONIC_UART, &receipt_data);
    dat[num] = receipt_data;
    if(dat[0] != 0xa5)  num = 0;                                                    //����һ�������Ƿ�Ϊ0xa5
    else                num++;

    if(num == 3)                                                                    //������� ��ʼ��������
    {
        num = 0;
        ranging_counter = dat[1]<<8 | dat[2];                                       //�õ�������ģ�����ľ���
        ranging_flage = 0x01;
    }
}


