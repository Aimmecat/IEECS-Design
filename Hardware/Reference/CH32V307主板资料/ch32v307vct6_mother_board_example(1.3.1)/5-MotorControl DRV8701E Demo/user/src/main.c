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

#define MOTOR1_A   D12                      // 定义1电机正反转引脚
#define MOTOR1_B   TIM4_PWM_CH2_D13         // 定义1电机PWM引脚

#define MOTOR2_A   D15                      // 定义2电机正反转引脚
#define MOTOR2_B   TIM4_PWM_CH3_D14         // 定义2电机PWM引脚

#define MOTOR3_A   A1                       // 定义3电机正反转引脚
#define MOTOR3_B   TIM5_PWM_CH1_A0          // 定义3电机PWM引脚

#define MOTOR4_A   A2                       // 定义4电机正反转引脚
#define MOTOR4_B   TIM5_PWM_CH4_A3          // 定义4电机PWM引脚



int32 speed1_power;
int32 speed2_power;
int32 speed3_power;
int32 speed4_power;

int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口


    // 初始化电机PWM引脚

    // 卓大大的推文中，建议电磁组电机频率选用13K-17K
    // 最大占空比值pwm_set_duty_MAX 可以在zf_driver_pwm.h文件中修改 默认为10000
    // 对于一个PWM模块 包含的所有通道只能输出频率一样 占空比不一样的 PWM CH32V307只有十个定时器模块 每个模块有4个通道
    gpio_init(MOTOR1_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR1_B,17000,0);
    gpio_init(MOTOR2_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR2_B,17000,0);
    gpio_init(MOTOR3_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR3_B,17000,0);
    gpio_init(MOTOR4_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR4_B,17000,0);
    // 这里一共8个通道，分别控制4个电机的正反转
    // 这里需要注意，单片机是无法直接驱动电机的，单片机只能给出控制信号，将控制信号给驱动模块，驱动模块输出电压使得电机转动
    // 可查看我们店铺MOS管驱动模块


    // 设置默认速度  也可以通过在线调试直接修改此值  变化电机速度
    speed1_power = 1500;
    speed2_power = 1500;
    speed3_power = 1500;
    speed4_power = 1500;

    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {
        //如何控制电机的正反转
        //每个电机都有两个驱动信号，其实就是控制这两个驱动信号的占空比（即高电平时间）
        //比如本历程中使用定时器1的0和1通道控制左电机，假设0占空比为50%，1通道为%0,那么电机正转
        //假设0占空比为0%，1通道为%50,那么电机反转，如果都为0，则电机停止

        if(0<=speed1_power) //电机1   正转 设置占空比为 百分之 (1000/TIMER1_pwm_set_duty_MAX*100)
        {
           gpio_set_level(MOTOR1_A, 1);
           pwm_set_duty(MOTOR1_B, speed1_power);
        }
        else                //电机1   反转
        {
           gpio_set_level(MOTOR1_A, 0);
           pwm_set_duty(MOTOR1_B, -speed1_power);
        }

        if(0<=speed2_power) //电机2   正转
        {
           gpio_set_level(MOTOR2_A, 1);
           pwm_set_duty(MOTOR2_B, speed2_power);
        }
        else                //电机2   反转
        {
           gpio_set_level(MOTOR2_A, 0);
           pwm_set_duty(MOTOR2_B, -speed2_power);
        }

        if(0<=speed3_power) //电机3   正转
        {
           gpio_set_level(MOTOR3_A, 1);
           pwm_set_duty(MOTOR3_B, speed3_power);
        }
        else                //电机3   反转
        {
           gpio_set_level(MOTOR3_A, 0);
           pwm_set_duty(MOTOR3_B, -speed3_power);
        }

        if(0<=speed4_power) //电机3   正转
        {
           gpio_set_level(MOTOR4_A, 1);
           pwm_set_duty(MOTOR4_B, speed4_power);
        }
        else                //电机3   反转
        {
           gpio_set_level(MOTOR4_A, 0);
           pwm_set_duty(MOTOR4_B, -speed4_power);
        }
    }
}




