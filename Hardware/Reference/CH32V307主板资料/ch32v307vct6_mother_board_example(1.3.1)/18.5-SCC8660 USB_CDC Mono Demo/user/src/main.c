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

    // USB���⴮�ڳ�ʼ��
    usb_cdc_init();

    // ���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
    scc8660_init_dvp();


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        if(scc8660_finish_flag_dvp)
        {
            // ͨ�����ڣ�����ͼ����λ��
            // ���ڴ���ͼ����λ�� ���ٵ�ԭ���ǣ����ڴ������ݱ������������λ�� �� ����ͷ û�й�ϵ��
            camera_send_image_usb_cdc((uint8_t *)scc8660_image_dvp[0], SCC8660_DVP_W*SCC8660_DVP_H);
            scc8660_finish_flag_dvp = 0;
        }
    }
}
