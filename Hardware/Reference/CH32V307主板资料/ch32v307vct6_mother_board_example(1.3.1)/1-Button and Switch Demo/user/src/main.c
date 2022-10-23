/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"



//定义按键引脚
#define KEY1    A8
#define KEY2    D8
#define KEY3    B12
#define KEY4    B0

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//开关标志位
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;

uint8 test1,test2,test3,test4;

int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口


    // 显示模式设置为0
    // 显示模式在zf_device_ips200_parallel8的h文件内的IPS200_DEFAULT_DISPLAY_DIR宏定义设置
    ips200_init();     //初始化2寸IPS屏幕

    // 如果屏幕没有变白，请检查屏幕接线
    // 按键初始化
    gpio_init(KEY1, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY2, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY3, GPI, 0, GPI_PULL_UP);
    gpio_init(KEY4, GPI, 0, GPI_PULL_UP);


    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {

        //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
        //保存按键状态
        key1_last_status = key1_status;
        key2_last_status = key2_status;
        key3_last_status = key3_status;
        key4_last_status = key4_status;

        //读取当前按键状态
        key1_status = gpio_get_level(KEY1);
        key2_status = gpio_get_level(KEY2);
        key3_status = gpio_get_level(KEY3);
        key4_status = gpio_get_level(KEY4);

        //检测到按键按下之后  并放开置位标志位
        if(key1_status && !key1_last_status)    key1_flag = 1;
        if(key2_status && !key2_last_status)    key2_flag = 1;
        if(key3_status && !key3_last_status)    key3_flag = 1;
        if(key4_status && !key4_last_status)    key4_flag = 1;

        //标志位置位之后，可以使用标志位执行自己想要做的事件
        if(key1_flag)
        {
            key1_flag = 0;//使用按键之后，应该清除标志位
            test1++;
        }

        if(key2_flag)
        {
            key2_flag = 0;//使用按键之后，应该清除标志位
            test2++;
        }

        if(key3_flag)
        {
            key3_flag = 0;//使用按键之后，应该清除标志位
            test3++;
        }

        if(key4_flag)
        {
            key4_flag = 0;//使用按键之后，应该清除标志位
            test4++;
        }
        // 在屏幕上显示测试变量
        ips200_show_string(0, 0,"KEY1  TEST:");     ips200_show_int(12*8, 0,test1,2);
        ips200_show_string(0,20,"KEY2  TEST:");     ips200_show_int(12*8,20,test2,2);
        ips200_show_string(0,40,"KEY3  TEST:");     ips200_show_int(12*8,40,test3,2);
        ips200_show_string(0,60,"KEY4  TEST:");     ips200_show_int(12*8,60,test4,2);

        system_delay_ms(10);//延时，按键程序应该保证调用时间不小于10ms

    }
}




