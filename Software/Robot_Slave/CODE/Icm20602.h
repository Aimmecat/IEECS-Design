/*
 * Icm20602.h
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_ICM20602_H_
#define CODE_ICM20602_H_

//积分时长:5ms
#define DT      0.005f

#define PI      3.1415926

//辅助四元数解算
#define sampleFreq  200.0f         // sample frequency in Hz
#define twoKpDef    (2.0f * 0.5f)   // 2 * proportional gain
#define twoKiDef    (2.0f * 0.0f)   // 2 * integral gain

//计算零漂统计次数
#define CALC_ZOFF_AVARAGE_TIME  100000

typedef struct ROBOT_STYLE{
    int16 pitch;
    int16 yaw;
    int16 roll;
}ROBOT_STYLE;

extern ROBOT_STYLE robot_style;

extern uint8 enable_calc_icm;

extern double gyro_z_off;

void ICM20602_Init(void);
void ICM20602_Get(void);

void angle_calculate(float gx, float gy, float gz, float ax, float ay, float az);

#endif /* CODE_ICM20602_H_ */
