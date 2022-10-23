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


#define S_MOTOR_PIN   TIM2_PWM_CH1_A15       // 定义舵机引脚
uint16_t duty = 500;

int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口


    // 初始化舵机控制引脚A15, 频率50hz, 占空比 500/10000 * 100% (10000是PWM的满占空比时候的值）
    pwm_init(S_MOTOR_PIN, 50, 500);


    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        // 计算舵机位置舵机位置   （0.5ms - 2.5ms）ms/20ms * 10000（10000是PWM的满占空比时候的值）
        // 舵机最小值为250   最大值为1250
        // 这里加20 减20是为了缩小转动的区域，不要转动过于极限位置，有的舵机在极限位置容易卡住
        duty += 2;
        if((1250-20) < duty) duty = (250+20);

        // 控制舵机达到指定位置
        pwm_set_duty(S_MOTOR_PIN,duty);

        if((250+20) >= duty)    system_delay_ms(1000); // 当从1250的位置   回转到250的位置时   应该使用较长的延时等到舵机达到指定位置
        else                    system_delay_ms(3);    //
    }
}




