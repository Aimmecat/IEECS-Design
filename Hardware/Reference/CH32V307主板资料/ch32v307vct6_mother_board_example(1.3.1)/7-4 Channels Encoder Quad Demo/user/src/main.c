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

int16_t encoder_data[4];
int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 一个定时器只能做一件事情。例如这个编码器用作了PWM输出，就不能做其他的用了。
    // 使用定时器1做编码器解码(正交解码模式)
    encoder_init_quad(TIM1_ENCOEDER, TIM1_CH1_ENCOEDER_E9, TIM1_CH2_ENCOEDER_E11);
    // 使用定时器3做编码器解码(正交解码模式)
    encoder_init_quad(TIM3_ENCOEDER, TIM3_CH1_ENCOEDER_C6, TIM3_CH2_ENCOEDER_C7);
    // 使用定时器9做编码器解码(正交解码模式)
    encoder_init_quad(TIM9_ENCOEDER, TIM9_CH1_ENCOEDER_D9, TIM9_CH2_ENCOEDER_D11);
    // 使用定时器10做编码器解码(正交解码模式)
    encoder_init_quad(TIM10_ENCOEDER, TIM10_CH1_ENCOEDER_D1, TIMER10_CH2_ENCOEDER_D3);

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {

        encoder_data[0] = encoder_get_count(TIM1_ENCOEDER);     // 定时器取值
        encoder_clear_count(TIM1_ENCOEDER);                     // 定时器清空

        encoder_data[1] = encoder_get_count(TIM3_ENCOEDER);     // 定时器取值
        encoder_clear_count(TIM3_ENCOEDER);                     // 定时器清空

        encoder_data[2] = encoder_get_count(TIM9_ENCOEDER);     // 定时器取值
        encoder_clear_count(TIM9_ENCOEDER);                     // 定时器清空

        encoder_data[3] = encoder_get_count(TIM10_ENCOEDER);    // 定时器取值
        encoder_clear_count(TIM10_ENCOEDER);                    // 定时器清空

        printf("encoder_1 = %d\r\n", encoder_data[0]);
        printf("encoder_2 = %d\r\n", encoder_data[1]);
        printf("encoder_3 = %d\r\n", encoder_data[2]);
        printf("encoder_4 = %d\r\n", encoder_data[3]);

        system_delay_ms(100);
    }
}




