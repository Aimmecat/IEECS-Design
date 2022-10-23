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
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      FLASH_SECTION_INDEX: 62, FLASH_PAGE_INDEX: 3, origin data is :
//      ...
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�



#include "zf_common_headfile.h"


// **************************** �������� ****************************

// ��κ궨����Ϊ����ʾ����� FLASH ʹ�û�����д��Ͷ�ȡ���ݶ�����
#define FLASH_SECTION_INDEX       FLASH_SECTION_62                          // �洢�����õ����� �����ڶ�������
#define FLASH_PAGE_INDEX          FLASH_PAGE_3                              // �洢�����õ�ҳ�� ������һ��ҳ��





int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // �˴���д�û����� ���������ʼ�������
     if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // �ж��Ƿ�������
         flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                // ������һҳ

     flash_read_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);      // �����ݴ� flash ��ȡ��������
     printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, origin data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ���
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // ���������� 1 ��λ�õ������� uint32 ��ʽ���
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // ���������� 2 ��λ�õ������� int32  ��ʽ���
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // ���������� 3 ��λ�õ������� uint16 ��ʽ���
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // ���������� 4 ��λ�õ������� int16  ��ʽ���
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // ���������� 5 ��λ�õ������� uint8  ��ʽ���
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // ���������� 6 ��λ�õ������� int8   ��ʽ���

     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����

     // ���� flash_data_union_buffer[0] д�� int8_type ��ôֻ���� int8_type ��ȡ
     // ͬ�� flash_data_union_buffer[0] д�� float_type ��ôֻ���� float_type ��ȡ
     printf("\r\n Data property display :");
     printf("\r\n flash_data_union_buffer[0] write int8 data type:");
     flash_data_union_buffer[0].int8_type   = -128;                              // �򻺳����� 0 ��λ��д��     int8   ����
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ��� ���ݽ�����ȷ
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // ���������� 0 ��λ�õ������� int8   ��ʽ��� �õ���ȷд������

     printf("\r\n flash_data_union_buffer[0] write int8 data type:");
     flash_data_union_buffer[0].int8_type  -= 1;                                 // �򻺳����� 0 ��λ��д��     int8   ����
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ��� ���ݽ�����ȷ
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // ���������� 0 ��λ�õ������� int8   ��ʽ��� �õ���ȷд������

     printf("\r\n flash_data_union_buffer[0] write float data type:");
     flash_data_union_buffer[0].float_type  = 16.625;                            // �򻺳����� 0 ��λ��д��     float  ����
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ��� �õ���ȷд������
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // ���������� 0 ��λ�õ������� int8   ��ʽ��� ���ݽ�����ȷ

     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
     // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����

     flash_data_buffer_clear();                                                  // ��ջ�����
     flash_data_union_buffer[0].float_type  = 3.1415926;                         // �򻺳����� 0 ��λ��д�� float  ����
     flash_data_union_buffer[1].uint32_type = 4294967295;                        // �򻺳����� 1 ��λ��д�� uint32 ����
     flash_data_union_buffer[2].int32_type  = -2147483648;                       // �򻺳����� 2 ��λ��д�� int32  ����
     flash_data_union_buffer[3].uint16_type = 65535;                             // �򻺳����� 3 ��λ��д�� uint16 ����
     flash_data_union_buffer[4].int16_type  = -32768;                            // �򻺳����� 4 ��λ��д�� int16  ����
     flash_data_union_buffer[5].uint8_type  = 255;                               // �򻺳����� 5 ��λ��д�� uint8  ����
     flash_data_union_buffer[6].int8_type   = -127;                              // �򻺳����� 6 ��λ��д�� int8   ����
     flash_write_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);     // ��ָ�� Flash ������ҳ��д�뻺��������


     flash_data_buffer_clear();                                                  // ��ջ�����
     printf("\r\n Flash data buffer default data is :");
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ���
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // ���������� 1 ��λ�õ������� uint32 ��ʽ���
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // ���������� 2 ��λ�õ������� int32  ��ʽ���
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // ���������� 3 ��λ�õ������� uint16 ��ʽ���
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // ���������� 4 ��λ�õ������� int16  ��ʽ���
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // ���������� 5 ��λ�õ������� uint8  ��ʽ���
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // ���������� 6 ��λ�õ������� int8   ��ʽ���


     flash_read_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);      // �����ݴ� flash ��ȡ��������
     printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // ���������� 0 ��λ�õ������� float  ��ʽ���
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // ���������� 1 ��λ�õ������� uint32 ��ʽ���
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // ���������� 2 ��λ�õ������� int32  ��ʽ���
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // ���������� 3 ��λ�õ������� uint16 ��ʽ���
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // ���������� 4 ��λ�õ������� int16  ��ʽ���
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // ���������� 5 ��λ�õ������� uint8  ��ʽ���
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // ���������� 6 ��λ�õ������� int8   ��ʽ���
     printf("\r\n");
     // �˴���д�û����� ���������ʼ�������
    interrupt_global_enable();            // ���ж������
    while(1)
    {

    }
}
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� WCH-LINK �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
//      ���������鶼������������û��������ݣ��ͽ�����Կ����Ƿ������ԣ����������Ծ͸���������ҳ�볢�ԣ�������ɲ��У���ô��ϵ����֧��
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
// ����3�����ݲ���
//      ����������ҳ�볢�ԣ�����������ɶ�������ȷ����ϵ����֧��



