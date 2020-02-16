/*--------------------------------------------------------------------------
* @file         SystickDelay.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for delay.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif

#include "MK60D10.h"
#include "common.h"
#ifndef _MK60_systick_h
#define _MK60_systick_h

void    systick_delay(uint32 time);
void    systick_delay_ms(uint32 ms);
void    systick_timing(uint32 time);
uint32  systick_getval(void);


#endif

#ifdef __cplusplus
}
#endif
