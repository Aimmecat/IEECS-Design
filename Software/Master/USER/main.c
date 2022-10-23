#include "myheadfile.h"

int main(void)
{
    DisableGlobalIRQ();                     //禁止中断
    board_init();                           //主频初始化

    if(!flash_check(FLASH_SECTION_15, FLASH_PAGE_0))
        flash_page_program(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
    else {
        flash_page_read(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
    }
    lcd_init();
    Robot_Communite_Init();                 //通讯初始化
    MCUC_Master_Init();                     //主从通讯初始化
    Beep_Init();                            //蜂鸣器初始化
    ALLPID_INIT();                          //PID控制器初始化
    Motor_All_Init();                       //电机初始化
    Encoder_Master_Init();                  //编码器初始化
    timer_pit_interrupt_ms(TIMER_1, 20);    //定时器20ms周期调用电机控制函数
    Key_Init();                             //按键初始化

//    lcd_showstr(0, 0, "Init Success!");

    EnableGlobalIRQ(0);                     //允许中断


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

