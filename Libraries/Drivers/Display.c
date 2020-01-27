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
#include "Display.h"
#include "CHIPs_Lib.h"

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

Info_Display_Typedef    DSP_Info_Structure;

void DSP_Info_Init(Info_Display_Typedef* DSP_Info_Structure)
{
  uint8 cnt = 0;
  for(cnt=0;cnt<8;cnt++)//Write Chip picture into the CGRAM
  {
    LCD1602_DefChar(cnt,CHIP_Edge[cnt]);
  }
  
  DSP_Info_Structure->Name.Display    = Enable;
  DSP_Info_Structure->Name.DSP_PosX   = 0;
  DSP_Info_Structure->Name.DSP_PosY   = 1;
  
  DSP_Info_Structure->Type.Display    = Enable;
  DSP_Info_Structure->Type.DSP_PosX   = 0;
  DSP_Info_Structure->Type.DSP_PosY   = 0;
  
  DSP_Info_Structure->Quality.Display  = Enable;
  DSP_Info_Structure->Quality.DSP_PosX = 12;
  DSP_Info_Structure->Quality.DSP_PosY = 1;
  
  DSP_Info_Structure->Gate.Display    = Enable;
  DSP_Info_Structure->Gate.DSP_PosX   = 12;
  DSP_Info_Structure->Gate.DSP_PosY   = 0;
}

void DSP_Detail_Init(Detail_Display_Typedef* DSP_Detail_Structure)
{
  DSP_Detail_Structure-> MaxRate = "%d to %d";
  DSP_Detail_Structure->Symbol[1] = "Vcc";//,"Vih","Vil","Voh","Iol","Ta"};
}
  
void DSP_Information(CHIP_Para_Typedef* CHIP_Parameter,Info_Display_Typedef* DSP_Info_Structure)
{
  DSP_Info_Structure->Name.TEXT_Name    = CHIP_Parameter->CHIP_Name.ID_Name;
  DSP_Info_Structure->Quality.TEXT_Name = "Good";
  switch(CHIP_Parameter->CHIP_Type)
  {
  case 0:DSP_Info_Structure->Type.TEXT_Name  = "Logic Gate";
        switch(CHIP_Parameter->GATE_Type)
        {
          case 0:DSP_Info_Structure->Gate.TEXT_Name = "AND";  break;
          case 1:DSP_Info_Structure->Gate.TEXT_Name = "OR";   break;
          case 2:DSP_Info_Structure->Gate.TEXT_Name = "NOT";  break;
          case 3:DSP_Info_Structure->Gate.TEXT_Name = "NAND"; break;
          case 4:DSP_Info_Structure->Gate.TEXT_Name = "NOR";  break;
          case 5:DSP_Info_Structure->Gate.TEXT_Name = "EOR";  break;
          case 6:
          default:DSP_Info_Structure->Quality.TEXT_Name = " Bad";
                  DSP_Info_Structure->Gate.TEXT_Name    = " N/A"; 
                  RUN(1);ERR(0);break;
      }break;
  case 1:DSP_Info_Structure->Type.TEXT_Name  = "Encoder";       break;
  case 2:DSP_Info_Structure->Type.TEXT_Name  = "Decoder";       break;
  case 3:DSP_Info_Structure->Type.TEXT_Name  = "Flip_flop";     break;
  case 4:DSP_Info_Structure->Type.TEXT_Name  = "Comparator";    break;
  case 5:DSP_Info_Structure->Type.TEXT_Name  = "Multiplexer";   break;
  case 6:DSP_Info_Structure->Type.TEXT_Name  = "Demultiplexer"; break;
  case 7:DSP_Info_Structure->Type.TEXT_Name  = "Tri State";     break;
  case 8:DSP_Info_Structure->Type.TEXT_Name  = "Shift Reg";     break;
  case 9:DSP_Info_Structure->Type.TEXT_Name  = "S-P";           break;
  case 10:
  default:DSP_Info_Structure->Type.TEXT_Name    = "Unknown Chip";
          DSP_Info_Structure->Gate.TEXT_Name    = " N/A";
          DSP_Info_Structure->Quality.TEXT_Name = " Bad";
          RUN(1);ERR(0);break;
  }
  
  LCD1602_CleanScreen();
  if(DSP_Info_Structure->Name.Display == Enable)
    LCD1602_Str( DSP_Info_Structure->Name.DSP_PosX,
                 DSP_Info_Structure->Name.DSP_PosY,
                 DSP_Info_Structure->Name.TEXT_Name );
  if(DSP_Info_Structure->Type.Display == Enable)
    LCD1602_Str( DSP_Info_Structure->Type.DSP_PosX,
                 DSP_Info_Structure->Type.DSP_PosY,
                 DSP_Info_Structure->Type.TEXT_Name );
  if(DSP_Info_Structure->Gate.Display == Enable)
    LCD1602_Str( DSP_Info_Structure->Gate.DSP_PosX,
                 DSP_Info_Structure->Gate.DSP_PosY,
                 DSP_Info_Structure->Gate.TEXT_Name );
  if(DSP_Info_Structure->Quality.Display == Enable)
    LCD1602_Str( DSP_Info_Structure->Quality.DSP_PosX,
                 DSP_Info_Structure->Quality.DSP_PosY,
                 DSP_Info_Structure->Quality.TEXT_Name );
}

void DSP_DataSheet(CHIP_Para_Typedef* CHIP_Parameter)
{
  switch(CHIP_Parameter->CHIP_Name.Index)
  {
  case IDX__74XX00:
  case IDX__74XX03:break;
  case IDX__74XX02:break;
  case IDX__74XX04:break;
  case IDX__74XX08:
  case IDX__74XX09:break;
  case IDX__74XX20:break;
  }
}

void DSP_ChipFig(void)
{
  uint8 cnt = 7;
  LCD1602_Char(15,0,RU);
  LCD1602_Char(15,1,RD);
  LCD1602_Char(7,0,LU);
  LCD1602_Char(7,1,LD);
  while(cnt--)
  {
    if(CHIP_Parameter.PIN_Error[6-cnt])
      LCD1602_Char(14-cnt,1,ED);
    else
      LCD1602_Char(14-cnt,1,D);
    
    if(CHIP_Parameter.PIN_Error[cnt+9])
      LCD1602_Char(14-cnt,0,EU);
    else
      LCD1602_Char(14-cnt,0,U);
  }
}

