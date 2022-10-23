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

// *************************** 例程硬件连接说明 ***************************
// 核心板正常供电即可 无需额外连接

// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，完成上电
// 2.如果E7引脚输入低电平，则LED E2亮，否则LED E2灭。

// **************************** 代码区域 ****************************
#include "zf_common_headfile.h"

uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 初始化E2引脚，作为LED
    gpio_init(E2, GPO, GPIO_LOW, GPO_PUSH_PULL);
    // 初始化E7引脚，作为输入引脚使用
    gpio_init(E7, GPI, GPIO_LOW, GPI_PULL_UP);

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        // 如果E7引脚输入低电平，则LED E2亮，否则LED E2灭。
        if(gpio_get_level(E7))
        {
            gpio_set_level(E2, GPIO_HIGH);
        }
        else
        {
            gpio_set_level(E2, GPIO_LOW);
        }
    }
}

// **************************** 代码区域 ****************************


