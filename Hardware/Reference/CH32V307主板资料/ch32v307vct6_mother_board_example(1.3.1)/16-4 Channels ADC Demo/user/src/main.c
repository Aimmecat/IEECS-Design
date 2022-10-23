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



uint16 dat[8];



int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // ADC初始化
    adc_init(ADC_IN7_A7);               // ADC初始化 引脚A7
    adc_init(ADC_IN9_B1);               // ADC初始化 引脚B1
    adc_init(ADC_IN10_C0);              // ADC初始化 引脚C0
    adc_init(ADC_IN11_C1);              // ADC初始化 引脚C1


    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        dat[0] = adc_convert(ADC_IN7_A7, ADC_12BIT);    // ADC取值 引脚A7 ,分辨率12位
        dat[1] = adc_convert(ADC_IN9_B1, ADC_8BIT);    // ADC取值 引脚B1 ,分辨率8位
        dat[2] = adc_convert(ADC_IN10_C0, ADC_10BIT);   // ADC取值 引脚C0 ,分辨率10位
        dat[3] = adc_convert(ADC_IN11_C1, ADC_12BIT);   // ADC取值 引脚C1 ,分辨率12位
        printf("ADC_0 = %d\r\n", dat[0]);
        printf("ADC_1 = %d\r\n", dat[1]);
        printf("ADC_2 = %d\r\n", dat[2]);
        printf("ADC_3 = %d\r\n", dat[3]);


        system_delay_ms(100);
    }
}
