/*
 * Key.h
 *
 *  Created on: Aug 29, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_KEY_H_
#define CODE_KEY_H_

#define KEY_ENTER           C9
#define KEY_B_PORT          C8
#define KEY_A_PORT          C7

typedef enum{
    _KEY_NULL = 0,
    _KEY_ROTATION_LEFT,
    _KEY_ROTATION_RIGHT,
    _KEY_ENTER,
    _KEY_ROTATION_LEFT_PREPARE,
    _KEY_ROTATION_RIGHT_PREPARE,
}KEY_STATE;

void Key_Init(void);
void Key_Happen(void);

extern KEY_STATE key_state;

#endif /* CODE_KEY_H_ */
