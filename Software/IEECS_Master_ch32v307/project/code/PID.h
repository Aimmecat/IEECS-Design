/*
 * PID.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef PID_H_
#define PID_H_

//�ĸ����ӵ�PID�ṹ��
typedef struct PID
{
    int16 LastError;                                    //e[k-1]
    int16 LastSpeed;                                    //u[k-1]

    int16 SumError;

    int16 kp;                                           //p
    int16 ki;                                           //i
} PID;

//�����ٶȽṹ��
typedef struct EXPSPEED
{
    int16 Left_expspeed;                                //��
    int16 Right_expspeed;                               //��
} EXPSPEED;

//ռ�ձȽṹ��ṹ��
typedef struct PWMDUTY
{
    int16 Left_pwmduty;                                 //��ǰ
    int16 Right_pwmduty;                                //��ǰ
} PWMDUTY;

//�����ĸ����ӵ�PID����
extern int16    Left_Motor[2]   ;
extern int16    Right_Motor[2]    ;

//�����ĸ����ӵ�PID�ṹ��
extern PID     Pid_Left_Motor;
extern PID     Pid_Right_Motor;

extern EXPSPEED     Expspeed;                           //�����ٶȽṹ��
extern PWMDUTY      Duty;                               //����ռ�ձȽṹ��

void PID_INIT(PID *sptr, int16 *MOTOR_PID);             //PID��ʼ��
void ALLPID_INIT(void);                                 //���PIDȫ����ʼ��

int16 PID_Control(PID *Sptr, int16 real_speed, int16 expect_speed);

#endif /* PID_H_ */
