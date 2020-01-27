/*--------------------------------------------------------------------------
* @file         IC_Test.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides all class claims for tests.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "headfiles.h"
#include "Num_Convert.h"
#ifndef _IC_TEST_H
#define _IC_TEST_H

#define SEND_WORD(X) PTD->PDOR = (uint16)(X);systick_delay(100)
#define READ_WORD    (uint16)(PTB->PDIR)|(PTE->PDIR<<8)

typedef enum
{
  Normal,
  Auto,
  Manual,
  ShowResult,
  ShowFig,
  Wait
}State_Typedef;

typedef enum
{
  FAST,
  FULL
}TestType;

typedef enum
{
  logic_gate,
  encoder,
  decoder,
  flip_flop,
  comparator,
  multiplexer,
  demultiplexer,
  tri_state,
  shift_reg,
  serial_parallel,
  unknown_chip
}CHIP_Typedef;

typedef enum
{
  INPUT,
  OTHER
}DDR_Typedef;

typedef enum
{
  AND,
  OR,
  NOT,
  NAND,
  NOR,
  EOR,
  unknown_gate
}GATE_Typedef;

typedef struct//To record the string name and the index of the chip in Lib 
{
  char*  ID_Name;
  uint16 Index;
}CHIP_Name_Typedef;

typedef struct//To record the general parameters of the chip
{
  CHIP_Typedef          CHIP_Type;
  GATE_Typedef          GATE_Type;
  uint32                PIN_Direction;
  uint8                 PIN_Error[16];
  CHIP_Name_Typedef     CHIP_Name;
}CHIP_Para_Typedef;

void Dector_Init(void);
void TEST_Init(CHIP_Para_Typedef* CHIP_Parameter);
void TEST_Direction(CHIP_Para_Typedef* CHIP_Parameter);
void TEST_Type(CHIP_Para_Typedef* CHIP_Parameter);
void TEST_ID(CHIP_Para_Typedef* CHIP_Parameter);

void AUTO_Test(void);
uint8 MANUAL_Test(void);

static char* GATE_ID(void);
static bool GATE_Test(uint8 index,TestType TEST_TYPE);

uint16 ID2INDEX(char*  ID_Name);

static char* CODER_ID(void);


void __DEBUG_PRINT_PROCESS(uint32 send,NUM_Type scale);
void __DEBUG_PRINT_PROPERTY(uint32 dir);
void __DEBUG_PRINT_TYPE(CHIP_Typedef type);
extern CHIP_Para_Typedef        CHIP_Parameter;
extern State_Typedef DectorState;
extern State_Typedef DectorLastState;
#endif


