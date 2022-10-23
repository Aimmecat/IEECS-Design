#include <myheadfile.h>

//主机用于接收数据的BUFF
uint8   receive_slave_buff[LINE_LEN];

//采集测距
int16 sonar[8];

//采集AD
int16 input_adc[4];

uint8 uart_flag;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              主机通讯初始化
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       MCUC_Master_Init();
//-------------------------------------------------------------------------------------------------------------------
void MCUC_Master_Init(void){

    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //串口3初始化，波特率460800
    uart_rx_irq(UART_3, ENABLE);                            //默认抢占优先级0 次优先级0。
    nvic_init((IRQn_Type)(53 + UART_3), 0, 0, ENABLE);      //将串口3的抢占优先级设置为最高，次优先级设置为最高。
    gpio_interrupt_init(A0, RISING, GPIO_INT_CONFIG);       //A0初始化为GPIO 上升沿触发
    nvic_init(EXTI0_IRQn, 1, 1, ENABLE);                    //EXTI0优先级配置，抢占优先级1，次优先级1
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              获得从机数据
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              data     数据
//  @return             void
//  Sample usage:       内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void Get_Slave_Data(uint8 data){

    static uint8 uart_num = 0;
    receive_slave_buff[uart_num++] = data;

    if(1 == uart_num){
        if(0xD8 != receive_slave_buff[0]){                         //接收到的第一个字符不为0xD8，帧头错误
            uart_num = 0;
            uart_flag = E_FRAME_HEADER_ERROR;
        }
    }
    if(LINE_LEN == uart_num){
        uart_flag = E_OK;                                 //接收到最后一个字节为0xEE
        if(0xEE == receive_slave_buff[LINE_LEN - 1]){
            uart_flag = E_OK;
        }
        else{                                             //接收到最后一个字节不是0xEE，帧尾错误
            uart_flag = E_FRAME_RTAIL_ERROR;
        }
        uart_num = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              根据协议解析数据
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              line        slave_buff
//  @return             void
//  Sample usage:       内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void Data_Analysis(uint8 *line){

    if(line[1] == 0xB0)      sonar[0]           = ((int16)line[2]  << 8) | line[3] ;

    if(line[4] == 0xB1)      sonar[1]           = ((int16)line[5]  << 8) | line[6] ;

    if(line[7] == 0xB2)      sonar[2]           = ((int16)line[8]  << 8) | line[9] ;

    if(line[10] == 0xB3)     sonar[3]           = ((int16)line[11] << 8) | line[12];

    if(line[13] == 0xB4)     sonar[4]           = ((int16)line[14] << 8) | line[15];

    if(line[16] == 0xB5)     sonar[5]           = ((int16)line[17] << 8) | line[18];

    if(line[19] == 0xB6)     sonar[6]           = ((int16)line[20] << 8) | line[21];

    if(line[22] == 0xB7)     sonar[7]           = ((int16)line[23] << 8) | line[24];

    if(line[25] == 0xB8)     input_adc[0]       = ((int16)line[26] << 8) | line[27];

    if(line[28] == 0xB9)     input_adc[1]       = ((int16)line[29] << 8) | line[30];

    if(line[31] == 0xBA)     input_adc[2]       = ((int16)line[32] << 8) | line[33];

    if(line[34] == 0xBB)     input_adc[3]       = ((int16)line[35] << 8) | line[36];

    //if(line[37] == 0xBC)     robot_style.Thpos  = ((int16)line[38] << 8) | line[39];

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              串口3中断服务函数
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void USART3_IRQHandler(void){

    uint8 dat;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     //清除串口接收中断标志位
        dat = USART_ReceiveData(USART3);                    //获取串口数据
        Get_Slave_Data(dat);                                //将每一个字节的串口数据存入temp_buff中。
        uart_putchar(UART_3, roll_flag);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              外部中断0服务函数
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       内部使用,无需关心
//-------------------------------------------------------------------------------------------------------------------
void EXTI0_IRQHandler(void){

    if(SET == EXTI_GetITStatus(EXTI_Line0)){
        EXTI_ClearITPendingBit(EXTI_Line0);
        if(uart_flag == E_OK){
            uart_flag = E_START;
            Data_Analysis(receive_slave_buff);
        }
    }
}

