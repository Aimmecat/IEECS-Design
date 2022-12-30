/*
 * Encoder.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//定义存储编码器读数数组
int16 encoder_master_data[2];

//-------------------------------------------------------------------------------------------------------------------
//  @brief              主机编码器初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Encoder_Master_Init()
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Master_Init(void){

    encoder_init_quad(ENCODER_LEFT_T, ENCODER_LEFT_A, ENCODER_LEFT_B);          //左电机初始化
    encoder_init_quad(ENCODER_RIGHT_R, ENCODER_RIGHT_A, ENCODER_RIGHT_B);       //右电机初始化
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

    encoder_master_data[left_encoder]  = -encoder_get_count(ENCODER_LEFT_T);       //编码器取值
    encoder_master_data[right_encoder] = encoder_get_count(ENCODER_RIGHT_R);     //编码器取值
    if(encoder_master_data[left_encoder] != 0 || encoder_master_data[right_encoder] != 0)
        CalcPos(encoder_master_data[left_encoder], encoder_master_data[right_encoder]);
    encoder_clear_count(ENCODER_LEFT_T);                                          //清空编码器
    encoder_clear_count(ENCODER_RIGHT_R);                                         //清空编码器
}

