/*
 * Motor.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_L_DIR   A8                    //������������ת����
#define MOTOR_L_PWM   TIM4_PWM_CH1_D12      //��������PWM����

#define MOTOR_R_DIR   A9                    //�����ҵ������ת����
#define MOTOR_R_PWM   TIM4_PWM_CH2_D13      //�����ҵ��PWM����

#define DIR_1  1                            //ת������1
#define DIR_0  0                            //ת������0

#define MAXDUTY     20000                   //����ٶ�

#define VR_KP       0.731f
#define VT_KP       0.367f

typedef struct SET_SPEED
{
    int16 Vt;                               //ǰ���ٶ�
    int16 Vr;                               //���ٶ�
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
