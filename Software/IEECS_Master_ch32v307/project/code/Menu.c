/*
 * Menu.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

uint8 pageindex = DEBUG_PAGE;
uint8 page_col,page_row;

//修改参数顺序前请修改对应参数宏定义
uint32 parameter[] = {50, 10, 50, 10};

void Menu_Init(void){
    ips200_init();
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

    ips200_show_string(16, PARAMETER_PAGE * BASE_LENGTH, "parameter" );
    ips200_show_string(16, SONARS_PAGE    * BASE_LENGTH, "sonar_datas"    );
    ips200_show_string(16, DEBUG_PAGE     * BASE_LENGTH, "debug info");
    ips200_show_string(16, ADC_PAGE       * BASE_LENGTH, "adc"       );
    ips200_show_string(16, CONTROL_PAGE   * BASE_LENGTH, "control"   );
    ips200_show_string(8, 9 * BASE_LENGTH, "row:");

    ips200_show_int(40, 9 * BASE_LENGTH, page_row, 3);

    if(key_state == _KEY_ROTATION_LEFT){
        page_row = page_row == 0 ? HOME_PAGE_LEN - 1 : page_row - 1;
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ROTATION_RIGHT){
        page_row = page_row == HOME_PAGE_LEN - 1 ? 0 : page_row + 1;
        key_state = _KEY_NULL;
    }
    else if(key_state == _KEY_ENTER){
        pageindex = page_row;
        page_row = 0;
        page_col = 0;
        ips200_clear(RGB565_WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Parameter_Page(void){
    static KEY_SETTING_STATE key_setting_state;

    ips200_show_string(16, 0 * BASE_LENGTH, "read & write");
    ips200_show_string(0,  9 * BASE_LENGTH, "row:");
    ips200_show_string(64, 9 * BASE_LENGTH, "col:");

    ips200_show_string(8, 1 * BASE_LENGTH, "L_P_I:");
    ips200_show_string(8, 2 * BASE_LENGTH, "R_P_I:");

    ips200_show_int(56, 1 * BASE_LENGTH , *( parameter  +  0 ), 3);                     //左轮P
    ips200_show_int(88, 1 * BASE_LENGTH , *( parameter  +  1 ), 3);                     //左轮I
    ips200_show_int(56, 2 * BASE_LENGTH , *( parameter  +  2 ), 3);                     //右轮P
    ips200_show_int(88, 2 * BASE_LENGTH, *( parameter  +  3 ), 3);                     //右轮I

    ips200_show_int(32, 9 * BASE_LENGTH, page_row, 3);
    ips200_show_int(96, 9 * BASE_LENGTH, page_col, 3);


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
                ips200_show_string(24, 8 * BASE_LENGTH, "Adjust Col");
                key_setting_state = _CHOOSE_COL;
            }
            else if(key_setting_state == _CHOOSE_COL){
                ips200_show_string(24, 8 * BASE_LENGTH, "Adjust Num");
                key_setting_state = _ADJUST_NUM;
            }
            else {
                ips200_show_string(24, 8 * BASE_LENGTH, "Adjust Row");
                page_col = 0;
//                flash_page_program(FLASH_SECTION_15, FLASH_PAGE_0, parameter, PARAMTTER_DATA_LEN);
                key_setting_state = _CHOOSE_ROW;
            }
        }
        else{
            page_row = 0;
            pageindex = HOME_PAGE;
            ips200_clear(RGB565_WHITE);
        }
        key_state = _KEY_NULL;
    }
}

void Menu_Sonars_Page(void){
    ips200_show_string(24, 0 * BASE_LENGTH, "only read");

    ips200_show_string(8, 1 * BASE_LENGTH, "sonar0:");
    ips200_show_string(8, 2 * BASE_LENGTH, "sonar1:");
    ips200_show_string(8, 3 * BASE_LENGTH, "sonar2:");
    ips200_show_string(8, 4 * BASE_LENGTH, "sonar3:");
    ips200_show_string(8, 5 * BASE_LENGTH, "sonar4:");
    ips200_show_string(8, 6 * BASE_LENGTH, "sonar5:");
    ips200_show_string(8, 7 * BASE_LENGTH, "sonar6:");
    ips200_show_string(8, 8 * BASE_LENGTH, "sonar7:");

    ips200_show_int(64, 1 * BASE_LENGTH, *(sonar_data + 0), 5);
    ips200_show_int(64, 2 * BASE_LENGTH, *(sonar_data + 1), 5);
    ips200_show_int(64, 3 * BASE_LENGTH, *(sonar_data + 2), 5);
    ips200_show_int(64, 4 * BASE_LENGTH, *(sonar_data + 3), 5);
    ips200_show_int(64, 5 * BASE_LENGTH, *(sonar_data + 4), 5);
    ips200_show_int(64, 6 * BASE_LENGTH, *(sonar_data + 5), 5);
    ips200_show_int(64, 7 * BASE_LENGTH, *(sonar_data + 6), 5);
    ips200_show_int(64, 8 * BASE_LENGTH, *(sonar_data + 7), 5);

    ips200_show_string(8, 9 * BASE_LENGTH, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        ips200_clear(RGB565_WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Debug_Page(void){

    static bool reset_page = false;

    if(robot_connect_state == _CLOSE_CONNECT){
        if(reset_page){
            reset_page = false;
            ips200_clear(RGB565_WHITE);
        }
        ips200_show_string(8,0 * BASE_LENGTH,"wait to connect");
    }
    else if(robot_connect_state == _SYCN0_SUCCESS)
        ips200_show_string(8,1 * BASE_LENGTH,"sync0 success");
    else if(robot_connect_state == _SYNC1_SUCCESS)
        ips200_show_string(8,2 * BASE_LENGTH,"sync1 success");
    else if(robot_connect_state == _SYNC2_SUCCESS)
        ips200_show_string(8,3 * BASE_LENGTH,"sync2 success");
    else if(robot_connect_state == _KEEP_CONNECT){
        ips200_show_string(8,4 * BASE_LENGTH,"connecting...");
        reset_page = true;
    }

    if(!check_sum_error && robot_connect_state == _KEEP_CONNECT){
        ips200_show_string(8,5 * BASE_LENGTH,"check no error");
    }
    else if(check_sum_error && robot_connect_state == _KEEP_CONNECT){
        ips200_show_string(8,5 * BASE_LENGTH,"check error!!!");
    }

    ips200_show_string(8,6 * BASE_LENGTH,"Vt:");
    ips200_show_string(8,7 * BASE_LENGTH,"Vr:");
    ips200_show_string(8,8 * BASE_LENGTH,"V :");

    ips200_show_string(8, 12 * BASE_LENGTH, "press to exit");

    ips200_show_int(64, 6 * BASE_LENGTH, Controlspeed.Vt, 5);
    ips200_show_int(64, 7 * BASE_LENGTH, Controlspeed.Vr, 5);
    ips200_show_float(64, 8 * BASE_LENGTH, voltage / 25.5,2,2);

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        ips200_clear(RGB565_WHITE);
        key_state = _KEY_NULL;
    }
}

void Menu_Adc_Page(void){
    ips200_show_string(24, 0 * BASE_LENGTH, "only read");

    ips200_show_string(16, 1 * BASE_LENGTH, "ADC0:");
    ips200_show_string(16, 2 * BASE_LENGTH, "ADC1:");
    ips200_show_string(16, 3 * BASE_LENGTH, "ADC2:");
    ips200_show_string(16, 4 * BASE_LENGTH, "ADC3:");


    ips200_show_int(64, 1 * BASE_LENGTH, *(input_adc + 0), 5);
    ips200_show_int(64, 2 * BASE_LENGTH, *(input_adc + 1), 5);
    ips200_show_int(64, 3 * BASE_LENGTH, *(input_adc + 2), 5);
    ips200_show_int(64, 4 * BASE_LENGTH, *(input_adc + 3), 5);

    ips200_show_string(8, 9 * BASE_LENGTH, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        ips200_clear(RGB565_WHITE);
        key_state = _KEY_NULL;
    }
}

int16 sum = 0;

void Menu_Control_Page(void){
    ips200_show_string(24, 0 * BASE_LENGTH, "only read");

    ips200_show_string(16, 1 * BASE_LENGTH, "Xpos:");
    ips200_show_string(16, 2 * BASE_LENGTH, "Ypos:");
    ips200_show_string(16, 3 * BASE_LENGTH, "Thpos:");
    ips200_show_string(16, 4 * BASE_LENGTH, "Vt:");
    ips200_show_string(16, 5 * BASE_LENGTH, "Vr:");
    ips200_show_string(16, 6 * BASE_LENGTH, "V:  ");
    ips200_show_string(16, 7 * BASE_LENGTH, "L: ");
    ips200_show_string(16, 8 * BASE_LENGTH, "R: ");

    ips200_show_int(64, 1 * BASE_LENGTH, robot_style.Xpos, 5);
    ips200_show_int(64, 2 * BASE_LENGTH, robot_style.Ypos, 5);
    ips200_show_int(64, 3 * BASE_LENGTH, robot_style.Thpos, 5);
    ips200_show_int(128, 4 * BASE_LENGTH, Expspeed.Left_expspeed, 5);
    ips200_show_int(128, 5 * BASE_LENGTH, Expspeed.Right_expspeed, 5);

    int16 left_encoder_num = Encoder_Left_Get();
    int16 right_encoder_num = Encoder_Right_Get();

    ips200_show_int(64, 4 * BASE_LENGTH, left_encoder_num, 5);
    ips200_show_int(64, 5 * BASE_LENGTH, right_encoder_num, 5);
    ips200_show_int(64, 6 * BASE_LENGTH, voltage, 3);
    ips200_show_int(64, 7 * BASE_LENGTH, Duty.Left_pwmduty, 5);
    ips200_show_int(64, 8 * BASE_LENGTH, Duty.Right_pwmduty, 5);

    ips200_show_string(8, 9 * BASE_LENGTH, "press to exit");

    if(key_state == _KEY_ENTER){
        pageindex = HOME_PAGE;
        ips200_clear(RGB565_WHITE);
        key_state = _KEY_NULL;
    }
}

