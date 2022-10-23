/*
 * Icm20602.c
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#include "myheadfile.h"

ROBOT_STYLE robot_style = {0,0,0};

#include <myheadfile.h>

// 允许积分
uint8 enable_calc_icm;

//z轴零漂
double gyro_z_off;

//偏航角
float yaw = 0.0f ,yaw_last = 0.0f;

float pitch;

volatile float twoKp = twoKpDef;                                            // 2 * proportional gain (Kp)
volatile float twoKi = twoKiDef;                                            // 2 * integral gain (Ki)
volatile float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;                    // quaternion of sensor frame relative to auxiliary frame
volatile float integralFBx = 0.0f,  integralFBy = 0.0f, integralFBz = 0.0f; // integral error terms scaled by Ki


//-------------------------------------------------------------------------------------------------------------------
//  @brief              陀螺仪初始化 默认用SPI通讯,计算零漂
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       ICM20602_Init()
//-------------------------------------------------------------------------------------------------------------------
void ICM20602_Init(void){

    icm20602_init_spi();
    for(int i = 0;i < CALC_ZOFF_AVARAGE_TIME; i++){
        get_icm20602_gyro_spi();
        gyro_z_off += icm_gyro_z / 100.0f;
    }
    gyro_z_off /= 1000.0f;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              获取陀螺仪数据,已消除零漂
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       ICM20602_Get()
//-------------------------------------------------------------------------------------------------------------------
void ICM20602_Get(void){

    get_icm20602_gyro_spi();
    get_icm20602_accdata_spi();
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              四元数解算pitch
//  @author             Ji Xiaoyu
//  @update             2021-7-26
//  @param              None
//  @return             void
//  Sample usage:       angle_calculate()
//-------------------------------------------------------------------------------------------------------------------
void angle_calculate(float gx, float gy, float gz, float ax, float ay, float az) {
    float recipNorm;
    float halfvx, halfvy, halfvz;
    float halfex, halfey, halfez;

    gx *= 0.001064f;
    gy *= 0.001064f;
    gz = (gz - gyro_z_off) * 0.001064f;

    // 只在加速度计数据有效时才进行运算
    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
        // 将加速度计得到的实际重力加速度向量v单位化
        recipNorm = invSqrt(ax * ax + ay * ay + az * az); //该函数返回平方根的倒数
        ax *= recipNorm;
        ay *= recipNorm;
        az *= recipNorm;

        // 通过四元数得到理论重力加速度向量g
        // 注意，这里实际上是矩阵第三列*1/2，在开头对Kp Ki的宏定义均为2*增益
        // 这样处理目的是减少乘法运算量
        halfvx = q1 * q3 - q0 * q2;
        halfvy = q0 * q1 + q2 * q3;
        halfvz = q0 * q0 - 0.5f + q3 * q3;

        // 对实际重力加速度向量v与理论重力加速度向量g做外积
        halfex = (ay * halfvz - az * halfvy);
        halfey = (az * halfvx - ax * halfvz);
        halfez = (ax * halfvy - ay * halfvx);

        if(twoKi > 0.0f){
            // 在PI补偿器中积分项使能情况下计算并应用积分项
            integralFBx += twoKi * halfex * DT;
            integralFBy += twoKi * halfey * DT;
            integralFBz += twoKi * halfez * DT;

            // 应用误差补偿中的积分项
            gx += integralFBx;
            gy += integralFBy;
            gz += integralFBz;
        }
        else{
            integralFBx = 0.0f;
            integralFBy = 0.0f;
            integralFBz = 0.0f;
        }


        // 应用误差补偿中的比例项
        gx += twoKp * halfex;
        gy += twoKp * halfey;
        gz += twoKp * halfez;
    }

    // 微分方程迭代求解
    gx *= (0.5f * DT);     // pre-multiply common factors
    gy *= (0.5f * DT);
    gz *= (0.5f * DT);
    q0 += (-q1 * gx - q2 * gy - q3 * gz);
    q1 += (q0 * gx + q2 * gz - q3 * gy);
    q2 += (q0 * gy - q1 * gz + q3 * gx);
    q3 += (q0 * gz + q1 * gy - q2 * gx);

    // Normalise quaternion
    // 单位化四元数 保证四元数在迭代过程中保持单位性质
    recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 *= recipNorm;
    q1 *= recipNorm;
    q2 *= recipNorm;
    q3 *= recipNorm;

    //10 计算姿态角
    //robot_style.roll  =   (int16)(4095.0    / (2 * PI) * atan2(q0 * q1 + q2 * q3  , 1-2*(q1*q1+q2*q2)));
    //robot_style.pitch =   (int16)(4095.0    / (2 * PI) * asin(2*(q0 * q2 - q1 * q3)));
    float tmp_yaw = atan2(q0 * q3 + q1 * q2  , 1-2*(q2*q2+q3*q3));
    if(tmp_yaw < 0)
        tmp_yaw += 2 * PI;
    robot_style.yaw = (int16)(4095.0    / (2 * PI) * tmp_yaw);
}





