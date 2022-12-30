/*
 * Encoder.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef ENCODER_H_
#define ENCODER_H_

//�������ӱ�����ڱ��������������е��÷���
#define left_encoder       0
#define right_encoder      1

#define ENCODER_LEFT_T   TIM10_ENCOEDER
#define ENCODER_LEFT_B   TIM10_CH2_ENCOEDER_D3
#define ENCODER_LEFT_A   TIM10_CH1_ENCOEDER_D1

#define ENCODER_RIGHT_R  TIM9_ENCOEDER
#define ENCODER_RIGHT_B  TIM9_CH2_ENCOEDER_D11
#define ENCODER_RIGHT_A  TIM9_CH1_ENCOEDER_D9

//�ⲿ���ñ���������
extern int16 encoder_master_data[2];


//��������־
extern uint8 roll_flag;


void Encoder_Master_Init(void);
void Encoder_Master_Get(void);

#endif /* ENCODER_H_ */
