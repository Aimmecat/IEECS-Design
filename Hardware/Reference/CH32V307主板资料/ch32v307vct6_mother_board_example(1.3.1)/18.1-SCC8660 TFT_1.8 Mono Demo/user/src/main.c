/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/

#include "zf_common_headfile.h"

int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口


    // 显示模式设置为TFT180_PORTAIT
    // 显示模式在 zf_device_tft180.h 文件内的 TFT180_DEFAULT_DISPLAY_DIR 宏定义设置
    tft180_init();     //初始化屏幕
    tft180_show_string(0,0,"MT9V03x");
    tft180_show_string(0,20,"Initializing...");
    // 如果屏幕没有任何显示，请检查屏幕接线
    // 如果屏幕一直显示初始化信息，请检查摄像头接线
    // 如果图像只采集一次，请检查场信号(VSY)是否连接OK?
    scc8660_init_dvp();


    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        if(scc8660_finish_flag_dvp)
        {
            // 使用缩放显示函数，根据原始图像大小 以及设置需要显示的大小自动进行缩放或者放大显示
            tft180_displayimage8660_zoom(scc8660_image_dvp[0], SCC8660_DVP_PIC_W, SCC8660_DVP_PIC_H, 120, 160);
            scc8660_finish_flag_dvp = 0;
        }
    }
}
