/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file            main
 * @company         �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
 * @version         �鿴doc��version�ļ� �汾˵��
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//�Ҽ��������̣�ѡ��ˢ��


#include "myheadfile.h"


int main(void)
{
    DisableGlobalIRQ();
    board_init();                           //��ر���

    uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10);    //���ô����жϺ�,������,TX,RX
    gpio_init(C12, GPI, 1, GPIO_PIN_CONFIG);
//    ICM20602_Init();
    MCUC_Slave_Init();
    Key_Init();
    timer_pit_interrupt_ms(TIMER_2, 5);
    Adc_Init();

    EnableGlobalIRQ(0);

    while(1){
//        Key_Happen();
//        ICM20602_Get();
        Adc_Get();
    }

}

