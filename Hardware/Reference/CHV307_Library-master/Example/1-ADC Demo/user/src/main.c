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
// 使用逐飞科技 WCH-LINK 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 B10
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 B11
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源

// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在串口助手上看到如下串口信息：
//      ADC_0 = x
//      ...
//      ...
//      ...
// 5.将 ADC_CHANNELx 宏定义对应的引脚分别接到 3V3/GND 再对应的信息会看到数据变化
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查


// **************************** 代码区域 ****************************

#define ADC_CHANNEL1            ADC_IN12_C2
#define ADC_CHANNEL2            ADC_IN13_C3
#define ADC_CHANNEL3            ADC_IN14_C4
#define ADC_CHANNEL4            ADC_IN15_C5

uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    adc_init(ADC_CHANNEL1);
    adc_init(ADC_CHANNEL2);
    adc_init(ADC_CHANNEL3);
    adc_init(ADC_CHANNEL4);

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {

        dat[0] = adc_convert(ADC_CHANNEL1, ADC_12BIT);
        dat[1] = adc_convert(ADC_CHANNEL2, ADC_12BIT);
        dat[2] = adc_convert(ADC_CHANNEL3, ADC_12BIT);
        dat[3] = adc_convert(ADC_CHANNEL4, ADC_12BIT);
        printf("ADC_0 = %d\r\n", dat[0]);
        printf("ADC_1 = %d\r\n", dat[1]);
        printf("ADC_2 = %d\r\n", dat[2]);
        printf("ADC_3 = %d\r\n", dat[3]);

        system_delay_ms(100);

    }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 WCH-LINK 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：显示数值与接入电压相差过大
//      检查信号引脚是否接对，信号线是否松动
//      使用万用表测量实际引脚上电压是多少 然后按照 voltage/3V3*4096 计算
