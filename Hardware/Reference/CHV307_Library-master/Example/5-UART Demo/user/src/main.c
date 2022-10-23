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

// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� WCH-LINK ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� B10
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� B11
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ


// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      UART Text.
// 5.ͨ���������ַ������ݣ����յ���ͬ�ķ�������
//      UART get data:.......
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


#include "zf_common_headfile.h"

#define UART_INDEX              DEBUG_UART_INDEX                                // Ĭ�� UART_1
#define UART_BAUDRATE           DEBUG_UART_BAUDRATE                             // Ĭ�� 115200
#define UART_TX_PIN             DEBUG_UART_TX_PIN                               // Ĭ�� UART3_TX_B10
#define UART_RX_PIN             DEBUG_UART_RX_PIN                               // Ĭ�� UART3_RX_B11

#define UART_PRIORITY           USART1_IRQn                                      // ��Ӧ�����жϵ��жϱ�� �� mm32f3277gx.h ͷ�ļ��в鿴 IRQn_Type ö����

uint8 uart_get_data[64];                                                        // ���ڽ������ݻ�����
uint8 fifo_get_data[64];                                                        // fifo �������������

uint8 get_data = 0;                                                             // �������ݱ���
uint32 fifo_data_count = 0;                                                     // fifo ���ݸ���

fifo_struct uart_data_fifo;

int16_t encoder_data;
int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���


    fifo_init(&uart_data_fifo, uart_get_data, 64);                              // ��ʼ�� fifo ���ػ�����

    uart_init(UART_INDEX, UART_BAUDRATE, UART_TX_PIN, UART_RX_PIN);             // ��ʼ��������ģ�������� �������������ģʽ
    uart_rx_interrupt(UART_INDEX, ENABLE);                                      // ���� UART_INDEX �Ľ����ж�
    interrupt_set_priority(UART_PRIORITY, 0);                                   // ���ö�Ӧ UART_INDEX ���ж����ȼ�Ϊ 0

    uart_write_string(UART_INDEX, (const uint8 *)"UART Text.");                 // ���������Ϣ
    uart_write_byte(UART_INDEX, '\r');                                          // ����س�
    uart_write_byte(UART_INDEX, '\n');                                          // �������

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo �Ƿ�������
        if(fifo_data_count != 0)                                                // ��ȡ��������
        {
            fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // �� fifo �����ݶ�������� fifo ���صĻ���
            uart_write_string(UART_INDEX, (const uint8 *)"\r\nUART get data:");                // ���������Ϣ
            uart_write_buffer(UART_INDEX, fifo_get_data, fifo_data_count);      // ����ȡ�������ݷ��ͳ�ȥ
        }
        system_delay_ms(10);

    }
}
//-------------------------------------------------------------------------------------------------------------------
// @brief       UART_INDEX �Ľ����жϴ����� ����������� UART_INDEX ��Ӧ���жϵ��� ��� isr.c
// @param       void
// @return      void
// Sample usage:                uart_rx_interrupt_handler();
//-------------------------------------------------------------------------------------------------------------------
void uart_rx_interrupt_handler (void)
{
//    get_data = uart_read_byte(UART_INDEX);                                      // �������� while �ȴ�ʽ ���������ж�ʹ��
    uart_query_byte(UART_INDEX, &get_data);                                     // �������� ��ѯʽ �����ݻ᷵�� TRUE û�����ݻ᷵�� FALSE
    fifo_write_buffer(&uart_data_fifo, &get_data, 1);                           // ������д�� fifo ��
}
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� WCH-LINK �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����

