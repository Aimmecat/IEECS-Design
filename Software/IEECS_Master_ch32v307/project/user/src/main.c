#include "headfile.h"

bool switch_mode = true;

int main(void)
{
    interrupt_global_disable();             //�ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          //��ر���������ϵͳʱ�ӡ�
    debug_init();                           //��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    ips200_init();                          //��ʼ����Ļ
    Robot_Communite_Init();                 //��λ��ͨѶ��ʼ��
    Encoder_Master_Init();                  //��������ʼ��
    ALLPID_INIT();                          //PID��������ʼ��
    Motor_All_Init();                       //�����ʼ��
    pit_init_ms(TIM1_PIT, 5);               //��ʱ��5ms���ڵ��õ�����ƺ���
    Beep_Init();                            //��������ʼ��
//    pit_init_ms(TIM2_PIT, 5);              //��ʱ��20ms���ڲɼ������ADC,DAC����
    Key_Init();                             //������ʼ��
    Dac_Init();                             //DAC�����ʼ��
    Adc_Init();                             //ADC�����ʼ��

    interrupt_global_enable();              //���ж������

    while(1)
    {
        Clear_Sip_Data(standard_io_info, IO_LEN);   //�������
        Clear_Sip_Data(standard_sip_info, SIP_LEN); //�������
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


