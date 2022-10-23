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



//���尴������
#define KEY1    A8
#define KEY2    D8
#define KEY3    B12
#define KEY4    B0

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 test1,test2,test3,test4;

int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���


    // ��ʾģʽ����Ϊ0
    // ��ʾģʽ��zf_device_ips200_parallel8��h�ļ��ڵ�IPS200_DEFAULT_DISPLAY_DIR�궨������
    ips200_init();     //��ʼ��2��IPS��Ļ

    // �����Ļû�б�ף�������Ļ����
    // ������ʼ��
    gpio_init(KEY1, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY2, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY3, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY4, GPI, 0, GPI_PULL_UP);


    interrupt_global_enable();            // ���ж������
    while(1)
    {

        //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
        //���水��״̬
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;

        //��ȡ��ǰ����״̬
        key1_status = gpio_get_level(KEY1);
        key2_status = gpio_get_level(KEY2);
        key3_status = gpio_get_level(KEY3);
        key4_status = gpio_get_level(KEY4);

        //��⵽��������֮��  ���ſ���λ��־λ
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;

        //��־λ��λ֮�󣬿���ʹ�ñ�־λִ���Լ���Ҫ�����¼�
        if(key1_flag)
        {
            key1_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test1++;
        }

        if(key2_flag)
        {
            key2_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test2++;
        }

        if(key3_flag)
        {
            key3_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test3++;
        }

        if(key4_flag)
        {
            key4_flag = 0;//ʹ�ð���֮��Ӧ�������־λ
            test4++;
        }
        // ����Ļ����ʾ���Ա���
        ips200_show_string(0, 0,"KEY1  TEST:");     ips200_show_int(12*8, 0,test1,2);
        ips200_show_string(0,20,"KEY2  TEST:");     ips200_show_int(12*8,20,test2,2);
        ips200_show_string(0,40,"KEY3  TEST:");     ips200_show_int(12*8,40,test3,2);
        ips200_show_string(0,60,"KEY4  TEST:");     ips200_show_int(12*8,60,test4,2);

        system_delay_ms(10);//��ʱ����������Ӧ�ñ�֤����ʱ�䲻С��10ms

    }
}




