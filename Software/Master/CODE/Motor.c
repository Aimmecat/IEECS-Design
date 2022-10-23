#include <myheadfile.h>

//设定速度结构体
SET_SPEED Controlspeed = {0,0};

//-------------------------------------------------------------------------------------------------------------------
//  @brief              电机初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Motor_All_Init()
//-------------------------------------------------------------------------------------------------------------------
void Motor_All_Init(void){

    gpio_init(MOTOR_L_DIR, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(MOTOR_R_DIR, GPO, 0, GPIO_PIN_CONFIG);

    pwm_init(MOTOR_L_PWM,30000,0);
    pwm_init(MOTOR_R_PWM,30000,0);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              车轮PWM设置
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Motor_Set_Duty();
//-------------------------------------------------------------------------------------------------------------------
void Motor_Set_Duty(void){

    Duty.Left_pwmduty  +=  PID_Control(&Pid_Left_Motor ,  *(encoder_master_data + left_encoder ) , Expspeed.Left_expspeed );

    Duty.Right_pwmduty +=  PID_Control(&Pid_Right_Motor,  *(encoder_master_data + right_encoder) , Expspeed.Right_expspeed);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              PWM限幅
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              max_pwm_duty    最大PWM值
//  @param              min_pwm_duty    最小PWM值
//  @return             void
//  Sample usage:       Motor_Speed_Limit(20000);
//-------------------------------------------------------------------------------------------------------------------
void Motor_Speed_Limit(int16 max_pwm_duty){

    Duty.Left_pwmduty  = Range(Duty.Left_pwmduty, -max_pwm_duty,max_pwm_duty);
    Duty.Right_pwmduty = Range(Duty.Right_pwmduty,-max_pwm_duty,max_pwm_duty);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              控制电机移动
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              null
//  @return             void
//  Sample usage:       Moter_Move();
//-------------------------------------------------------------------------------------------------------------------
void Moter_Move(void){

    Duty.Left_pwmduty   > 0     ?   gpio_set(MOTOR_L_DIR, DIR_1) : gpio_set(MOTOR_L_DIR, DIR_0);
    Duty.Right_pwmduty  > 0     ?   gpio_set(MOTOR_R_DIR, DIR_0) : gpio_set(MOTOR_R_DIR, DIR_1);

    pwm_duty(MOTOR_L_PWM, Duty.Left_pwmduty  > 0 ? Duty.Left_pwmduty    : -Duty.Left_pwmduty  );
    pwm_duty(MOTOR_R_PWM, Duty.Right_pwmduty > 0 ? Duty.Right_pwmduty   : -Duty.Right_pwmduty );
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              根据X、Y和角度方向速度设置轮子期望速度(编码器值)
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              null
//  @return             void
//  Sample usage:       Motor_Set_Expect_Speed();
//-------------------------------------------------------------------------------------------------------------------
void Motor_Set_Expect_Speed(void){

    Expspeed.Left_expspeed    =   +(int16)(Controlspeed.Vt * VT_KP) - (int16)(VR_KP * Controlspeed.Vr);
    Expspeed.Right_expspeed   =   +(int16)(Controlspeed.Vt * VT_KP) + (int16)(VR_KP * Controlspeed.Vr);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              设置速度(编码器值)
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              Vt, Vr两个方向的速度
//  @return             void
//  Sample usage:       Motor_Set_Speed(30, 30);
//-------------------------------------------------------------------------------------------------------------------
void Motor_Set_Speed(int16 Vt, int16 Vr){

    Controlspeed.Vt = Vt;
    Controlspeed.Vr = Vr;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              总电机控制函数
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              null
//  @return             void
//  Sample usage:       Motor_Control();
//-------------------------------------------------------------------------------------------------------------------
void Motor_Control(void){

    Motor_Set_Expect_Speed();
    Encoder_Master_Get();
    Motor_Set_Duty();
    Motor_Speed_Limit(MAXDUTY);
    Moter_Move();
}
