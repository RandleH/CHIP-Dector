
#ifndef _headfile_h
#define _headfile_h

/*-------------------------------------
Self-Defination in this project
---------------------------------------*/
#define LCD1602_CleanScreen CleanScreen
#define LCD_Printf          Printf
//#define systick_delay_ms    Delay
/*-------------------------------------
End of Self-Defination
---------------------------------------*/
#include "SystickDelay.h"
#include "stdbool.h"
#include "MK60D10.h"
#include "common.h"

#include "IC_Test.h"
#include "bit.h"
#include "debug.h"

#include "LCD1602.h"
#include "LED.h"
#include "key_board.h"
#include "information.h"
void System_Initialization(void);
#endif
