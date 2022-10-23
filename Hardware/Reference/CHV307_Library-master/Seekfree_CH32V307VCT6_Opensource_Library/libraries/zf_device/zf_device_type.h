/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_type
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             
*                   V1.1 2022.03.02 BULETOOTH_CH9141修改为BLUETOOTH_CH9141
********************************************************************************************************************/
#ifndef _zf_device_type_h_
#define _zf_device_type_h_

typedef enum
{
    NO_CAMERE = 0,                                                              // 无摄像头
    CAMERA_BIN,                                                                 // 小钻风
    CAMERA_BIN_UART,                                                            // 小钻风串口版本
    CAMERA_GRAYSCALE,                                                           // 总钻风
    CAMERA_COLOR,                                                               // 凌瞳
}camera_type_enum;

typedef enum
{
    NO_WIRELESS = 0,                                                            // 无设备
    WIRELESS_UART,                                                              // 无线串口
    BLUETOOTH_CH9141,                                                           // CH9141蓝牙模块
    WIRELESS_CH573,                                                             // CH573无线模块
}wireless_type_enum;

extern camera_type_enum camera_type;
extern wireless_type_enum wireless_type;

void set_camera_type (camera_type_enum type_set);
void set_wireless_type (camera_type_enum type_set);

#endif
