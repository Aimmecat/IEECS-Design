#ifndef _MOTOR_H
#define _MOTOR_H

#define MOTOR_L_DIR   C11              //定义1电机正反转引脚 左
#define MOTOR_L_PWM   PWM4_CH1_B6      //定义1电机PWM引脚

#define MOTOR_R_DIR   C10              //定义2电机正反转引脚 右
#define MOTOR_R_PWM   PWM4_CH2_B7      //定义2电机PWM引脚

#define DIR_1  1                      //转动方向1
#define DIR_0  0                      //转动方向0

#define MAXDUTY     20000             //最大速度

#define VR_KP       1.618f
#define VT_KP       1.189f

typedef struct SET_SPEED
{
    int16 Vt;                         //前进速度
    int16 Vr;                         //角速度
} SET_SPEED;

extern SET_SPEED Controlspeed;

void Motor_All_Init(void);
void Motor_Set_Duty(void);
void Motor_Speed_Limit(int16 max_pwm_duty);
void Moter_Move(void);
void Motor_Set_Expect_Speed(void);
void Motor_Set_Speed(int16 Vt, int16 Vr);
void Motor_Control(void);

#endif
