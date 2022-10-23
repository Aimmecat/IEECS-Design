#include "myheadfile.h"

int main(void)
{
    DisableGlobalIRQ();                     //��ֹ�ж�
    board_init();                           //��Ƶ��ʼ��

    if(!flash_check(FLASH_SECTION_15, FLASH_PAGE_0))
        flash_page_program(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
    else {
        flash_page_read(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
    }
    lcd_init();
    Robot_Communite_Init();                 //ͨѶ��ʼ��
    MCUC_Master_Init();                     //����ͨѶ��ʼ��
    Beep_Init();                            //��������ʼ��
    ALLPID_INIT();                          //PID��������ʼ��
    Motor_All_Init();                       //�����ʼ��
    Encoder_Master_Init();                  //��������ʼ��
    timer_pit_interrupt_ms(TIMER_1, 20);    //��ʱ��20ms���ڵ��õ�����ƺ���
    Key_Init();                             //������ʼ��

//    lcd_showstr(0, 0, "Init Success!");

    EnableGlobalIRQ(0);                     //�����ж�


//    Beep_Set_ms(100);
    while(1){
        Clear_Sip_Data(standard_io_info);
        Clear_Sip_Data(standard_sip_info);
        while(1){
            Menu();
            if(sip_receive_info && Start_Robot_Connection_Sync())
                break;
        }
//        Beep_Set_ms(100);
//        Beep_Set_ms(100);
//        Beep_Set_ms(100);
        while(1){
            Menu();
            if(sip_receive_info && Keep_Robot_Communite())
                break;
        }
//        Beep_Set_ms(100);
//        Beep_Set_ms(100);
    }
}

