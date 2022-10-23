/*
 * Style.h
 *
 *  Created on: Sep 1, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_STYLE_H_
#define CODE_STYLE_H_

#define PI                  (3.1415926535)
#define D                   (0.078)
#define DELTA_T             (0.02)
#define TransEncoder2v(x)   (x / 390.0f * 0.21f / DELTA_T)

typedef struct ROBOT_STYLE{
    int16 Xpos;
    int16 Ypos;
    int16 Thpos;
}ROBOT_STYLE;

extern ROBOT_STYLE robot_style;
extern float robot_theta;

void CalcPos(int left_encoder_num, int right_encoder_num);

#endif /* CODE_STYLE_H_ */
