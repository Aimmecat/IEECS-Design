#include "myheadfile.h"

uint8 send_to_master_buff[LINE_LEN];                        //从机向主机发送数据BUFF

//采集的测距数据
int16 sonar_data[8];

//采集的AD数据
int16 adc_data[4];


//-------------------------------------------------------------------------------------------------------------------
//  @brief      主机单片机通讯初始化函数
//  @param      void
//  @return     void
//  Sample usage:   MCUC_Slave_Init()
//-------------------------------------------------------------------------------------------------------------------
void MCUC_Slave_Init(void)
{
    gpio_init(A0, GPO, 0, GPIO_PIN_CONFIG);                 //同步引脚初始化
    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //串口3初始化，波特率460800
    timer_pit_interrupt_ms(TIMER_4, 5);                     //定时器4初始化
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取传感器数据
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void get_sensor_data(void)
{
    //示例
    sonar_data[0] = 1;
    sonar_data[1] = 10;
    sonar_data[2] = 100;
    sonar_data[3] = 2;
    sonar_data[4] = 20;
    sonar_data[5] = 200;
    sonar_data[6] = 3;
    sonar_data[7] = 300;
    adc_data[0] = 255;
    adc_data[1] = 125;
    adc_data[2] = 25;
    adc_data[3] = 199;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      根据协议处理数据
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void process_data(void)
{
    send_to_master_buff[0]  = 0xD8;                          //帧头

    send_to_master_buff[1]  = 0xB0;                          //功能字        sonar-0
    send_to_master_buff[2]  = *(sonar_data + 0)>>8;          //数据高8位
    send_to_master_buff[3]  = *(sonar_data + 0)&0xFF;        //数据低8位

    send_to_master_buff[4]  = 0xB1;                          //功能字        sonar-1
    send_to_master_buff[5]  = *(sonar_data + 1)>>8;          //数据高8位
    send_to_master_buff[6]  = *(sonar_data + 1)&0xFF;        //数据低8位

    send_to_master_buff[7]  = 0xB2;                          //功能字        sonar-2
    send_to_master_buff[8]  = *(sonar_data + 2)>>8;          //数据高8位
    send_to_master_buff[9]  = *(sonar_data + 2)&0xFF;        //数据低8位

    send_to_master_buff[10] = 0xB3;                          //功能字        sonar-3
    send_to_master_buff[11] = *(sonar_data + 3)>>8;          //数据高8位
    send_to_master_buff[12] = *(sonar_data + 3)&0xFF;        //数据低8位

    send_to_master_buff[13] = 0xB4;                          //功能字        sonar-4
    send_to_master_buff[14] = *(sonar_data + 4)>>8;          //数据高8位
    send_to_master_buff[15] = *(sonar_data + 4)&0xFF;        //数据低8位

    send_to_master_buff[16] = 0xB5;                          //功能字        sonar-5
    send_to_master_buff[17] = *(sonar_data + 5)>>8;          //数据高8位
    send_to_master_buff[18] = *(sonar_data + 5)&0xFF;        //数据低8位

    send_to_master_buff[19] = 0xB6;                          //功能字        sonar-6
    send_to_master_buff[20] = *(sonar_data + 6)>>8;          //数据高8位
    send_to_master_buff[21] = *(sonar_data + 6)&0xFF;        //数据低8位

    send_to_master_buff[22] = 0xB7;                          //功能字        sonar-7
    send_to_master_buff[23] = *(sonar_data + 7)>>8;          //数据高8位
    send_to_master_buff[24] = *(sonar_data + 7)&0xFF;        //数据低8位

    send_to_master_buff[25] = 0xB8;                          //功能字        adc-0
    send_to_master_buff[26] = *(adc_data   + 0)>>8;          //数据高8位
    send_to_master_buff[27] = *(adc_data   + 0)&0xFF;        //数据低8位

    send_to_master_buff[28] = 0xB9;                          //功能字        adc-1
    send_to_master_buff[29] = *(adc_data   + 1)>>8;          //数据高8位
    send_to_master_buff[30] = *(adc_data   + 1)&0xFF;        //数据低8位

    send_to_master_buff[31] = 0xBA;                          //功能字        adc-2
    send_to_master_buff[32] = *(adc_data   + 2)>>8;          //数据高8位
    send_to_master_buff[33] = *(adc_data   + 2)&0xFF;        //数据低8位

    send_to_master_buff[34] = 0xBB;                          //功能字        adc-3
    send_to_master_buff[35] = *(adc_data   + 3)>>8;          //数据高8位
    send_to_master_buff[36] = *(adc_data   + 3)&0xFF;        //数据低8位

    send_to_master_buff[37] = 0xBC;                          //功能字        Thpos
    send_to_master_buff[38] = robot_style.yaw  >>8;          //数据高8位
    send_to_master_buff[39] = robot_style.yaw  &0xFF;        //数据低8位

    send_to_master_buff[40] = 0xEE;                          //帧尾
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      定时器4中断服务函数
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        GPIO_PIN_SET(A0);                           //A0引脚拉高
        //get_sensor_data();                          //获取传感器数据。
        process_data();                             //根据协议处理数据，并存入temp_buff中。
        uart_putbuff(UART_3, send_to_master_buff, LINE_LEN);  //通过串口3将数据发送出去。
//        enable_calc_icm = USART_ReceiveData(USART3);
        GPIO_PIN_RESET(A0);                         //A0引脚拉低
    }
}
