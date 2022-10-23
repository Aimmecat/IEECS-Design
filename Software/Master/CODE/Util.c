/*
 * Util.c
 *
 *  Created on: Aug 23, 2021
 *      Author: Aimmecat
 */

#include "myheadfile.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief              计算校验
//  @author             Ji Xiaoyu
//  @update             2021-8-23
//  @param              data  sip_info
//  @return             check 校验和
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
//  @brief              数组初始化
//  @author             Ji Xiaoyu
//  @update             2021-8-25
//  @param              data  sip_info
//  @return             none
//  Sample usage:       Clear_Sip_Data(sip_info)
//-------------------------------------------------------------------------------------------------------------------
void Clear_Sip_Data(uint8 *data){
    int len = (int)(sizeof(data) / sizeof(data[0]));
    for(int index = 4; index < len; index++){
        if(index == 23 || index == 26 || index == 29 || index == 32 || index == 35 || index == 38 || index == 41 || index == 44)
            continue;
        *(data + index) = 0;
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief              清空数组
//  @author             Ji Xiaoyu
//  @update             2021-8-31
//  @param              array  sip_info
//  @return             none
//  Sample usage:       Clear_Array(array)
//-------------------------------------------------------------------------------------------------------------------
void Clear_Array(uint8 *array){
    int len = (int)(sizeof(array) / sizeof(array[0]));
    for(int index = 0; index < len; index++ ){
        *(array + index) = 0;
    }
}
