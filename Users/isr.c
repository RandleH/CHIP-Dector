#include "isr.h"

void PORTA_IRQHandler(void)
{
  PORTA->ISFR |= (uint32)(1<<TEST_KEY);
  //PORTA->ISFR = 0xffffffff;
  systick_delay_ms(100);
  if(DectorState == Normal)
  {
    DectorState = Auto;
  }
}

void PORTE_IRQHandler(void)
{
  uint8 key;
  key = (uint8)((PORTE->ISFR&0x00000F00)>>8);
  PORTE->ISFR |= (uint32)(0x0F<<8);
  systick_delay_ms(1);
  if(key != (uint8)((PTE->PDIR&0x00000F00)>>8))
    return;
  if(DectorState == ShowResult||DectorState == ShowFig)
  {
    systick_delay_ms(100);
    DectorState = Normal;
    return;
  }
  PTE->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTB->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTE->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  systick_delay(10);
  key |= (PTB->PDIR&0x00000F00)>>4;
  switch(key)
  {
  case 0x81:break;// 1
  case 0x41:break;// 2
  case 0x21:break;// 3
  case 0x11://A---Functional Key: Mannual Test
    if(DectorState == Normal)
    {
      DectorState = Wait;
      __disable_irq();
      systick_delay_ms(100);
    }break;
  case 0x82:break;// 4
  case 0x42:break;// 5
  case 0x22:break;// 6
  case 0x12:break;// B
  case 0x84:break;// 7
  case 0x44:break;// 8
  case 0x24:break;// 9
  case 0x14:break;// C
  case 0x88:break;// *
  case 0x48:break;// 0
  case 0x28:break;// #
  case 0x18:break;// D
  }
  systick_delay_ms(100);
  PTB->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTE->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTB->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
}
