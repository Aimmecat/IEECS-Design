/*
 * Beep.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef BEEP_H_
#define BEEP_H_

#define BEEP_PIN    B9

void Beep_Init(void);
void Beep_Set_ms(int16 time);

#endif /* BEEP_H_ */
