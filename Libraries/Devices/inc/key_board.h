/*--------------------------------------------------------------------------
* @file         key_board.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for key board.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "headfiles.h"
#ifndef _KEY_H
#define _KEY_H

#define TEST_KEY 8
#define USE_INTERRUPT Enable
#define KEY_DETECTED (uint8)((PTE->PDIR&0x00000F00)>>8)

void KEYs_Init(void);
char* Keyboard_GetChar(void);
uint8 GET_TestKey(void);
uint8 GET_Keyboard(void);
void key_board_Init(void);
extern char buf[10];
#endif



