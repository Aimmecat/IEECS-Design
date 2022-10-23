#include "myheadfile.h"

uint8 send_to_master_buff[LINE_LEN];                        //�ӻ���������������BUFF

//�ɼ��Ĳ������
int16 sonar_data[8];

//�ɼ���AD����
int16 adc_data[4];


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������Ƭ��ͨѶ��ʼ������
//  @param      void
//  @return     void
//  Sample usage:   MCUC_Slave_Init()
//-------------------------------------------------------------------------------------------------------------------
void MCUC_Slave_Init(void)
{
    gpio_init(A0, GPO, 0, GPIO_PIN_CONFIG);                 //ͬ�����ų�ʼ��
    uart_init(UART_3, 460800, UART3_TX_B10, UART3_RX_B11);  //����3��ʼ����������460800
    timer_pit_interrupt_ms(TIMER_4, 5);                     //��ʱ��4��ʼ��
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����������
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   �ڲ�ʹ��,�������
//-------------------------------------------------------------------------------------------------------------------
void get_sensor_data(void)
{
    //ʾ��
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
//  @brief      ����Э�鴦������
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   �ڲ�ʹ��,�������
//-------------------------------------------------------------------------------------------------------------------
void process_data(void)
{
    send_to_master_buff[0]  = 0xD8;                          //֡ͷ

    send_to_master_buff[1]  = 0xB0;                          //������        sonar-0
    send_to_master_buff[2]  = *(sonar_data + 0)>>8;          //���ݸ�8λ
    send_to_master_buff[3]  = *(sonar_data + 0)&0xFF;        //���ݵ�8λ

    send_to_master_buff[4]  = 0xB1;                          //������        sonar-1
    send_to_master_buff[5]  = *(sonar_data + 1)>>8;          //���ݸ�8λ
    send_to_master_buff[6]  = *(sonar_data + 1)&0xFF;        //���ݵ�8λ

    send_to_master_buff[7]  = 0xB2;                          //������        sonar-2
    send_to_master_buff[8]  = *(sonar_data + 2)>>8;          //���ݸ�8λ
    send_to_master_buff[9]  = *(sonar_data + 2)&0xFF;        //���ݵ�8λ

    send_to_master_buff[10] = 0xB3;                          //������        sonar-3
    send_to_master_buff[11] = *(sonar_data + 3)>>8;          //���ݸ�8λ
    send_to_master_buff[12] = *(sonar_data + 3)&0xFF;        //���ݵ�8λ

    send_to_master_buff[13] = 0xB4;                          //������        sonar-4
    send_to_master_buff[14] = *(sonar_data + 4)>>8;          //���ݸ�8λ
    send_to_master_buff[15] = *(sonar_data + 4)&0xFF;        //���ݵ�8λ

    send_to_master_buff[16] = 0xB5;                          //������        sonar-5
    send_to_master_buff[17] = *(sonar_data + 5)>>8;          //���ݸ�8λ
    send_to_master_buff[18] = *(sonar_data + 5)&0xFF;        //���ݵ�8λ

    send_to_master_buff[19] = 0xB6;                          //������        sonar-6
    send_to_master_buff[20] = *(sonar_data + 6)>>8;          //���ݸ�8λ
    send_to_master_buff[21] = *(sonar_data + 6)&0xFF;        //���ݵ�8λ

    send_to_master_buff[22] = 0xB7;                          //������        sonar-7
    send_to_master_buff[23] = *(sonar_data + 7)>>8;          //���ݸ�8λ
    send_to_master_buff[24] = *(sonar_data + 7)&0xFF;        //���ݵ�8λ

    send_to_master_buff[25] = 0xB8;                          //������        adc-0
    send_to_master_buff[26] = *(adc_data   + 0)>>8;          //���ݸ�8λ
    send_to_master_buff[27] = *(adc_data   + 0)&0xFF;        //���ݵ�8λ

    send_to_master_buff[28] = 0xB9;                          //������        adc-1
    send_to_master_buff[29] = *(adc_data   + 1)>>8;          //���ݸ�8λ
    send_to_master_buff[30] = *(adc_data   + 1)&0xFF;        //���ݵ�8λ

    send_to_master_buff[31] = 0xBA;                          //������        adc-2
    send_to_master_buff[32] = *(adc_data   + 2)>>8;          //���ݸ�8λ
    send_to_master_buff[33] = *(adc_data   + 2)&0xFF;        //���ݵ�8λ

    send_to_master_buff[34] = 0xBB;                          //������        adc-3
    send_to_master_buff[35] = *(adc_data   + 3)>>8;          //���ݸ�8λ
    send_to_master_buff[36] = *(adc_data   + 3)&0xFF;        //���ݵ�8λ

    send_to_master_buff[37] = 0xBC;                          //������        Thpos
    send_to_master_buff[38] = robot_style.yaw  >>8;          //���ݸ�8λ
    send_to_master_buff[39] = robot_style.yaw  &0xFF;        //���ݵ�8λ

    send_to_master_buff[40] = 0xEE;                          //֡β
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʱ��4�жϷ�����
//  @param      void
//  @return     void
//  @since      v1.0
//  Sample usage:   �ڲ�ʹ��,�������
//-------------------------------------------------------------------------------------------------------------------
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        GPIO_PIN_SET(A0);                           //A0��������
        //get_sensor_data();                          //��ȡ���������ݡ�
        process_data();                             //����Э�鴦�����ݣ�������temp_buff�С�
        uart_putbuff(UART_3, send_to_master_buff, LINE_LEN);  //ͨ������3�����ݷ��ͳ�ȥ��
//        enable_calc_icm = USART_ReceiveData(USART3);
        GPIO_PIN_RESET(A0);                         //A0��������
    }
}
