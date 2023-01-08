/*
 * PID.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//�������ӵ�PI����
int16   Left_Motor[2]   = {100,10};          //��ǰ��
int16   Right_Motor[2]  = {100,10};          //��ǰ��


//�����ĸ����ӵ�PID�ṹ��
PID Pid_Left_Motor;                        //��ǰ��
PID Pid_Right_Motor;                       //��ǰ��


//���������ٶȣ���������ռ�ձ�
EXPSPEED    Expspeed    =   {0,0};
PWMDUTY     Duty        =   {0,0};

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����PID��ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              *sptr       ����PID�ṹ��ָ��
//  @param              *MOTOR_PID  ����PID����ָ��
//  @return             void
//  Sample usage:       �ڲ�ʹ�� �������
//-------------------------------------------------------------------------------------------------------------------
void PID_INIT(PID *sptr, int16 *MOTOR_PID){

    sptr->LastError = 0;
    sptr->LastSpeed = 0;
    sptr->kp        = *(MOTOR_PID+0);
    sptr->ki        = *(MOTOR_PID+1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ������������PID��ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              void
//  @return             void
//  Sample usage:       �ڲ�ʹ�� �������
//-------------------------------------------------------------------------------------------------------------------
void ALLPID_INIT(void){
//    *(Left_Motor + 0)  = (int16)parameter[LEFT_PID_P];
//    *(Left_Motor + 1)  = (int16)parameter[LEFT_PID_I];
//    *(Right_Motor + 0) = (int16)parameter[RIGHT_PID_P];
//    *(Right_Motor + 1) = (int16)parameter[RIGHT_PID_I];
    PID_INIT (&Pid_Left_Motor  ,  Left_Motor);
    PID_INIT (&Pid_Right_Motor ,  Right_Motor);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����ʽPID����
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              *Sptr               ����PID�ṹ��
//  @param              real_speed          ʵ���ٶ�,�ñ�������ֵ����
//  @param              expect_speed        �����ٶ�
//  @return             INCREASE            ����(PWM�ı���)
//  Sample usage:       PID_Control(&Left_front_Motor  ,  Pulse.Leftfront * POWER ,   Expspeed.Leftfront);
//-------------------------------------------------------------------------------------------------------------------
int16 PID_Control(PID *Sptr, int16 real_speed, int16 expect_speed)
{

    int16             INCREASE;
    int16             ERROR;
    ERROR           = expect_speed - real_speed;

    INCREASE        = Sptr->kp       * (ERROR - Sptr->LastError)
                    + Sptr->ki       *  ERROR;

    Sptr->LastError = ERROR;

    return            (int16)(INCREASE);
}


