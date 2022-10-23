/*
 * Menu.h
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_MENU_H_
#define CODE_MENU_H_

#define HOME_PAGE_LEN         5
#define PARAMTTER_PAGE_LEN    9

#define PARAMETER_PAGE  0
#define SONARS_PAGE     1
#define DEBUG_PAGE      2
#define ADC_PAGE        3
#define CONTROL_PAGE    4
#define HOME_PAGE       9

#define PARAMTTER_DATA_LEN    4

#define LEFT_PID_P      0
#define LEFT_PID_I      1
#define RIGHT_PID_P     2
#define RIGHT_PID_I     3

typedef enum{
    _CHOOSE_ROW,
    _CHOOSE_COL,
    _ADJUST_NUM,
}KEY_SETTING_STATE;


extern uint32 parameter[];

void Menu_Init(void);
void Menu(void);
void Menu_Home_Page(void);
void Menu_Parameter_Page(void);
void Menu_Sonars_Page(void);
void Menu_Debug_Page(void);
void Menu_Adc_Page(void);
void Menu_Control_Page(void);

#endif /* CODE_MENU_H_ */
