/*
 * PID.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//定义轮子的PI参数
int16   Left_Motor[2]   = {100,10};          //左前轮
int16   Right_Motor[2]  = {100,10};          //右前轮


//定义四个轮子的PID结构体
PID Pid_Left_Motor;                        //左前轮
PID Pid_Right_Motor;                       //右前轮


//定义期望速度，脉冲数，占空比
EXPSPEED    Expspeed    =   {0,0};
PWMDUTY     Duty        =   {0,0};

//-------------------------------------------------------------------------------------------------------------------
//  @brief              单轮PID初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              *sptr       轮子PID结构体指针
//  @param              *MOTOR_PID  轮子PID参数指针
//  @return             void
//  Sample usage:       内部使用 无需关心
//-------------------------------------------------------------------------------------------------------------------
void PID_INIT(PID *sptr, int16 *MOTOR_PID){

    sptr->LastError = 0;
    sptr->LastSpeed = 0;
    sptr->kp        = *(MOTOR_PID+0);
    sptr->ki        = *(MOTOR_PID+1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              四轮与陀螺仪PID初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              void
//  @return             void
//  Sample usage:       内部使用 无需关心
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
//  @brief              增量式PID控制
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              *Sptr               轮子PID结构体
//  @param              real_speed          实际速度,用编码器的值代表
//  @param              expect_speed        期望速度
//  @return             INCREASE            增量(PWM改变量)
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


