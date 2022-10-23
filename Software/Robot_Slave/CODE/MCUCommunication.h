#ifndef _MCUCOMMUNICATION_H
#define _MCUCOMMUNICATION_H

//This is Slave
#define LINE_LEN 41

extern int16 sonar_data[8];
extern int16 adc_data[4];

void MCUC_Slave_Init(void);
void get_sensor_data(void);
void process_data(void);
void TIM4_IRQHandler(void) __attribute__((interrupt()));

#endif
