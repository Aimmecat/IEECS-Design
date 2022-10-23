#ifndef _ENCODER_H
#define _ENCODER_H

//定义轮子编号用于编码器读数数组中调用方便
#define left_encoder       0
#define right_encoder      1

#define ENCODER_LEFT_A   TIMER3_CHA_B4
#define ENCODER_LEFT_B   TIMER3_CHB_B5

#define ENCODER_RIGHT_A  TIMER2_CHA_A15
#define ENCODER_RIGHT_B  TIMER2_CHB_B3

//外部调用编码器数组
extern int16 encoder_master_data[2];


//允许计算标志
extern uint8 roll_flag;


void Encoder_Master_Init(void);
void Encoder_Master_Get(void);


#endif
