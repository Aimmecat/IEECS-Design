#include "headfile.h"

bool switch_mode = true;

int main(void)
{
    interrupt_global_disable();             //关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          //务必保留，设置系统时钟。
    debug_init();                           //务必保留，本函数用于初始化MPU 时钟 调试串口

    ips200_init();                          //初始化屏幕
    Robot_Communite_Init();                 //上位机通讯初始化
    Encoder_Master_Init();                  //编码器初始化
    ALLPID_INIT();                          //PID控制器初始化
    Motor_All_Init();                       //电机初始化
    pit_init_ms(TIM1_PIT, 5);               //定时器5ms周期调用电机控制函数
    Beep_Init();                            //蜂鸣器初始化
//    pit_init_ms(TIM2_PIT, 5);              //定时器20ms周期采集并输出ADC,DAC数据
    Key_Init();                             //按键初始化
    Dac_Init();                             //DAC输出初始化
    Adc_Init();                             //ADC输入初始化

    interrupt_global_enable();              //总中断最后开启

    while(1)
    {
        Clear_Sip_Data(standard_io_info, IO_LEN);   //清空数据
        Clear_Sip_Data(standard_sip_info, SIP_LEN); //清空数据
        while(1){
            Menu();
            if(sip_receive_info && Start_Robot_Connection_Sync())
                break;
        }
        Beep_Set_ms(50);
        while(1){
            Menu();
            Send_Info();
            if(sip_receive_info && Keep_Robot_Communite())
                break;
            Sonar_Adc_Get();
        }
        Beep_Set_ms(100);
        system_delay_ms(200);
        Beep_Set_ms(100);
    }
}


