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

    tft180_init();     //初始化屏幕

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        tft180_show_string(0,0,"seekfree");             //显示字符串
        tft180_show_int(0,20,-56, 4);                    //显示一个8位有符号型数字
        tft180_show_uint(0,40,56, 4);                    //显示一个8位无符号型数字
        tft180_show_float(0,60,56.356,2,2);             //显示一个浮点数 去除无效0位  整数位显示5位  小数位显示2位

        system_delay_ms(2000);

        tft180_clear(RGB565_BLUE);
        system_delay_ms(500);
        tft180_clear(RGB565_RED);
        system_delay_ms(500);
        tft180_clear(RGB565_YELLOW);
        system_delay_ms(500);
        tft180_clear(RGB565_WHITE);
    }
}




