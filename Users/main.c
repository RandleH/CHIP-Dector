
#include "headfiles.h"
#include "CHIPs_Lib.h"
int main()
{
  System_Initialization();
  while(1)
  {
//DectorState shouldn't be altered while in a non-transition state
    switch(DectorState)
    {
  case Normal:  //Normal State          This is a non-transition state
    if(DectorLastState != Normal)
    {
      __enable_irq();
      CleanScreen();
      RUN(1);ERR(1);
      Printf("<A>=Mannual\n<Test>=Auto");
    }
    DectorLastState = Normal;
    break;
    
  case Auto:    //Auto Test State       
    AUTO_Test();
    DectorLastState = DectorState;
    DectorState     = ShowResult;
    break;
    
  case ShowResult://Showing the result  This is a non-transition state
    if(DectorLastState != ShowResult)
    {
      CleanScreen();
      DSP_Information(&CHIP_Parameter,&DSP_Info_Structure);   
    }
    DectorLastState = ShowResult;
    break;
    
  case Manual:  //Manual Test State     
    if(DectorLastState != Manual)
      MANUAL_Test();
    DectorLastState = DectorState;
    DectorState     = ShowFig;
    break;
    
  case ShowFig://Showing the chip fig   This is a non-transition state
    if(DectorLastState != ShowFig)
    {
      CleanScreen();
      DSP_ChipFig();
      __enable_irq();
    }
    DectorLastState = ShowFig;
    break;
    
  case Wait:    //Wait for users       
    if(DectorLastState != Wait)
    {
      LCD1602_CleanScreen();
      Printf("Which Chip?\n74XX____");
    }
    CHIP_Parameter.CHIP_Name.ID_Name = Keyboard_GetChar();    
    DectorLastState = DectorState;
    DectorState     = Manual;
    break;
    }
  }
}

void System_Initialization(void)
{
  systick_delay_ms(20);
  key_board_Init();
  Dector_Init();
  KEYs_Init();
  LED_Init();
  LCD1602_Init();
  DSP_Info_Init(&DSP_Info_Structure);
  DectorState = Normal;
  DectorLastState = Wait;
}

