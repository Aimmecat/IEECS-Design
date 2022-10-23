/*
 * Data.h
 *
 *  Created on: Aug 23, 2021
 *      Author: Aimmecat
 */

#ifndef CODE_DATA_H_
#define CODE_DATA_H_

#define FIRST_HEAD  0XFA
#define SECOND_HEAD 0XFB

#define STOP_TYPE   0X32
#define MOVE_TYPE   0X33
#define IO_TYPE     0XF0

#define ARCOS_CMD_INDEX 3
#define ARG_TYPE_INDEX  4

#define RECEIVE_MAXLEN      20

typedef enum{
    CMD_SYNC0,
    CMD_SYNC1,
    CMD_SYNC2,
    CMD_SYNC_READY
}CMD_SYNC;

typedef enum{
    ARGINT  = 0x3B,
    ARGNINT = 0X1B,
    ARGSTR  = 0X2B
}ARG_TYPE;

typedef enum{
    ROBOT_PULSE                 =   0,
    ROBOT_OPEN                  =   1,
    ROBOT_CLOSE                 =   2,
    ROBOT_POLLING               =   3,
    ROBOT_ENABLE                =   4,
    ROBOT_SETA                  =   5,
    ROBOT_SETV                  =   6,
    ROBOT_SETO                  =   7,
    ROBOT_MOVE                  =   8,
    ROBOT_ROTATE                =   9,
    ROBOT_SETRV                 =  10,
    ROBOT_VEL                   =  11,
    ROBOT_HEAD                  =  12,
    ROBOT_DHEAD                 =  13,
    ROBOT_SAY                   =  15,
    ROBOT_JOYREQUEST            =  17,
    ROBOT_CONFIG                =  18,
    ROBOT_ENCODER               =  19,
    ROBOT_RVEL                  =  21,
    ROBOT_DCHEAD                =  22,
    ROBOT_SETRA                 =  23,
    ROBOT_SONAR                 =  28,
    ROBOT_STOP                  =  29,
    ROBOT_DIGOUT                =  30,
    ROBOT_VEL2                  =  32,
    ROBOT_GRIPPER               =  33,
    ROBOT_ADSEL                 =  35,
    ROBOT_GRIPPERVAL            =  36,
    ROBOT_GRIPREQUEST           =  37,
    ROBOT_IOREQUEST             =  40,
    ROBOT_TTY2                  =  42,
    ROBOT_GETAUX                =  43,
    ROBOT_BUMPSTALL             =  44,
    ROBOT_TCM2                  =  45,
    ROBOT_JOYDRIVE              =  47,
    ROBOT_SONARCYCLE            =  48,
    ROBOT_HOSTBAUD              =  50,
    ROBOT_AUX1BAUD              =  51,
    ROBOT_AUX2BAUD              =  52,
    ROBOT_AUX3BAUD              =  53,
    ROBOT_E_STOP                =  55,
    ROBOT_M_STALL               =  56,
    ROBOT_GYROREQUEST           =  58,
    ROBOT_LCDWRITE              =  59,
    ROBOT_TTY4                  =  60,
    ROBOT_GETAUX3               =  61,
    ROBOT_TTY3                  =  66,
    ROBOT_GETAUX2               =  67,
    ROBOT_CHARGE                =  68,
    ROBOT_RESET                 = 254,
    ROBOT_MAINTENANCE           = 255,
} ARCOS_CMD;

extern uint8 sip_receive_info_One[RECEIVE_MAXLEN];
extern uint8 sip_receive_info_Two[RECEIVE_MAXLEN];
extern uint8 standard_sip_info[];
extern uint8 standard_io_info[];

extern uint8 voltage;

#endif /* CODE_DATA_H_ */
