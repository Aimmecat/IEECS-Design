/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2022,逐飞科技
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
* @date             2022-03-07
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// *************************** 例程硬件连接说明 ***************************
//      模块管脚            单片机管脚
//      RX                  查看zf_device_wireless_ch573.h文件中WIRELESS_CH573_RX_PIN宏定义的引脚 默认 D5
//      TX                  查看zf_device_wireless_ch573.h文件中WIRELESS_CH573_TX_PIN宏定义的引脚 默认 D6
//      RTS                 查看zf_device_wireless_ch573.h文件中WIRELESS_CH573_RTS_PIN宏定义的引脚 默认 E10
//      GND                 电源地
//      VCC                 5V电源

//使用之前请先查看CH573简易版蓝牙组网上位机使用说明书，先进行CH573模块 配置！！！
//使用之前请先查看CH573简易版蓝牙组网上位机使用说明书，先进行CH573模块 配置！！！
//使用之前请先查看CH573简易版蓝牙组网上位机使用说明书，先进行CH573模块 配置！！！

// *************************** 例程测试说明 ***************************
//1. 使用该模块前先使用上位机进行配置
//2. 使用现象：
//单片机通过模块持续发送数据,LED会常亮，其他邻居设备（邻居设备请查看说明书定义）会收到数据
//可以将邻居设备连接到电脑查看接收的数据
//如果邻居设备是排针端，需要使用TTL连接到电脑
//如果邻居设备是USB端，可以直接插到电脑上

//如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************
uint8 send_test_dat[] = {0x44, 0x66, 0x99};
uint8 read_dat[10];
int main(void)
{
    interrupt_global_disable();                        // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);                  // 务必保留，设置系统时钟。
    debug_init();                                   // 务必保留，本函数用于初始化MPU 时钟 调试串口
    gpio_init(E2, GPO, GPIO_HIGH, GPO_PUSH_PULL);   //初始化LED 默认高电平 推挽输出模式

    wireless_ch573_init();

//    if(wireless_ch573_init())                       //初始化失败会在这进入死循环
//    {
//        while(1)
//        {
//            gpio_toggle_level(E2);                  //翻转LED电平
//            system_delay_ms(100);                   //短延时快速闪灯表示异常
//        }
//    }
//    gpio_set_level(E2, 0);

    interrupt_global_enable();                        // 总中断最后开启


    while(1)
    {
        // 发送数据
        wireless_ch573_send_buff(send_test_dat, sizeof(send_test_dat));

        wireless_ch573_read_buff(read_dat, 10);
        wireless_ch573_send_buff(read_dat, 10);

        system_delay_ms(1000);
    }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
//问题1：其他无线CH573模块设备没有收到数据
//使用例程后查看单片机LED有没有快速闪烁，
//LED常亮查看连接单片机的CH573有没有闪烁蓝灯
//CH573蓝灯正常闪烁，检查设备之间有没有配置成功，查看CH573说明书

