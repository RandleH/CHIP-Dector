/*--------------------------------------------------------------------------
* @file         IC_Test.c
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides all the algorithms for tests.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "IC_Test.h"
#include "CHIPs_Lib.h"

CHIP_Para_Typedef       CHIP_Parameter;
State_Typedef DectorState     = Normal;
State_Typedef DectorLastState = Normal; 

void Dector_Init(void)
{
  // Port for Seading Data = D[15:0]
  // Port for Rending Data = E[7:0] & B[7:0]
  uint8 cnt = 16;
  SIM->SCGC5 |= ( SIM_SCGC5_PORTB_MASK
                 |SIM_SCGC5_PORTD_MASK
                 |SIM_SCGC5_PORTE_MASK);
  while(cnt--)
  {
    PORTD->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTD->PCR[cnt] |= PORT_PCR_MUX(1); //Alternative 1 (GPIO).
    PORTD->PCR[cnt] |= (uint32)(1<<6);  //Drive Strength Enable
  }
  cnt = 8;
  while(cnt--)
  {
    PORTE->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTE->PCR[cnt] |= PORT_PCR_MUX(1);
    PORTE->PCR[cnt] |= (1<<PORT_PCR_PE_SHIFT)|(0<<PORT_PCR_PS_SHIFT);
    PORTB->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTB->PCR[cnt] |= PORT_PCR_MUX(1);
    PORTE->PCR[cnt] |= (1<<PORT_PCR_PE_SHIFT)|(0<<PORT_PCR_PS_SHIFT);
  }
  PTB->PDDR &= ~(uint32)(0XFF);
  PTE->PDDR &= ~(uint32)(0XFF);
  PTD->PDDR |= (uint32)(0XFFFF);
  PTD->PDOR  = 0X00;
}

void AUTO_Test(void)
{
  TEST_Init(&CHIP_Parameter);
  TEST_Direction(&CHIP_Parameter);
  TEST_Type(&CHIP_Parameter);
  TEST_ID(&CHIP_Parameter);
  DSP_Information(&CHIP_Parameter,&DSP_Info_Structure);
}

uint8 MANUAL_Test(void)
{
  uint16 index = ID2INDEX(CHIP_Parameter.CHIP_Name.ID_Name);
  if(index==0xffff) return 0;
    
  if(CHIP_Parameter.CHIP_Type == logic_gate)
    GATE_Test(index,FULL);
  return 1;
}

void TEST_Init(CHIP_Para_Typedef* CHIP_Parameter)
{
  CHIP_Parameter->CHIP_Type = unknown_chip;
  CHIP_Parameter->GATE_Type = unknown_gate;
  CHIP_Parameter->PIN_Direction = 0xffff;
  CHIP_Parameter->CHIP_Name.ID_Name = "N/A";
  RUN(0);ERR(1);
}

void TEST_Direction(CHIP_Para_Typedef* CHIP_Parameter)
{
  uint32 send = 0;
  uint32 read = 0;
  uint32 dir  = 0;
  for(send=0;send<=0XFFFF;send++)
  {
    PTD->PDOR = send;
    systick_delay(10);
    read  = (uint8)(PTB->PDIR);
    read |= (PTE->PDIR<<8);
    dir  |= send^read;
    //__DEBUG_PRINT_PROCESS(send,BIN);
  }
  //__DEBUG_PRINT_PROPERTY(dir);
  CHIP_Parameter->PIN_Direction = dir;
}

void TEST_Type(CHIP_Para_Typedef* CHIP_Parameter)
{
  uint8  cnt;
  uint16 dir;
  dir = CHIP_Parameter->PIN_Direction;
  cnt = sizeof(IO__GATE)/sizeof(uint16);
  while(cnt--)
  {
    if(IO_14PIN(dir)==IO__GATE[cnt])
    {
      CHIP_Parameter->CHIP_Type = logic_gate;
      break;
    }
  }
  __DEBUG_PRINT_TYPE(CHIP_Parameter->CHIP_Type);
}

void TEST_ID(CHIP_Para_Typedef* CHIP_Parameter)
{
  if(CHIP_Parameter->CHIP_Type == logic_gate)
  {
    CHIP_Parameter->CHIP_Name.ID_Name = GATE_ID();
  }
}
/*-----------------------------------
Internal Function for Gate Type Chips
------------------------------------*/
static char* GATE_ID(void)
{
  uint8  index;
  char*  name;
  index = 10;
  while(index--)
  {
    if(GATE_Test(index,FAST)==true)
    {
      switch(index)
      {
      case 0: 
      case 2: CHIP_Parameter.GATE_Type = NAND;
              CHIP_Parameter.CHIP_Name.Index = IDX__74XX00;
              name = "74XX00/03";break;
      case 1: CHIP_Parameter.GATE_Type = NOR ;
              CHIP_Parameter.CHIP_Name.Index = IDX__74XX02;
              name = "74XX02";break;
      case 3: CHIP_Parameter.GATE_Type = NOT ;
              CHIP_Parameter.CHIP_Name.Index = IDX__74XX04;
              name = "74XX04";break;
      case 4:
      case 5: CHIP_Parameter.GATE_Type = AND ;
              CHIP_Parameter.CHIP_Name.Index = IDX__74XX08;
              name = "74XX08/09";break;
      case 6: CHIP_Parameter.GATE_Type = NAND;
              CHIP_Parameter.CHIP_Name.Index = IDX__74XX20;
              name = "74XX20";break;
      }
      return name;
    }
  }
  CHIP_Parameter.GATE_Type = unknown_gate;
  return "N/A";
}

static bool GATE_Test(uint8 index,TestType TEST_TYPE)
{
  uint8  cnt = 0;
  uint16 read;
  if(TEST_TYPE == FAST)
  {
    while(GATE_KEYs[index][cnt+1]!='$')
    {
      if(GATE_KEYs[index][cnt+1]=='?')
      {
        index--;
        cnt = 0;
        continue;
      }
      cnt++;
      SEND_WORD(GATE_KEYs[index][cnt]);
      read  = (uint8)(PTB->PDIR&0x000000FF);
      read |= (PTE->PDIR<<8);
      //__DEBUG_PRINT_PROCESS(GATE_KEYs[index][cnt],read,BIN); 
      if(  (read&GATE_ACKs[index][0]) != (GATE_ACKs[index][cnt]&GATE_ACKs[index][0])  )
      {
        cnt=0;
        break;
      }
    }
  }
  else if(TEST_TYPE == FULL)
  {
    while(GATE_KEYs[index][cnt+1]!='$')
    {
      if(GATE_KEYs[index][cnt+1]=='?')
      {
        index--;
        cnt = 0;
        continue;
      }
      cnt++;
      SEND_WORD(GATE_KEYs[index][cnt]);
      read  = (uint8)(PTB->PDIR&0x000000FF);
      read |= (PTE->PDIR<<8);
      for(int i=0;i<16;i++)
      {
        if((1<<i)&((read&GATE_ACKs[index][0])^(GATE_ACKs[index][cnt]&GATE_ACKs[index][0])))
          CHIP_Parameter.PIN_Error[i]=1;
        else
          CHIP_Parameter.PIN_Error[i]=0;
      }
    }
  }

  return (bool)cnt;
}

uint16 ID2INDEX(char*  ID_Name)
{
  uint8  cnt=0,i=0,j=1;
  uint16 num = 0;
  uint16 index=0;
  for(cnt=0;ID_Name[cnt]!='\0';cnt++);
  while(i<cnt-4)
  {
    i++;
    num += (ID_Name[cnt-i]-48)*j;// "48" is the ASCII Shift
    j*=10;
  }
  switch(num)
  {
  case 0:index=0;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 2:index=1;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 3:index=2;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 4:index=3;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 8:index=4;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 9:index=5;CHIP_Parameter.CHIP_Type = logic_gate;break;
  case 20:index=6;CHIP_Parameter.CHIP_Type = logic_gate;break;
  default:index = 0xffff;break;
  }
  return index;
}
/*---------------------------------------------------
The following functions are only for Debug
---------------------------------------------------*/
#if DEBUG
void __DEBUG_PRINT_BIN(uint8 x,uint8 y,uint16 num)
{
  LCD_Print_BIN(x,y,BIN);
}

void __DEBUG_PRINT_PROCESS(uint32 send,NUM_Type scale)
{
  uint16 read = 0xFFFF;
  PTD->PDOR = send;
  systick_delay(10);
  read  = (uint8)(PTB->PDIR);
  read |= (PTE->PDIR<<8);
  if(scale == BIN)
  {
    LCD_Print_BIN(0,0,send);
    LCD_Print_BIN(0,1,read);
  }
  else if(scale == HEX)
    Printf("Send:0x%x\nRead:0x%x",send,read);
  systick_delay_ms(1000);
}

void __DEBUG_PRINT_PROPERTY(uint32 dir)
{
  Printf("+FEDCBA98-654321");
  LCD_Print_BIN(0,1,dir);
}

void __DEBUG_PRINT_TYPE(CHIP_Typedef type)
{
  switch(type)
  {
  case 0:Printf("Logic Gate");      break;
  case 1:Printf("Encoder");         break;
  case 2:Printf("Decoder");         break;
  case 3:Printf("Flip Flop");       break;
  case 4:Printf("Comparator");      break;
  case 5:Printf("Multiplexer");     break;
  case 6:Printf("Demultiplexer");   break;
  case 7:Printf("Tri-State");       break;
  case 8:Printf("Shift_Reg");       break;
  case 9:Printf("S-P");             break;
  
  default:Printf("Unknown Chip");   break;
  }
}
#endif

