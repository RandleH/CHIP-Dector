/*--------------------------------------------------------------------------
* @file         LCD1602.c
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
#include "stdarg.h"
#include "stdio.h"
#ifdef __cplusplus
extern "C"{
#endif
char sprint_buf[32];

const uint8 CHIP_Edge[][8]={
  {0x00,0x00,0x00,0x1f,0x01,0x01,0x01,0x01},//   `|     Right Up Corner
  {0x01,0x01,0x01,0x01,0x0f,0x00,0x00,0x00},//   _|     Right Down Corner
  {0x04,0x04,0x04,0x1f,0x00,0x00,0x00,0x00},//   `      Up Line(Good Pin)
  {0x00,0x00,0x00,0x00,0x1f,0x04,0x04,0x04},//   _      Down Line(Good Pin)
  {0x00,0x00,0x00,0x1f,0x10,0x10,0x1c,0x04},//   |`     Left Up Corner
  {0x04,0x1c,0x10,0x10,0x1f,0x00,0x00,0x00},//   |_     Left Down Corner
  {0x04,0x15,0x0e,0x1f,0x0a,0x11,0x00,0x00},//          Error Up Pin
  {0x00,0x00,0x11,0x0a,0x1f,0x0e,0x15,0x04},//          Error Down Pin
};

void LCD1602_Init(void)
{
  LCD1602_GPIO_Configuration();
  systick_delay_ms(15); 
  LCD1602_WriteCmd(0x38);  
  systick_delay_ms(15);
  LCD1602_WriteCmd(0x38);  
  systick_delay_ms(5);
  LCD1602_WriteCmd(0x38);  
  systick_delay_ms(5);
  LCD1602_WriteCmd(0x38);  
  systick_delay_ms(5);
  LCD1602_WriteCmd(0x08);  
  LCD1602_WriteCmd(0x06);  
  LCD1602_WriteCmd(0x01);  
  systick_delay_ms(5);
  LCD1602_WriteCmd(0x0c);
}

void LCD1602_ImportGraph(void)
{
  for(uint8 cnt=0;cnt<8;cnt++)//Write Chip picture into the CGRAM
  {
    LCD1602_DefChar(cnt,CHIP_Edge[cnt]);
  }
}

void LCD1602_WriteCmd(uint8 cmd)
{
  while(LCD1602_CheckBusy());
  PTC->PDDR |= (uint32)(0XFF);          //Change direction into Output
  systick_delay(20);
  LCD_RS(0);
  LCD_RW(0);
  PTC->PDOR |= (uint32)(cmd);           //Write a Byte into Data Register
  PTC->PDOR &= (uint32)((0XFFFFFF00)|cmd);
  LCD_EN(1);
  systick_delay(50);
  LCD_EN(0);
  systick_delay(20);
}

uint8 LCD1602_CheckBusy(void) 
{ 
  LCD_RS(0);; 
  LCD_RW(1);; 
  LCD_EN(0);; 
  systick_delay(10); 
  LCD_EN(1);;
  PTC->PDDR &= ~((uint32)(1<<7));       //Change direction into Input
  return (((PTC->PDIR)&(0X80))>>7);     //Get the value of C7
}

void LCD1602_WriteDat(uint8 data)
{
  while(LCD1602_CheckBusy());
  PTC->PDDR |= (uint32)(0XFF);
  systick_delay(20);
  LCD_RS(1);
  LCD_RW(0);
  PTC->PDOR |= (uint32)(data);
  PTC->PDOR &= (uint32)((0XFFFFFF00)|data);
  LCD_EN(1);
  systick_delay(50);                    //Very important!
  LCD_EN(0);                            //Do not modify!
  //systick_delay(20);
}

void LCD1602_GPIO_Configuration(void)
{
  uint8 i=8;
  SIM->SCGC5 |= (SIM_SCGC5_PORTC_MASK);         //Enable the PHB Clock
  while(i--)
  {
    PORTC->PCR[i] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTC->PCR[i] |= PORT_PCR_MUX(1);
    PTC->PDDR |= (uint32)(1<<i);                //Direction: output
    PTC->PDOR &= ~(uint32)(1<<i);               //State:       0
  }
  PORTC->PCR[13] &= ~(uint32)PORT_PCR_MUX_MASK; //Clear the previous function
  PORTC->PCR[15] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTC->PCR[19] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTC->PCR[13] |= PORT_PCR_MUX(1);            //Set Function as GPIO
  PORTC->PCR[15] |= PORT_PCR_MUX(1);
  PORTC->PCR[19] |= PORT_PCR_MUX(1);
  PTC->PDDR |= (uint32)(0xff);                  //Set Direction as Output
  PTC->PDDR |= (uint32)((1<<19)|(1<<15)|(1<<13));
  PTC->PDOR &= ~(uint32)((1<<19)|(1<<15)|(1<<13)|0xff);
}

uint8 LCD1602_Str(uint8 x,uint8 y,const char *str)
{
  uint8 cursor_pos = x;
  if(y==0)		{LCD1602_WriteCmd(0x80+x);}
  else			{LCD1602_WriteCmd(0xc0+x);}
  while(*str)
  {
    LCD1602_WriteDat(*str);
    str++;
    cursor_pos++;
  }
  return cursor_pos;
}

void LCD1602_Char(uint8 x,uint8 y, char letter)
{
  if(y==0)		{LCD1602_WriteCmd(0x80+x);}
  else			{LCD1602_WriteCmd(0xc0+x);}
  LCD1602_WriteDat(letter);
}

void LCD1602_CleanLine(uint8 x,uint8 y)
{
  uint8 cursor_x = x;
  if(y==0)    {LCD1602_WriteCmd(0x80+x);}
  else        {LCD1602_WriteCmd(0xc0+x);}
  while(cursor_x < 16)
  {
    LCD1602_WriteDat(' ');
    cursor_x++;
  }
}

void LCD1602_CleanScreen(void)
{
  LCD1602_WriteCmd(0x01);
  systick_delay_ms(2);
}

void LCD1602_DefChar(uint8 char_index,const uint8* data)
{
  uint8 cnt;
  if(char_index >= 8)   return;
  for(cnt=0;cnt<8;cnt++)
  {
    LCD1602_WriteCmd(0x40|char_index<<3|cnt);
    LCD1602_WriteDat(*data++);
  }
}

void LCD_Printf(const char* format,...)
{
  va_list args;
  int length,cnt,x_pos,y_pos;
  
  va_start(args,format);
  x_pos = 0;
  y_pos = 0;
  length = vsprintf(sprint_buf,format,args);
  for(cnt=0;cnt<length;cnt++)
  {
    /*if(format[cnt]=='%'&&format[cnt+1]=='b')
    {
      
    }*/
    if(sprint_buf[cnt]=='\n')
    {
      y_pos++;
      x_pos = cnt;
      x_pos++;
      continue;
    }
    LCD1602_Char(cnt-x_pos,y_pos,sprint_buf[cnt]);
  }
  va_end(args);
}

void LCD_Print_BIN(uint8 x,uint8 y, unsigned int num)
{
  if(y==0)
    LCD1602_WriteCmd(0x80 + x);
  else
    LCD1602_WriteCmd(0xc0 + x);
  int i = 16;
  for(i=16;i>0;i--)
  {
    LCD1602_WriteDat(0x30 + ((num&0x8000)>>15));
    num <<= 1;
  }
}

#ifdef __cplusplus
}
#endif
