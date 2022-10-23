#include <myheadfile.h>

//定义存储编码器读数数组
int16 encoder_master_data[2];

uint8 roll_flag = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              主机编码器初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Encoder_Master_Init()
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Master_Init(void){

    timer_quad_init(TIMER_3, ENCODER_LEFT_A, ENCODER_LEFT_B);
    timer_quad_init(TIMER_2, ENCODER_RIGHT_A, ENCODER_RIGHT_B);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              获取主机编码器读数
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Encoder_Master_Get()
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Master_Get(void){

    encoder_master_data[left_encoder]  = -timer_quad_get(TIMER_3);       //编码器取值
    encoder_master_data[right_encoder] = timer_quad_get(TIMER_2);       //编码器取值
    if(encoder_master_data[left_encoder] != 0 || encoder_master_data[right_encoder] != 0)
        roll_flag = 1;
    else roll_flag = 0;
    CalcPos(encoder_master_data[left_encoder], encoder_master_data[right_encoder]);
    encoder_master_data[left_encoder] <<= 5;
    encoder_master_data[right_encoder] <<= 5;
    timer_quad_clear(TIMER_2);                                                                                                                      //清空计数器
    timer_quad_clear(TIMER_3);                                                                                                                      //清空计数器
}
