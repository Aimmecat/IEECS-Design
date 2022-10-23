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

uint8 send_dat_1[] = {0x11, 0x22, 0x33};
uint8 send_dat_2[] = {0x44, 0x66, 0x88};

uint8 read_dat_1[10];
uint8 read_dat_2[10];


int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

	// 蓝牙模块1初始化
    bluetooth_ch9141_init_ch1();
    bluetooth_ch9141_init_ch2();


    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        // 发送数据。
        bluetooth_ch9141_send_buff_ch1(send_dat_1, 3);
        bluetooth_ch9141_send_buff_ch2(send_dat_2, 3);
        system_delay_ms(1000);
        // 通过在线调试，查看 read_dat_1和read_dat_2 可以查看接收的数据。

        // 读取FIFO里面的数据
        bluetooth_ch9141_read_buff_ch1(read_dat_1, 10);
        bluetooth_ch9141_read_buff_ch2(read_dat_2, 10);

        // 将数据发送出去
        bluetooth_ch9141_send_buff_ch1(read_dat_1, 10);
        bluetooth_ch9141_send_buff_ch2(read_dat_2, 10);

        system_delay_ms(1000);
    }
}
