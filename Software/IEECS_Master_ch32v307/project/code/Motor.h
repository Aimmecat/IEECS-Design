/*
 * Motor.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_L_DIR   A8                    //定义左电机正反转引脚
#define MOTOR_L_PWM   TIM4_PWM_CH1_D12      //定义左电机PWM引脚

#define MOTOR_R_DIR   A9                    //定义右电机正反转引脚
#define MOTOR_R_PWM   TIM4_PWM_CH2_D13      //定义右电机PWM引脚

#define DIR_1  1                            //转动方向1
#define DIR_0  0                            //转动方向0

#define MAXDUTY     20000                   //最大速度

#define VR_KP       0.731f
#define VT_KP       0.367f

typedef struct SET_SPEED
{
    int16 Vt;                               //前进速度
    int16 Vr;                               //角速度
} SET_SPEED;

extern SET_SPEED Controlspeed;

void Motor_All_Init(void);
void Motor_Set_Duty(void);
void Motor_Speed_Limit(int16 max_pwm_duty);
void Moter_Move(void);
void Motor_Set_Expect_Speed(void);
void Motor_Set_Speed(int16 Vt, int16 Vr);
void Motor_Control(void);

#endif /* MOTOR_H_ */
