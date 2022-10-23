/*
 * Util.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_UTIL_H_
#define CODE_UTIL_H_

#define Max(num_1, num_2)           (((num_1) > (num_2)) ? (num_1) : (num_2))
#define Min(num_1, num_2)           (((num_1) > (num_2)) ? (num_2) : (num_1))
#define Range(input, min, max)      (Min(Max(input, min),max))
#define Abs(number)                 ((number) > 0 ? (number) : -(number))

uint16 Calc_Check_Sum(uint8* data);
void Clear_Sip_Data(uint8 *data);
void Clear_Array(uint8 *array);

#endif /* CODE_UTIL_H_ */
