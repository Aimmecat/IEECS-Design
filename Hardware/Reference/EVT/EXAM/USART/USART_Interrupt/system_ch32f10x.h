/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32f10x_it.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains the headers of the interrupt handlers.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/ 
#ifndef __SYSTEM_CH32F10x_H
#define __SYSTEM_CH32F10x_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int SystemCoreClock;          /* System Clock Frequency (Core Clock) */

/* CH32F10x_System_Exported_Functions */
extern void SystemInit( void );
extern void SystemCoreClockUpdate( void );

#ifdef __cplusplus
}
#endif

#endif /*__CH32F10x_SYSTEM_H */


