/*--------------------------------------------------------------------------
* @file         LCD1602.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for LCD1602.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "LCD1602.h"
#include "headfiles.h"
#ifndef _LCD1602_H
#define _LCD1602_H

#define LCD_RS(x) ((x==0)?(PTC->PDOR&=~(uint32)(1<<19)):(PTC->PDOR|=(uint32)(1<<19)))
#define LCD_RW(x) ((x==0)?(PTC->PDOR&=~(uint32)(1<<15)):(PTC->PDOR|=(uint32)(1<<15)))
#define LCD_EN(x) ((x==0)?(PTC->PDOR&=~(uint32)(1<<13)):(PTC->PDOR|=(uint32)(1<<13)))


void LCD1602_Init(void);
void LCD1602_CleanScreen(void);
void LCD1602_GPIO_Configuration(void);
void LCD1602_WriteDat(uint8 data);
void LCD1602_WriteCmd(uint8 cmd);
uint8 LCD1602_CheckBusy(void);
void LCD1602_Str(uint8 x,uint8 y,char *str);
void LCD1602_Char(uint8 x,uint8 y, char letter);
void LCD1602_DefChar(uint8 char_index,const uint8* data);
void LCD_Printf(const char* format,...);
void LCD_Print_BIN(uint8 x,uint8 y, unsigned int num);
#endif
  
  
