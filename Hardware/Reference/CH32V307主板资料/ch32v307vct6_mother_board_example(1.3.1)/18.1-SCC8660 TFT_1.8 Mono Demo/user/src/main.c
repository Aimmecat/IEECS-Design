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


    // ��ʾģʽ����ΪTFT180_PORTAIT
    // ��ʾģʽ�� zf_device_tft180.h �ļ��ڵ� TFT180_DEFAULT_DISPLAY_DIR �궨������
    tft180_init();     //��ʼ����Ļ
    tft180_show_string(0,0,"MT9V03x");
    tft180_show_string(0,20,"Initializing...");
    // �����Ļû���κ���ʾ��������Ļ����
    // �����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    // ���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?
    scc8660_init_dvp();


    interrupt_global_enable();            // ���ж������
    while(1)
    {
        if(scc8660_finish_flag_dvp)
        {
            // ʹ��������ʾ����������ԭʼͼ���С �Լ�������Ҫ��ʾ�Ĵ�С�Զ��������Ż��߷Ŵ���ʾ
            tft180_displayimage8660_zoom(scc8660_image_dvp[0], SCC8660_DVP_PIC_W, SCC8660_DVP_PIC_H, 120, 160);
            scc8660_finish_flag_dvp = 0;
        }
    }
}
