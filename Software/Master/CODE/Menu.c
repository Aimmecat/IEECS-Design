/*
 * Menu.c
 *
 *  Created on: Aug 30, 2021
 *      Author: Aimmecat
 */

#include "myheadfile.h"

uint8 pageindex = DEBUG_PAGE;
uint8 page_col,page_row;

//修改参数顺序前请修改对应参数宏定义
uint32 parameter[] = {50, 10, 50, 10};

void Menu_Init(void){
    lcd_init();
}


//菜单入口
void Menu(void){
    if(pageindex == HOME_PAGE)
        Menu_Home_Page();
    else if(pageindex == PARAMETER_PAGE)
        Menu_Parameter_Page();
    else if(pageindex == SONARS_PAGE)
        Menu_Sonars_Page();
    else if(pageindex == DEBUG_PAGE)
        Menu_Debug_Page();
    else if(pageindex == ADC_PAGE)
        Menu_Adc_Page();
    else if(pageindex == CONTROL_PAGE)
        Menu_Control_Page();
}

//主页
void Menu_Home_Page(void){

    lcd_showstr(16, PARAMETER_PAGE, "parameter" );
    lcd_showstr(16, SONARS_PAGE   , "sonars"    );
    lcd_showstr(16, DEBUG_PAGE    , "debug info");
    lcd_showstr(16, ADC_PAGE      , "adc"       );
    lcd_showstr(16, CONTROL_PAGE  , "control"   );
    lcd_showstr(8, 9, "row:");

    lcd_showuint8(40, 9, page_row);

    if(key_state == _KEY_ROTATION_LEFT){
        page_row -= page_row || 0 ? 1 : 0;
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ROTATION_RIGHT){
        page_row += page_row == HOME_PAGE_LEN - 1 ? 0 : 1;
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ENTER){
        pageindex = page_row;
        page_row = 0;
        page_col = 0;
        lcd_clear(WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Parameter_Page(void){
    static KEY_SETTING_STATE key_setting_state;

    lcd_showstr(16, 0, "read & write");
    lcd_showstr(0,  9, "row:");
    lcd_showstr(64, 9, "col:");

    lcd_showstr(8, 1, "L_P_I:");
    lcd_showstr(8, 2, "R_P_I:");

    lcd_showuint8(56, 1 , *( parameter  +  0 ));                     //左轮P
    lcd_showuint8(88, 1 , *( parameter  +  1 ));                     //左轮I
    lcd_showuint8(56, 2 , *( parameter  +  2 ));                     //右轮P
    lcd_showuint8(88, 2 , *( parameter  +  3 ));                     //右轮I

    lcd_showuint8(32, 9, page_row);
    lcd_showuint8(96, 9, page_col);


    if(key_state == _KEY_ROTATION_LEFT){
        if(key_setting_state == _CHOOSE_ROW){
            page_row -= page_row || 0 ? 1 : 0;
        }
        else if(key_setting_state == _CHOOSE_COL){
            page_col -= page_col == 0  ?  0 : 1;
        }
        else if(key_setting_state == _ADJUST_NUM){
            *(parameter + 2 * page_row + page_col) -= 1;
        }
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ROTATION_RIGHT){
        if(key_setting_state == _CHOOSE_ROW){
            page_row += page_row == PARAMTTER_PAGE_LEN ? 0 : 1;
        }
        else if(key_setting_state == _CHOOSE_COL){
            page_col += page_col == 1  ? 0 : 1;
        }
        else if(key_setting_state == _ADJUST_NUM){
            *(parameter + 2 * page_row + page_col) += 1;
        }
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ENTER){
        if(page_row != PARAMTTER_PAGE_LEN){
            if(key_setting_state == _CHOOSE_ROW){
                lcd_showstr(24, 8, "Adjust Col");
                key_setting_state = _CHOOSE_COL;
            }
            else if(key_setting_state == _CHOOSE_COL){
                lcd_showstr(24, 8, "Adjust Num");
                key_setting_state = _ADJUST_NUM;
            }
            else {
                lcd_showstr(24, 8, "Adjust Row");
                page_col = 0;
                flash_page_program(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
                key_setting_state = _CHOOSE_ROW;
            }
        }
        else{
            page_row = 0;
            pageindex = HOME_PAGE;
            lcd_clear(WHITE);
        }
        key_state = _KEY_NULL;
    }
}

void Menu_Sonars_Page(void){
    lcd_showstr(24, 0, "only read");

    lcd_showstr(8, 1, "sonar0:");
    lcd_showstr(8, 2, "sonar1:");
    lcd_showstr(8, 3, "sonar2:");
    lcd_showstr(8, 4, "sonar3:");
    lcd_showstr(8, 5, "sonar4:");
    lcd_showstr(8, 6, "sonar5:");
    lcd_showstr(8, 7, "sonar6:");
    lcd_showstr(8, 8, "sonar7:");

    lcd_showuint16(64, 1, *(sonar + 0));
    lcd_showuint16(64, 2, *(sonar + 1));
    lcd_showuint16(64, 3, *(sonar + 2));
    lcd_showuint16(64, 4, *(sonar + 3));
    lcd_showuint16(64, 5, *(sonar + 4));
    lcd_showuint16(64, 6, *(sonar + 5));
    lcd_showuint16(64, 7, *(sonar + 6));
    lcd_showuint16(64, 8, *(sonar + 7));

    lcd_showstr(8, 9, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        lcd_clear(WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Debug_Page(void){

    static bool reset_page = false;

    if(robot_connect_state == _CLOSE_CONNECT){
        if(reset_page){
            reset_page = false;
            lcd_clear(WHITE);
        }
        lcd_showstr(8,0,"wait to connect");
    }
    else if(robot_connect_state == _SYCN0_SUCCESS)
        lcd_showstr(8,1,"sync0 success");
    else if(robot_connect_state == _SYNC1_SUCCESS)
        lcd_showstr(8,2,"sync1 success");
    else if(robot_connect_state == _SYNC2_SUCCESS)
        lcd_showstr(8,3,"sync2 success");
    else if(robot_connect_state == _KEEP_CONNECT){
        lcd_showstr(8,4,"connecting...");
        reset_page = true;
    }

    if(!check_sum_error && robot_connect_state == _KEEP_CONNECT){
        lcd_showstr(8,5,"check no error");
    }
    else if(check_sum_error && robot_connect_state == _KEEP_CONNECT){
        lcd_showstr(8,5,"check error!!!");
    }

    lcd_showstr(8,6,"Vt:");
    lcd_showstr(8,7,"Vr:");
    lcd_showstr(8,8,"V :");

    lcd_showstr(8, 9, "press to exit");

    lcd_showint16(32, 6, Controlspeed.Vt);
    lcd_showint16(32, 7, Controlspeed.Vr);
    lcd_showfloat(32, 8, voltage / 25.5,2,2);

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        lcd_clear(WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Adc_Page(void){
    lcd_showstr(24, 0, "only read");

    lcd_showstr(16, 1, "ADC0:");
    lcd_showstr(16, 2, "ADC1:");
    lcd_showstr(16, 3, "ADC2:");
    lcd_showstr(16, 4, "ADC3:");


    lcd_showuint16(64, 1, *(input_adc + 0));
    lcd_showuint16(64, 2, *(input_adc + 1));
    lcd_showuint16(64, 3, *(input_adc + 2));
    lcd_showuint16(64, 4, *(input_adc + 3));

    lcd_showstr(8, 9, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        lcd_clear(WHITE);
        key_state = _KEY_NULL;
    }
}

int16 sum = 0;

void Menu_Control_Page(void){
    lcd_showstr(24, 0, "only read");

    lcd_showstr(16, 1, "Xpos:");
    lcd_showstr(16, 2, "Ypos:");
    lcd_showstr(16, 3, "Thpos:");
    lcd_showstr(16, 4, "Vt:");
    lcd_showstr(16, 5, "Vr:");
    lcd_showstr(16, 6, "V:  ");
    lcd_showstr(16, 7, "L: ");
    lcd_showstr(16, 8, "R: ");

    lcd_showint16(64, 1, robot_style.Xpos);
    lcd_showint16(64, 2, robot_style.Ypos);
    lcd_showint16(64, 3, robot_style.Thpos);
//    lcd_showint16(64, 4, Expspeed.Left_expspeed);
//    lcd_showint16(64, 5, Expspeed.Right_expspeed);
    lcd_showint16(64, 4, encoder_master_data[left_encoder]);
    lcd_showint16(64, 5, encoder_master_data[right_encoder]);
    lcd_showuint8(64, 6, voltage);
    lcd_showint16(64, 7, Duty.Left_pwmduty);
    lcd_showint16(64, 8, Duty.Right_pwmduty);

    lcd_showstr(8, 9, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        lcd_clear(WHITE);
        key_state = _KEY_NULL;
    }
}
