/*
 * Encoder.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//����洢��������������
int16 encoder_master_data[2];

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ������������ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Encoder_Master_Init()
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Master_Init(void){

    encoder_init_quad(ENCODER_LEFT_T, ENCODER_LEFT_A, ENCODER_LEFT_B);          //������ʼ��
    encoder_init_quad(ENCODER_RIGHT_R, ENCODER_RIGHT_A, ENCODER_RIGHT_B);       //�ҵ����ʼ��
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ��ȡ��������������
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       Encoder_Master_Get()
//-------------------------------------------------------------------------------------------------------------------
void Encoder_Master_Get(void){

    encoder_master_data[left_encoder]  = -encoder_get_count(ENCODER_LEFT_T);       //������ȡֵ
    encoder_master_data[right_encoder] = encoder_get_count(ENCODER_RIGHT_R);     //������ȡֵ
    if(encoder_master_data[left_encoder] != 0 || encoder_master_data[right_encoder] != 0)
        CalcPos(encoder_master_data[left_encoder], encoder_master_data[right_encoder]);
    encoder_clear_count(ENCODER_LEFT_T);                                          //��ձ�����
    encoder_clear_count(ENCODER_RIGHT_R);                                         //��ձ�����
}

