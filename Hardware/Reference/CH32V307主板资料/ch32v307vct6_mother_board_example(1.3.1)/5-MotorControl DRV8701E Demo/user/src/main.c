/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             main
* @company          �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"

#define MOTOR1_A   D12                      // ����1�������ת����
#define MOTOR1_B   TIM4_PWM_CH2_D13         // ����1���PWM����

#define MOTOR2_A   D15                      // ����2�������ת����
#define MOTOR2_B   TIM4_PWM_CH3_D14         // ����2���PWM����

#define MOTOR3_A   A1                       // ����3�������ת����
#define MOTOR3_B   TIM5_PWM_CH1_A0          // ����3���PWM����

#define MOTOR4_A   A2                       // ����4�������ת����
#define MOTOR4_B   TIM5_PWM_CH4_A3          // ����4���PWM����



int32 speed1_power;
int32 speed2_power;
int32 speed3_power;
int32 speed4_power;

int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���


    // ��ʼ�����PWM����

    // ׿���������У�����������Ƶ��ѡ��13K-17K
    // ���ռ�ձ�ֵpwm_set_duty_MAX ������zf_driver_pwm.h�ļ����޸� Ĭ��Ϊ10000
    // ����һ��PWMģ�� ����������ͨ��ֻ�����Ƶ��һ�� ռ�ձȲ�һ���� PWM CH32V307ֻ��ʮ����ʱ��ģ�� ÿ��ģ����4��ͨ��
    gpio_init(MOTOR1_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR1_B,17000,0);
    gpio_init(MOTOR2_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR2_B,17000,0);
    gpio_init(MOTOR3_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR3_B,17000,0);
    gpio_init(MOTOR4_A, GPO, 0, GPIO_PIN_CONFIG);
    pwm_init(MOTOR4_B,17000,0);
    // ����һ��8��ͨ�����ֱ����4�����������ת
    // ������Ҫע�⣬��Ƭ�����޷�ֱ����������ģ���Ƭ��ֻ�ܸ��������źţ��������źŸ�����ģ�飬����ģ�������ѹʹ�õ��ת��
    // �ɲ鿴���ǵ���MOS������ģ��


    // ����Ĭ���ٶ�  Ҳ����ͨ�����ߵ���ֱ���޸Ĵ�ֵ  �仯����ٶ�
    speed1_power = 1500;
    speed2_power = 1500;
    speed3_power = 1500;
    speed4_power = 1500;

    interrupt_global_enable();            // ���ж������
    while(1)
    {
        //��ο��Ƶ��������ת
        //ÿ������������������źţ���ʵ���ǿ��������������źŵ�ռ�ձȣ����ߵ�ƽʱ�䣩
        //���籾������ʹ�ö�ʱ��1��0��1ͨ����������������0ռ�ձ�Ϊ50%��1ͨ��Ϊ%0,��ô�����ת
        //����0ռ�ձ�Ϊ0%��1ͨ��Ϊ%50,��ô�����ת�������Ϊ0������ֹͣ

        if(0<=speed1_power) //���1   ��ת ����ռ�ձ�Ϊ �ٷ�֮ (1000/TIMER1_pwm_set_duty_MAX*100)
        {
           gpio_set_level(MOTOR1_A, 1);
           pwm_set_duty(MOTOR1_B, speed1_power);
        }
        else                //���1   ��ת
        {
           gpio_set_level(MOTOR1_A, 0);
           pwm_set_duty(MOTOR1_B, -speed1_power);
        }

        if(0<=speed2_power) //���2   ��ת
        {
           gpio_set_level(MOTOR2_A, 1);
           pwm_set_duty(MOTOR2_B, speed2_power);
        }
        else                //���2   ��ת
        {
           gpio_set_level(MOTOR2_A, 0);
           pwm_set_duty(MOTOR2_B, -speed2_power);
        }

        if(0<=speed3_power) //���3   ��ת
        {
           gpio_set_level(MOTOR3_A, 1);
           pwm_set_duty(MOTOR3_B, speed3_power);
        }
        else                //���3   ��ת
        {
           gpio_set_level(MOTOR3_A, 0);
           pwm_set_duty(MOTOR3_B, -speed3_power);
        }

        if(0<=speed4_power) //���3   ��ת
        {
           gpio_set_level(MOTOR4_A, 1);
           pwm_set_duty(MOTOR4_B, speed4_power);
        }
        else                //���3   ��ת
        {
           gpio_set_level(MOTOR4_A, 0);
           pwm_set_duty(MOTOR4_B, -speed4_power);
        }
    }
}




