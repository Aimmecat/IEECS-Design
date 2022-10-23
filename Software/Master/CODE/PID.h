#ifndef _PID_H
#define _PID_H

//四个轮子的PID结构体
typedef struct PID
{
    int16 LastError;                                    //e[k-1]
    int16 LastSpeed;                                    //u[k-1]

    int16 SumError;

    int16 kp;                                           //p
    int16 ki;                                           //i
} PID;

//期望速度结构体
typedef struct EXPSPEED
{
    int16 Left_expspeed;                                //左
    int16 Right_expspeed;                               //右
} EXPSPEED;

//占空比结构体结构体
typedef struct PWMDUTY
{
    int16 Left_pwmduty;                                 //左前
    int16 Right_pwmduty;                                //右前
} PWMDUTY;

//定义四个轮子的PID参数
extern int16    Left_Motor[2]   ;
extern int16    Right_Motor[2]    ;

//定义四个轮子的PID结构体
extern PID     Pid_Left_Motor;
extern PID     Pid_Right_Motor;

extern EXPSPEED     Expspeed;                           //期望速度结构体
extern PWMDUTY      Duty;                               //设置占空比结构体

void PID_INIT(PID *sptr, int16 *MOTOR_PID);             //PID初始化
void ALLPID_INIT(void);                                 //电机PID全部初始化

int16 PID_Control(PID *Sptr, int16 real_speed, int16 expect_speed);

#endif
