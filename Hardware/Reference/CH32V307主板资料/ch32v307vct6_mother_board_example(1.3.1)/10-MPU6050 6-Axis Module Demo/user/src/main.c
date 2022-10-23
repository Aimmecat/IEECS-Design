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

    mpu6050_init();

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        // �ɼ�����
        mpu6050_get_acc();
        mpu6050_get_gyro();
        printf("mpu_gyro_x = %d\r\n",mpu_gyro_x);
        printf("mpu_gyro_y = %d\r\n",mpu_gyro_y);
        printf("mpu_gyro_z = %d\r\n",mpu_gyro_z);

        printf("mpu_acc_x = %d\r\n",mpu_acc_x);
        printf("mpu_acc_y = %d\r\n",mpu_acc_y);
        printf("mpu_acc_z = %d\r\n",mpu_acc_z);

        system_delay_ms(100);
    }
}




