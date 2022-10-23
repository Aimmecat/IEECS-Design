#ifndef _MCUCOMMUNICATION_H
#define _MCUCOMMUNICATION_H

//This is for Master
#define E_START                 0        //׼��״̬
#define E_OK                    1        //�ɹ�
#define E_FRAME_HEADER_ERROR    2        //֡ͷ����
#define E_FRAME_RTAIL_ERROR     3        //֡β����
#define LINE_LEN                41       //���ݳ���

extern int16 sonar[8];
extern int16 input_adc[4];

extern uint8 uart_flag;


void MCUC_Master_Init(void);
void Get_Slave_Data(uint8 data);
void Data_Analysis(uint8 *line);
void USART3_IRQHandler(void) __attribute__((interrupt()));
void EXTI0_IRQHandler(void) __attribute__((interrupt()));

#endif
