/*--------------------------------------------------------------------------
* @file         key_board.c
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for key board.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "key_board.h"
#include "bit.h"
char buf[10];
void KEYs_Init(void)
{
  SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK);         //Enable the PHB Clock
  PORTA->PCR[TEST_KEY] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTA->PCR[TEST_KEY] |= PORT_PCR_MUX(1);
  PTA->PDDR &= ~(uint32)(1<<TEST_KEY);          //Direction: Input
#if USE_INTERRUPT
  PORTA->PCR[TEST_KEY] |= PORT_PCR_IRQC(10);   //See the reference manual P278
  NVIC_SetPriority(PORTA_IRQn, 1U);
  NVIC_EnableIRQ(PORTA_IRQn);
  __enable_irq();
#endif
}

uint8 GET_TestKey(void)
{
  //return 1 = Button Down
  //return 0 = Button Up
  systick_delay_ms(1);
  return (!(uint8)((PTA->PDIR>>TEST_KEY)&0x01));
}

/*
    |——————————————|
    |  1  2  3  A  |
    |  4  5  6  B  |
    |  7  8  9  C  |
    |  *  0  #  D  |
    |——————————————|
        |||| ||||
    B[11:8]  E[8:11]
*/

void key_board_Init(void)
{
  uint8 cnt = 4;
  SIM->SCGC5 |= ( SIM_SCGC5_PORTB_MASK
                 |SIM_SCGC5_PORTE_MASK);
  while(cnt--)
  {
    PORTB->PCR[cnt+8] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTB->PCR[cnt+8] |= PORT_PCR_MUX(1);
    PORTE->PCR[cnt+8] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTE->PCR[cnt+8] |= PORT_PCR_MUX(1)|PORT_PCR_IRQC(9);//See Page 278
  }
  PTB->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTE->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTB->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
#if USE_INTERRUPT
  NVIC_SetPriority(PORTE_IRQn, 1U);
  NVIC_EnableIRQ(PORTE_IRQn);
  __enable_irq();
#endif
}

char* Keyboard_GetChar(void)
{
  uint8 pos = 4,cnt = 4;
  buf[0]='7';buf[1]='4';buf[2]='X';buf[3]='X';
  while(1)
  {
    if(KEY_DETECTED)
    {
      buf[cnt] = GET_Keyboard();
      if(buf[cnt]!='*')
        LCD1602_Char(pos,1,buf[cnt]);
      if(buf[cnt]=='*')
      {
        buf[cnt]='\0';
        break;
      }
      cnt++;pos++;
      systick_delay_ms(50);
    }   
  }
  return buf;
}

uint8 GET_Keyboard(void)
{
  uint8 key,letter='$';
  key = (uint8)((PTE->PDIR&0x00000F00)>>8);
  systick_delay(10);
  if(key != ((uint8)((PTE->PDIR&0x00000F00)>>8)))
    return '$';
  PTE->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTB->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTE->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  systick_delay(10);
  key |= (PTB->PDIR&0x00000F00)>>4;
  switch(key)
  {
  case 0x81:letter = '1';break;// 1
  case 0x41:letter = '2';break;// 2
  case 0x21:letter = '3';break;// 3
  case 0x11:letter = 'A';break;// A
  case 0x82:letter = '4';break;// 4
  case 0x42:letter = '5';break;// 5
  case 0x22:letter = '6';break;// 6
  case 0x12:letter = 'B';break;// B
  case 0x84:letter = '7';break;// 7
  case 0x44:letter = '8';break;// 8
  case 0x24:letter = '9';break;// 9
  case 0x14:letter = 'C';break;// C
  case 0x88:letter = '*';break;// *
  case 0x48:letter = '0';break;// 0
  case 0x28:letter = '#';break;// #
  case 0x18:letter = 'D';break;// D
  }
  systick_delay_ms(200);
  PTB->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTE->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTB->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  return letter;
}

