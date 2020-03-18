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

#define TEST_KEY  8  //PORTA

#define UP_KEY    24 //PORTE
#define DOWN_KEY  25 //PORTE
#define LEFT_KEY  26 //PORTE
#define RIGHT_KEY 27 //PORTE
#define USE_INTERRUPT Enable
#define KEY_DETECTED (uint8)((PTE->PDIR&0x00000F00)>>8)
#define WAIT_UNTIL_FINGER_RELEASED(func) systick_delay_ms(100);while(func==true)


void KEYs_Init(void);
char* Keyboard_GetChar(void);
bool GET_TestKey(void);
bool GET_UpKey(void);
bool GET_DownKey(void);
bool GET_LeftKey(void);
bool GET_RightKey(void);
uint8_t GET_Keyboard(void);
void key_board_Init(void);
extern char buf[10];
#endif



