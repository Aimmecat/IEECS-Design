#include <myheadfile.h>

//�������ڽ������ݵ�BUFF
uint8   receive_slave_buff[LINE_LEN];

//�ɼ����
int16 sonar[8];

//�ɼ�AD
int16 input_adc[4];

uint8 uart_flag;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����ͨѶ��ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       MCUC_Master_Init();
//-------------------------------------------------------------------------------------------------------------------
void MCUC_Master_Init(void){

    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //����3��ʼ����������460800
    uart_rx_irq(UART_3, ENABLE);                            //Ĭ����ռ���ȼ�0 �����ȼ�0��
    nvic_init((IRQn_Type)(53 + UART_3), 0, 0, ENABLE);      //������3����ռ���ȼ�����Ϊ��ߣ������ȼ�����Ϊ��ߡ�
    gpio_interrupt_init(A0, RISING, GPIO_INT_CONFIG);       //A0��ʼ��ΪGPIO �����ش���
    nvic_init(EXTI0_IRQn, 1, 1, ENABLE);                    //EXTI0���ȼ����ã���ռ���ȼ�1�������ȼ�1
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ��ôӻ�����
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              data     ����
//  @return             void
//  Sample usage:       �ڲ�ʹ��,�������
//-------------------------------------------------------------------------------------------------------------------
void Get_Slave_Data(uint8 data){

    static uint8 uart_num = 0;
    receive_slave_buff[uart_num++] = data;

    if(1 == uart_num){
        if(0xD8 != receive_slave_buff[0]){                         //���յ��ĵ�һ���ַ���Ϊ0xD8��֡ͷ����
            uart_num = 0;
            uart_flag = E_FRAME_HEADER_ERROR;
        }
    }
    if(LINE_LEN == uart_num){
        uart_flag = E_OK;                                 //���յ����һ���ֽ�Ϊ0xEE
        if(0xEE == receive_slave_buff[LINE_LEN - 1]){
            uart_flag = E_OK;
        }
        else{                                             //���յ����һ���ֽڲ���0xEE��֡β����
            uart_flag = E_FRAME_RTAIL_ERROR;
        }
        uart_num = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����Э���������
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              line        slave_buff
//  @return             void
//  Sample usage:       �ڲ�ʹ��,�������
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
//  @brief              ����3�жϷ�����
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       �ڲ�ʹ��,�������
//-------------------------------------------------------------------------------------------------------------------
void USART3_IRQHandler(void){

    uint8 dat;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     //������ڽ����жϱ�־λ
        dat = USART_ReceiveData(USART3);                    //��ȡ��������
        Get_Slave_Data(dat);                                //��ÿһ���ֽڵĴ������ݴ���temp_buff�С�
        uart_putchar(UART_3, roll_flag);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              �ⲿ�ж�0������
//  @author             Ji Xiaoyu
//  @update             2021-5-19
//  @param              None
//  @return             void
//  Sample usage:       �ڲ�ʹ��,�������
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

