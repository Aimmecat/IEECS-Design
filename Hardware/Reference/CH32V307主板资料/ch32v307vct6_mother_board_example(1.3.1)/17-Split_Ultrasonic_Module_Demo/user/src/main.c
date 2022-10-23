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


#define SPLIT_ULTRASONIC_UART       UART_8
#define SPLIT_ULTRASONIC_BAUD       115200
#define SPLIT_ULTRASONIC_RX         UART8_TX_E14        // 有来有去的 UART-RX 引脚 要接在单片机 TX 上
#define SPLIT_ULTRASONIC_TX         UART8_RX_E15        // 有来有去的 UART-TX 引脚 要接在单片机 RX 上

#define SEND_PORT_PIN               D10                 // 设置对应端口 有去模块发送 这里其实可以不用控制


uint16 ranging_counter = 0;                             // 测距数据
uint8 ranging_flage = 0x00;                             // 测距状态

uint8 receipt_data;
uint8 dat[3];
uint8 num;


int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    //此处编写用户代码(例如：外设初始化代码等)
    gpio_init(SEND_PORT_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);         // 初始化有去模块使能引脚
    uart_init(SPLIT_ULTRASONIC_UART, SPLIT_ULTRASONIC_BAUD, SPLIT_ULTRASONIC_RX, SPLIT_ULTRASONIC_TX);
    uart_rx_interrupt(SPLIT_ULTRASONIC_UART, ENABLE);

    gpio_set_level(SEND_PORT_PIN, GPIO_HIGH);                       // 拉高使能 有去模块发送 实际接上电上拉就开始发送 程序可以不用控制

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        //此处编写需要循环执行的代码
        if(ranging_flage)                                                 // 等待测距完毕
        {
            printf("\r\nRanging counter us is %d.", ranging_counter);     // 输出测距信息
            ranging_flage = 0x00;
        }
        system_delay_ms(100);                                             // 延时
        //此处编写需要循环执行的代码
    }
}

//此函数需要在串口8中断里面进行调用。
//如果不调用这个函数，ranging_counter 的值永远都是0
void uart_handler (void)
{
    uart_query_byte(SPLIT_ULTRASONIC_UART, &receipt_data);
    dat[num] = receipt_data;
    if(dat[0] != 0xa5)  num = 0;                                                    //检查第一个数据是否为0xa5
    else                num++;

    if(num == 3)                                                                    //接收完成 开始处理数据
    {
        num = 0;
        ranging_counter = dat[1]<<8 | dat[2];                                       //得到超声波模块测出的距离
        ranging_flage = 0x01;
    }
}


