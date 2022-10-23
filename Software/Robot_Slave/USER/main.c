/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
 * @version         查看doc内version文件 版本说明
 * @Software        MounRiver Studio V1.3
 * @Target core     CH32V103R8T6
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-12-04
 ********************************************************************************************************************/
//整套推荐IO查看Projecct文件夹下的TXT文本

//打开新的工程或者工程移动了位置务必执行以下操作
//右键单击工程，选择刷新


#include "myheadfile.h"


int main(void)
{
    DisableGlobalIRQ();
    board_init();                           //务必保留

    uart_init(UART_1, 115200, UART1_TX_A9, UART1_RX_A10);    //配置串口中断号,波特率,TX,RX
    gpio_init(C12, GPI, 1, GPIO_PIN_CONFIG);
//    ICM20602_Init();
    MCUC_Slave_Init();
    Key_Init();
    timer_pit_interrupt_ms(TIMER_2, 5);
    Adc_Init();

    EnableGlobalIRQ(0);

    while(1){
//        Key_Happen();
//        ICM20602_Get();
        Adc_Get();
    }

}

