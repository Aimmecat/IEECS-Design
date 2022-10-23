#ifndef _MOTOR_H
#define _MOTOR_H

#define MOTOR_L_DIR   C11              //����1�������ת���� ��
#define MOTOR_L_PWM   PWM4_CH1_B6      //����1���PWM����

#define MOTOR_R_DIR   C10              //����2�������ת���� ��
#define MOTOR_R_PWM   PWM4_CH2_B7      //����2���PWM����

#define DIR_1  1                      //ת������1
#define DIR_0  0                      //ת������0

#define MAXDUTY     20000             //����ٶ�

#define VR_KP       1.618f
#define VT_KP       1.189f

typedef struct SET_SPEED
{
    int16 Vt;                         //ǰ���ٶ�
    int16 Vr;                         //���ٶ�
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
