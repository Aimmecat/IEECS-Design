/*
 * Util.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef UTIL_H_
#define UTIL_H_

#define Max(num_1, num_2)           (((num_1) > (num_2)) ? (num_1) : (num_2))
#define Min(num_1, num_2)           (((num_1) > (num_2)) ? (num_2) : (num_1))
#define Range(input, min, max)      (Min(Max(input, min),max))
#define Abs(number)                 ((number) > 0 ? (number) : -(number))

uint16 Calc_Check_Sum(uint8* data);
void Clear_Sip_Data(uint8 *data, uint8 len);
void Clear_Array(uint8 *array, uint8 len);
void Copy_Array(uint8 *source, uint8 *target, int length);

#endif /* UTIL_H_ */
