/*
 * Robot_Communite.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//连接状态
ROBOT_CONNECT_STATE robot_connect_state = _CLOSE_CONNECT;

//校验和错误标志
bool check_sum_error = true;

//解析SIP包指针
uint8 *sip_receive_info;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              初始化通讯串口
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             null
//  Sample usage:       Robot_Communite_Init()
//-------------------------------------------------------------------------------------------------------------------
void Robot_Communite_Init(void){
    uart_init(UART_ROBOT, UART_ROBOT_BPS, UART_ROBOT_TX, UART_ROBOT_RX);    //配置串口中断号,波特率,TX,RX
    uart_rx_interrupt(UART_ROBOT, ENABLE);                                  //使能串口中断
    gpio_init(UART_ROBOT_RTS, GPI, 1, GPIO_PIN_CONFIG);                     //初始化校验引脚
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              添加校验
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              sip_info：通信数组
//  @return             null
//  Sample usage:       Add_Checksum(sip_info)
//-------------------------------------------------------------------------------------------------------------------
void Add_Checksum(uint8* sip_info){
    int len = sip_info[2] + 3;
    int16 checksum = Calc_Check_Sum(sip_info);
    sip_info[len - 2] = checksum >> 8;
    sip_info[len - 1] = checksum & 0xff;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              添加SIP数组信息
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              stander_sip_info：通信数组
//  @return             null
//  Sample usage:       Add_SIP_Info(stander_sip_info)
//-------------------------------------------------------------------------------------------------------------------
void Add_SIP_Info(uint8* stander_sip_info){

    *(stander_sip_info +  4) = robot_style.Xpos & 0xff;
    *(stander_sip_info +  5) = robot_style.Xpos >> 8;

    *(stander_sip_info +  6) = robot_style.Ypos & 0xff;
    *(stander_sip_info +  7) = robot_style.Ypos >> 8;

    *(stander_sip_info +  8) = robot_style.Thpos & 0xff;
    *(stander_sip_info +  9) = robot_style.Thpos >> 8;

    *(stander_sip_info + 24) = *(sonar_data + 0) & 0xff;
    *(stander_sip_info + 25) = *(sonar_data + 0) >> 8;

    *(stander_sip_info + 27) = *(sonar_data + 1) & 0xff;
    *(stander_sip_info + 28) = *(sonar_data + 1) >> 8;

    *(stander_sip_info + 30) = *(sonar_data + 2) & 0xff;
    *(stander_sip_info + 31) = *(sonar_data + 2) >> 8;

    *(stander_sip_info + 33) = *(sonar_data + 3) & 0xff;
    *(stander_sip_info + 34) = *(sonar_data + 3) >> 8;

    *(stander_sip_info + 36) = *(sonar_data + 4) & 0xff;
    *(stander_sip_info + 37) = *(sonar_data + 4) >> 8;

    *(stander_sip_info + 39) = *(sonar_data + 5) & 0xff;
    *(stander_sip_info + 40) = *(sonar_data + 5) >> 8;

    *(stander_sip_info + 42) = *(sonar_data + 6) & 0xff;
    *(stander_sip_info + 43) = *(sonar_data + 6) >> 8;

    *(stander_sip_info + 45) = *(sonar_data + 7) & 0xff;
    *(stander_sip_info + 46) = *(sonar_data + 7) >> 8;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              添加IO数组信息
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              stander_io_info：通信数组
//  @return             null
//  Sample usage:       Add_IO_Info(stander_io_info)
//-------------------------------------------------------------------------------------------------------------------
void Add_IO_Info(uint8* stander_io_info){

    *(standard_io_info + 21) = *(input_adc + 0) & 0xff;
    *(standard_io_info + 22) = *(input_adc + 0) >> 8;

    *(standard_io_info + 23) = *(input_adc + 1) & 0xff;
    *(standard_io_info + 24) = *(input_adc + 1) >> 8;

    *(standard_io_info + 25) = *(input_adc + 2) & 0xff;
    *(standard_io_info + 26) = *(input_adc + 2) >> 8;

    *(standard_io_info + 27) = *(input_adc + 3) & 0xff;
    *(standard_io_info + 28) = *(input_adc + 3) >> 8;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              接受SIP包
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              dat：字节数据
//  @param              sip_receive_array：存储数组
//  @return             bool 是否接受完当前的sip包
//  Sample usage:       Receive_Sip(dat)
//-------------------------------------------------------------------------------------------------------------------
bool Receive_Sip(uint8 dat,uint8* sip_receive_array){

    static uint8 cnt = 0;
    static uint8 start_receive_flag = -1;

    if(cnt > RECEIVE_MAXLEN - 1){
        cnt = 0;
        start_receive_flag = -1;
        return false;
    }

    if(dat == FIRST_HEAD || (start_receive_flag == 0 && dat == SECOND_HEAD)){
        start_receive_flag++;
    }

    if(start_receive_flag != -1)
        sip_receive_array[cnt++] = dat;

    if(cnt > 2 && cnt == sip_receive_array[2] + 3){
        cnt = 0;
        start_receive_flag = -1;
        uint16 checksum = Calc_Check_Sum(sip_receive_array);
        //校验SIP包
        if( (checksum >> 8) == *(sip_receive_array + sip_receive_array[2] + 1) && (checksum & 0xff) == *(sip_receive_array + sip_receive_array[2] + 2) ){
            check_sum_error = false;
            return true;
        }
        else{
            check_sum_error = true;
            return false;
        }
    }
    return false;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              点击Pioneer后建立通信
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             bool 是否完成建立通信
//  Sample usage:       Start_Robot_Connection_Sync()
//-------------------------------------------------------------------------------------------------------------------
bool Start_Robot_Connection_Sync(void){
    static CMD_SYNC sync = CMD_SYNC0;
    static bool start_pulse = false;
    if(sync != CMD_SYNC_READY && sip_receive_info[2] != 0){
        if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC0 && sync == CMD_SYNC0){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            sync = CMD_SYNC1;
            robot_connect_state = _SYCN0_SUCCESS;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC1 && sync == CMD_SYNC1){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            sync = CMD_SYNC2;
            robot_connect_state = _SYNC1_SUCCESS;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC2 && sync == CMD_SYNC2){
            uint8 sync2_array[22] = {0xFA,0xFB,19,CMD_SYNC2,80,105,111,110,101,101,114,0,99,120,0,50,48,59,57,0,0,0};
            Add_Checksum(sync2_array);
            uart_write_buffer(UART_ROBOT, sync2_array, sync2_array[2] + 3);
            sync = CMD_SYNC_READY;
            start_pulse = true;
            robot_connect_state = _SYNC2_SUCCESS;
        }
    }
    if(start_pulse){
        if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_OPEN){
            ;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_PULSE){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            Add_Checksum(standard_sip_info);
            uart_write_buffer(UART_ROBOT, standard_sip_info, standard_sip_info[2] + 3);
            start_pulse = false;
            sync = CMD_SYNC0;
            robot_connect_state = _KEEP_CONNECT;
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              保持通信
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             bool 是否终止
//  Sample usage:       Keep_Robot_Communite()
//-------------------------------------------------------------------------------------------------------------------
bool Keep_Robot_Communite(void){

    //解析数据包时静止全局中断 防止误接受数据
    interrupt_disable(USART2_IRQn);

    if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_VEL){
        //接受设置直线速度
        int Vt;
        if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGINT){
            Vt = (((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5);
        }
        else if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGNINT){
            Vt = -((((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5));
        }
        if(Abs(Vt) < 500)
            Controlspeed.Vt = Vt;
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_RVEL){
        //接受设置的角速度
        int Vr;
        if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGINT){
            Vr = (((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5);
        }
        else if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGNINT){
            Vr = -((((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5));
        }
        if(Abs(Vr) < 29)
            Controlspeed.Vr = Vr;
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_DIGOUT){
        //接受设置的电压信息
        int v;
        v = *(sip_receive_info + 5);
        if(v <= 255)
            voltage = v;
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_CLOSE){
        //接受到停止信息
        robot_connect_state = _CLOSE_CONNECT;
        Motor_Set_Speed(0, 0);
        sip_receive_info = NULL;
//        Clear_Array(sip_receive_info, RECEIVE_MAXLEN);

        //解析完毕准备返回 打开全局中断
        interrupt_enable(USART2_IRQn);
        return true;
    }

    //解析完毕准备返回 打开全局中断
//    Clear_Array(sip_receive_info, RECEIVE_MAXLEN);
    sip_receive_info = NULL;
    interrupt_enable(USART2_IRQn);

    return false;
}

void Send_Info(void){
    if(!gpio_get(UART_ROBOT_RTS)){
        Add_SIP_Info(standard_sip_info);
        Add_Checksum(standard_sip_info);
        uart_write_buffer(UART_ROBOT, standard_sip_info, SIP_LEN);
        Add_IO_Info(standard_io_info);
        Add_Checksum(standard_io_info);
        uart_write_buffer(UART_ROBOT, standard_io_info, IO_LEN);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              串口中断服务函数
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             null
//  Sample usage:       USART1_IRQHandler()
//-------------------------------------------------------------------------------------------------------------------
void USART2_IRQHandler(void)
{
    uint8 dat;
    //设置接收地址
    static uint8 *store_sip_info_point = sip_receive_info_One;
    //返回接受状态
    bool receive_state;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
        dat = USART_ReceiveData(USART2);
        receive_state = Receive_Sip(dat,store_sip_info_point);
        //接收且过校验了
        if(receive_state){
            //把带有数据的指针赋给全局访问接收sip包的指针
            sip_receive_info = store_sip_info_point;
        }
        else{
            ;//接受中或没通过校验
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);     //清除串口接收中断标志位
    }
}


