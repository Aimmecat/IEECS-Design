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
    pit_init_ms(TIM2_PIT, 20);              //��ʱ��20ms���ڵ��õ�����ƺ���
    Beep_Init();                            //��������ʼ��
//    pit_init_ms(TIM3_PIT, 20);              //��ʱ��20ms���ڲɼ������ADC,DAC����
    Key_Init();                             //������ʼ��
    Dac_Init();                             //DAC�����ʼ��
    Adc_Init();                             //ADC�����ʼ��


    Clear_Sip_Data(standard_io_info, IO_LEN);   //�������
    Clear_Sip_Data(standard_sip_info, SIP_LEN); //�������

    interrupt_global_enable();              //���ж������

    while(1)
    {
        while(1){
            Menu();
            if(sip_receive_info && Start_Robot_Connection_Sync())
                break;
            Sonar_Adc_Get();
        }
        Beep_Set_ms(50);
        while(1){
            Menu();
            if(!gpio_get(UART_ROBOT_RTS)){
                Add_SIP_Info(standard_sip_info);
                uart_write_buffer(UART_ROBOT, Add_Checksum(standard_sip_info), SIP_LEN);
                Add_IO_Info(standard_io_info);
                uart_write_buffer(UART_ROBOT, Add_Checksum(standard_io_info), IO_LEN);
            }
            if(sip_receive_info && Keep_Robot_Communite())
                break;
            Sonar_Adc_Get();
        }
        Beep_Set_ms(100);
        system_delay_ms(200);
        Beep_Set_ms(100);
    }
}



//        gpio_set(MOTOR_L_DIR, 1);
//        gpio_set(MOTOR_R_DIR, 1);
//        pwm_set_duty(MOTOR_L_PWM, 20000 );
//        pwm_set_duty(MOTOR_R_PWM, 20000 );
//        system_delay_ms(10);



