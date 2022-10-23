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

// *************************** 例程硬件连接说明 ***************************
// 无

// *************************** 例程测试说明 ***************************
// 1.E2和E9为LED引脚，每过200ms翻转一次

// **************************** 代码区域 ****************************
uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    gpio_init(E2, GPO, GPIO_LOW, GPO_PUSH_PULL);
    gpio_init(E9, GPO, GPIO_LOW, GPO_PUSH_PULL);

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        gpio_toggle_level(E2);
        system_delay_ms(100);
        gpio_toggle_level(E9);
        system_delay_ms(100);
    }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1:LED不闪烁
//       LED灯坏了


