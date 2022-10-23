/*
 * Style.c
 *
 *  Created on: Sep 1, 2021
 *      Author: Aimmecat
 */

#include "myheadfile.h"

ROBOT_STYLE robot_style = {0,0,0};

float x_pos = 0.0;
float y_pos = 0.0;
float robot_theta = 0.0;

void CalcPos(int left_encoder_num, int right_encoder_num){
    float theta = 0.0;
    float d_plus_r = 0.0;
    float new_x = 0.0;
    float new_y = 0.0;
    float left_v = TransEncoder2v(left_encoder_num);
    float right_v = TransEncoder2v(right_encoder_num);
    float dv = left_v - right_v;
    float tv = left_v + right_v;
    if(fabs(dv - 0) > 1e-8){
        theta = dv / (2 * D) * DELTA_T;
        d_plus_r = tv / dv * D;
        new_x = d_plus_r * (1 - cos(theta));
        new_y = d_plus_r * sin(theta);
    }
    else{
        new_x = 0.0;
        new_y = left_v * DELTA_T;
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

