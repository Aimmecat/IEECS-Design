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
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� A9
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� A10
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ
// ������������������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      A                   ENCODER_QUADDEC_A �궨������� Ĭ�� B4
//      B                   ENCODER_QUADDEC_B �궨������� Ĭ�� B5
//      GND                 ���İ��Դ�� GND
//      3V3                 ���İ� 3V3 ��Դ
// ���뷽�����������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      LSB                 ENCODER_DIR_PULSE �궨������� Ĭ�� B6
//      DIR                 ENCODER_DIR_DIR �궨������� Ĭ�� B7
//      GND                 ���İ��Դ�� GND
//      3V3                 ���İ� 3V3 ��Դ

// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�����Ӻñ��������ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      ENCODER_QUADDEC counter     x .
//      ENCODER_DIR counter         x .
// 5.ת���������ͻῴ����ֵ�仯
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************
#define ENCODER_QUADDEC                 TIM9_ENCOEDER
#define ENCODER_QUADDEC_B               TIM9_CH2_ENCOEDER_D11
#define ENCODER_QUADDEC_A               TIM9_CH1_ENCOEDER_D9

#define ENCODER_DIR                     TIM1_ENCOEDER
#define ENCODER_DIR_PULSE               TIM1_CH2_ENCOEDER_E11
#define ENCODER_DIR_DIR                 TIM1_CH1_ENCOEDER_E9

#include "zf_common_headfile.h"

int16 encoder_data = 0;

int main(void)
{
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // ��ʱ��������ģʽ�ɼ���ʼ��
	// ʹ�ö�ʱ��1��E9 �� E11��Ϊ��������
    encoder_init_dir(ENCODER_DIR, ENCODER_DIR_DIR, ENCODER_DIR_PULSE);          // ��ʼ��������ģ�������� ����������������ģʽ
    encoder_init_quad(ENCODER_QUADDEC, ENCODER_QUADDEC_A, ENCODER_QUADDEC_B);   // ��ʼ��������ģ�������� �������������ģʽ


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        encoder_data = encoder_get_count(ENCODER_QUADDEC);                      // ��ȡ����������
        encoder_clear_count(ENCODER_QUADDEC);                                   // ��ձ���������
        printf("ENCODER_QUADDEC counter \t%d .\r\n", encoder_data);             // ���������������Ϣ

//        encoder_data = encoder_get_count(ENCODER_DIR);                          // ��ȡ����������
//        encoder_clear_count(ENCODER_DIR);                                       // ��ձ���������
//        printf("ENCODER_DIR counter \t\t%d .\r\n", encoder_data);               // ���������������Ϣ

        system_delay_ms(100);
    }
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
// ����3����ֵһֱ������һ��ת
//      ��Ҫ�ѷ����������������������ģʽ�Ľӿ���
// ����4����ֵ�������ת���仯
//      ���ʹ��������ԣ��������Ҫ�õ�ع���
//      ���������Ƿ��������ģ����Ƿ��ɶ����������Ƿ������ˣ��Ƿ�Ӵ���




