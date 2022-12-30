/*
 * Robot_Communite.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef ROBOT_COMMUNITE_H_
#define ROBOT_COMMUNITE_H_

#define UART_ROBOT        UART_2
#define UART_ROBOT_BPS    115200
#define UART_ROBOT_TX     UART2_TX_D5
#define UART_ROBOT_RX     UART2_RX_D6
#define UART_ROBOT_RTS    D2

#define UART_OK                0
#define UART_HEAD_ERROR        1
#define UART_LEN_ERROR         2
#define UART_CLC_ERROR         3
#define UART_PROCESS           4

#define MAX_ERROR_SIP_TIMES    20

typedef enum{
    _RECEIVE_SIP_SUCCESS = 0,
    _RECEIVE_CHECKSUM_ERROR,
    _RECEIVING
}RECEIVE_STATE;

typedef enum{
    _UART_OK = 0,
    _UART_PROCESS,
    _UART_RECEIVING,
    _UART_WATING
}UART_STATE;

typedef enum{
    _SYCN0_SUCCESS = 0,
    _SYNC1_SUCCESS,
    _SYNC2_SUCCESS,
    _KEEP_CONNECT,
    _CLOSE_CONNECT
}ROBOT_CONNECT_STATE;

extern ROBOT_CONNECT_STATE robot_connect_state;

extern bool check_sum_error;

extern uint8* sip_receive_info;

extern uint8 sip_receive_error_times;

void Add_SIP_Info(uint8* stander_sip_info);
void Add_IO_Info(uint8* stander_io_info);
void Robot_Communite_Init(void);
void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

uint8* Add_Checksum(uint8* sip_info);

RECEIVE_STATE Receive_Sip(uint8 dat,uint8* sip_receive_array);

bool Start_Robot_Connection_Sync(void);
bool Keep_Robot_Communite(void);

#endif /* ROBOT_COMMUNITE_H_ */
