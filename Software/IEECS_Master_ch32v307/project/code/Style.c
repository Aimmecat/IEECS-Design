/*
 * Style.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

ROBOT_STYLE robot_style = {0,0,0};

void CalcPos(void){

    static double x_pos = 0.0;
    static double y_pos = 0.0;
    static double robot_theta = 0.0;

    double theta = 0.0;
    double d_plus_r = 0.0;
    double new_x = 0.0;
    double new_y = 0.0;

    int16 left_encoder_num = Encoder_Left_Get();
    int16 right_encoder_num = Encoder_Right_Get();

    double dv = TransEncoder2v(left_encoder_num - right_encoder_num);
    double tv = TransEncoder2v(left_encoder_num + right_encoder_num);
    if(left_encoder_num != right_encoder_num){
        theta = dv * DELTA_T / (2 * D);
        d_plus_r = tv / dv * D;
        new_x = d_plus_r * (1 - cos(theta));
        new_y = d_plus_r * sin(theta);
    }
    else{
        new_x = 0.0;
        new_y = tv * 0.5 * DELTA_T;
    }
    x_pos += cos(robot_theta) * new_x - sin(robot_theta) * new_y;
    y_pos += sin(robot_theta) * new_x + cos(robot_theta) * new_y;
    robot_theta -= theta;
    if(robot_theta < 0.0){
        robot_theta += 2 * PI;
    }
    else if(robot_theta >= 2 * PI){
        robot_theta -= 2 * PI;
    }

    robot_style.Xpos = (int16)(x_pos * 1000);
    robot_style.Ypos = (int16)(y_pos * 1000);
    robot_style.Thpos = (int16)(robot_theta * 4095.0f / (2.0f * PI));
}
