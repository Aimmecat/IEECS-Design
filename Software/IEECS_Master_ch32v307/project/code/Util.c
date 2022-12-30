/*
 * Util.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief              ����У��
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              data  sip_info
//  @return             check У���
//  Sample usage:       Calc_Check_Sum(sip_info)
//-------------------------------------------------------------------------------------------------------------------
uint16 Calc_Check_Sum(uint8* data){
    uint16 check = 0;
    int index = 3;
    int n = *(data + 2) - 2;
    while(n > 1){
        check += (((uint16)(*(data + index))) << 8) | *(data + index + 1);
        check &= 0xffff;
        n -= 2;
        index += 2;
    }
    if(n > 0)
        check ^= *(data + index);
    return check;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              �����ʼ��
//  @author             Ji Xiaoyu
//  @update             2021-8-25
//  @param              data  sip_info
//  @param              len   length
//  @return             none
//  Sample usage:       Clear_Sip_Data(sip_info, len)
//-------------------------------------------------------------------------------------------------------------------
void Clear_Sip_Data(uint8 *data, uint8 len){
    for(int index = 4; index < len; index++){
        if(index == 22 || index == 23 || index == 26 || index == 29 || index == 32 || index == 35 || index == 38 || index == 41 || index == 44)
            continue;
        *(data + index) = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              �������
//  @author             Ji Xiaoyu
//  @update             2021-8-31
//  @param              array  sip_info
//  @param              len    length
//  @return             none
//  Sample usage:       Clear_Array(array, len)
//-------------------------------------------------------------------------------------------------------------------
void Clear_Array(uint8 *array, uint8 len){
    for(int index = 0; index < len; index++ ){
        *(array + index) = 0;
    }
}

