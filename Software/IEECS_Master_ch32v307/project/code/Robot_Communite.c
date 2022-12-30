/*
 * Robot_Communite.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//��������״̬��־ ��ΪUART_OKʱ������������
uint8 uart_state = UART_OK;

//����״̬
ROBOT_CONNECT_STATE robot_connect_state = _CLOSE_CONNECT;

//У��ʹ����־
bool check_sum_error = true;

//����SIP��ָ��
uint8* sip_receive_info = NULL;

//����SIP���������
uint8 sip_receive_error_times = 0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ��ʼ��ͨѶ����
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             null
//  Sample usage:       Robot_Communite_Init()
//-------------------------------------------------------------------------------------------------------------------
void Robot_Communite_Init(void){
    uart_init(UART_ROBOT, UART_ROBOT_BPS, UART_ROBOT_TX, UART_ROBOT_RX);    //���ô����жϺ�,������,TX,RX
    uart_rx_interrupt(UART_ROBOT, ENABLE);                                  //ʹ�ܴ����ж�
    gpio_init(UART_ROBOT_RTS, GPI, 1, GPIO_PIN_CONFIG);                     //��ʼ��У������
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����У��
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              sip_info��ͨ������
//  @return             null
//  Sample usage:       Add_Checksum(sip_info)
//-------------------------------------------------------------------------------------------------------------------
uint8* Add_Checksum(uint8* sip_info){
    int len = sip_info[2] + 3;
    int16 checksum = Calc_Check_Sum(sip_info);
    sip_info[len - 2] = checksum >> 8;
    sip_info[len - 1] = checksum & 0xff;
    return sip_info;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����SIP������Ϣ
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              stander_sip_info��ͨ������
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
//  @brief              ����IO������Ϣ
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              stander_io_info��ͨ������
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
//  @brief              ����SIP��
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              dat���ֽ�����
//  @param              sip_receive_array���洢����
//  @return             bool �Ƿ�����굱ǰ��sip��
//  Sample usage:       Receive_Sip(dat)
//-------------------------------------------------------------------------------------------------------------------
RECEIVE_STATE Receive_Sip(uint8 dat,uint8* sip_receive_array){

    static uint8 cnt = 0;
    static uint8 start_receive_flag = -1;

    if(dat == FIRST_HEAD || (start_receive_flag == 0 && dat == SECOND_HEAD)){
        start_receive_flag++;
    }

    if(start_receive_flag != -1)
        sip_receive_array[cnt++] = dat;

    if(cnt > 2 && cnt == sip_receive_array[2] + 3){
        cnt = 0;
        start_receive_flag = -1;
        uint16 checksum = Calc_Check_Sum(sip_receive_array);
        //У��SIP��
        if( (checksum >> 8) == *(sip_receive_array + sip_receive_array[2] + 1) && (checksum & 0xff) == *(sip_receive_array + sip_receive_array[2] + 2) ){
            check_sum_error = false;
            sip_receive_error_times = 0;
            return _RECEIVE_SIP_SUCCESS;
        }else{
            sip_receive_error_times += 1;
            if(sip_receive_error_times > MAX_ERROR_SIP_TIMES){
                check_sum_error = true;
                return _RECEIVE_CHECKSUM_ERROR;
            }
            check_sum_error = false;
            return _RECEIVE_SIP_SUCCESS;
        }
    }
    return _RECEIVING;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              ���Pioneer����ͨ��
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             bool �Ƿ���ɽ���ͨ��
//  Sample usage:       Start_Robot_Connection_Sync()
//-------------------------------------------------------------------------------------------------------------------
bool Start_Robot_Connection_Sync(void){
    static CMD_SYNC sync = CMD_SYNC0;
    static bool start_pulse = false;
    if(sync != CMD_SYNC_READY && sip_receive_info[2] != 0){
        if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC2 && sync == CMD_SYNC2){
            uint8 sync2_array[] = {0xFA,0xFB,19,CMD_SYNC2,80,105,111,110,101,101,114,0,99,120,0,50,48,59,57,0,0,0};
            uart_write_buffer(UART_ROBOT, Add_Checksum(sync2_array), sync2_array[2] + 3);
            sync = CMD_SYNC_READY;
            start_pulse = true;
            robot_connect_state = _SYNC2_SUCCESS;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC1 && sync == CMD_SYNC1){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            sync = CMD_SYNC2;
            robot_connect_state = _SYNC1_SUCCESS;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == CMD_SYNC0 && sync == CMD_SYNC0){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            sync = CMD_SYNC1;
            robot_connect_state = _SYCN0_SUCCESS;
        }
    }
    if(start_pulse){
        if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_OPEN){
            ;
        }
        else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_PULSE){
            uart_write_buffer(UART_ROBOT, sip_receive_info, sip_receive_info[2] + 3);
            uart_write_buffer(UART_ROBOT, Add_Checksum(standard_sip_info), standard_sip_info[2] + 3);
            start_pulse = false;
            sync = CMD_SYNC0;
            robot_connect_state = _KEEP_CONNECT;
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����ͨ��
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             bool �Ƿ���ֹ
//  Sample usage:       Keep_Robot_Communite()
//-------------------------------------------------------------------------------------------------------------------
bool Keep_Robot_Communite(void){

    //�������ݰ�ʱ��ֹȫ���ж� ��ֹ���������
    interrupt_global_disable();

    if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_VEL){
        //��������ֱ���ٶ�
        if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGINT){
            Controlspeed.Vt = (((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5);
        }
        else if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGNINT){
            Controlspeed.Vt = -((((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5));
        }
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_RVEL){
        //�������õĽ��ٶ�
        if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGINT){
            Controlspeed.Vr = (((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5);
        }
        else if(*(sip_receive_info + ARG_TYPE_INDEX) == ARGNINT){
            Controlspeed.Vr = -((((int16)(*(sip_receive_info + 6))) << 8) | *(sip_receive_info + 5));
        }
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_DIGOUT){
        //�������õĵ�ѹ��Ϣ
        voltage = *(sip_receive_info + 5);
    }
    else if(*(sip_receive_info + ARCOS_CMD_INDEX) == ROBOT_CLOSE){
        //���ܵ�ֹͣ��Ϣ
        robot_connect_state = _CLOSE_CONNECT;
        Controlspeed.Vt = 0;
        Controlspeed.Vr = 0;
        sip_receive_info = NULL;

        //�������׼������ ��ȫ���ж�
        interrupt_global_enable();
        return true;
    }

    //�������׼������ ��ȫ���ж�
    sip_receive_info = NULL;
    interrupt_global_enable();

//    if(!gpio_get(UART_ROBOT_RTS)){
//        Add_SIP_Info(standard_sip_info);
//        uart_write_buffer(UART_ROBOT, Add_Checksum(standard_sip_info), SIP_LEN);
//        Add_IO_Info(standard_io_info);
//        uart_write_buffer(UART_ROBOT, Add_Checksum(standard_io_info), IO_LEN);
//    }
    return false;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief              �����жϷ�����
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              null
//  @return             null
//  Sample usage:       USART1_IRQHandler()
//-------------------------------------------------------------------------------------------------------------------
void USART2_IRQHandler(void)
{
    uint8 dat;
    //���ý��յ�ַ
    static uint8* store_sip_info_point = sip_receive_info_One;
    //���ؽ���״̬
    RECEIVE_STATE receive_state;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
        if(uart_state == UART_OK){
            dat = USART_ReceiveData(USART2);
            receive_state = Receive_Sip(dat,store_sip_info_point);
            //�����ҹ�У����
            if(receive_state == _RECEIVE_SIP_SUCCESS){
                //�Ѵ������ݵ�ָ�븳��ȫ�ַ��ʽ���sip����ָ��
                sip_receive_info = store_sip_info_point;
                //�л��汾�ش���ַ
                store_sip_info_point = (store_sip_info_point == sip_receive_info_One) ? sip_receive_info_Two : sip_receive_info_One;
            }
            //���յ�û��У�� ������½���
            else if(receive_state == _RECEIVE_CHECKSUM_ERROR){
                Clear_Array(store_sip_info_point, RECEIVE_MAXLEN);
            }
            else{
                ;//������
            }
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);     //������ڽ����жϱ�־λ
    }
}

