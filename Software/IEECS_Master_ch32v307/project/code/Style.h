/*
 * Style.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef STYLE_H_
#define STYLE_H_

#define PI                  (3.1415926535)
#define L_CENTER            (0.004)         //车轮轴与中心差距
#define D                   (0.114)         //左右轮半轴长
#define DELTA_T             (0.02)          //积分时间
#define WHEEL_RADIUS        (0.0325)        //轮子半径
#define TransEncoder2v(x)   (x / 15000.0f * 2.0f * PI * WHEEL_RADIUS / DELTA_T)

typedef struct ROBOT_STYLE{
    int16 Xpos;
    int16 Ypos;
    int16 Thpos;
}ROBOT_STYLE;

extern ROBOT_STYLE robot_style;
extern float robot_theta;

void CalcPos(int left_encoder_num, int right_encoder_num);

#endif /* STYLE_H_ */
