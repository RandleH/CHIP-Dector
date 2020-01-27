/*--------------------------------------------------------------------------
* @file         Display.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides display solvements for this project.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "LCD1602.h"
#ifndef _DISPLAY_H
#define _DISPLAY_H
enum CHIP_EdgeIndex {RU,RD,U,D,LU,LD,EU,ED};
typedef struct
{
  char* TEXT_Name;
  uint8 Display;
  uint8 DSP_PosX;
  uint8 DSP_PosY;
  //uint8 lenth = sizeof(TEXT_Name)/sizeof(char);
}TEXT_Typedef;

typedef struct
{
  TEXT_Typedef Name;
  TEXT_Typedef Type;
  TEXT_Typedef Quality;
  TEXT_Typedef Gate;
}Info_Display_Typedef;
/*
typedef struct //To record the detail of the chip
{
  uint8 Temperature[2];// 0 = Min; 1 = Max
  char* Logic;
  char* MaxRate     = "%d to %d";
  const char* Symbol[]    = {"Vcc","Vih","Vil","Voh","Iol","Ta"};
  const char* Parameter[] = {"Supply voltage","H Input Voltage",
                             "L Input Voltage","H Output Voltage",
                            "L Output Current","OP Air Temper"}; 

}Detail_Display_Typedef;*/

typedef struct
{
  char* Logic;
  char* MaxRate;
  const char* Symbol[6];
  const char* Parameter[6];
}Detail_Display_Typedef;


void DSP_Info_Init(Info_Display_Typedef* DSP_Info_Structure);
void DSP_Detail_Init(Detail_Display_Typedef* DSP_Detail_Structure);
void DSP_Information(CHIP_Para_Typedef* CHIP_Parameter,Info_Display_Typedef* DSP_Info_Structure);
void DSP_ChipFig(void);
extern Info_Display_Typedef     DSP_Info_Structure;
extern const uint8 CHIP_Edge[][8];
#endif


