/*
 * Style.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef STYLE_H_
#define STYLE_H_

#define PI                  (3.1415926535)
#define L_CENTER            (0.004)         //�����������Ĳ��
#define D                   (0.114)         //�����ְ��᳤
#define DELTA_T             (0.005)         //����ʱ��
#define WHEEL_RADIUS        (0.0325)        //���Ӱ뾶
//#define TransEncoder2v(x)   (x / 15000.0f * 2.0f * PI * WHEEL_RADIUS / DELTA_T)
#define TransEncoder2v(x)   ((x) * 0.00272f)

typedef struct ROBOT_STYLE{
    int16 Xpos;
    int16 Ypos;
    int16 Thpos;
}ROBOT_STYLE;

extern ROBOT_STYLE robot_style;

void CalcPos(void);

#endif /* STYLE_H_ */
