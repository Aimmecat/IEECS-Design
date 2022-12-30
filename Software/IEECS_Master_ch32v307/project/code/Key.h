/*
 * Key.h
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#ifndef KEY_H_
#define KEY_H_

#define KEY_ENTER           E12
#define KEY_A_PORT          E13
#define KEY_B_PORT          E14

typedef enum{
    _KEY_NULL = 0,
    _KEY_ROTATION_LEFT,
    _KEY_ROTATION_RIGHT,
    _KEY_ENTER,
}KEY_STATE;

void Key_Init(void);

extern KEY_STATE key_state;

#endif /* KEY_H_ */
