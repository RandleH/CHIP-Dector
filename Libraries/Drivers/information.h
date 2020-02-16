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
#include "IC_Test.h"


#ifndef _INFO_H
#define _INFO_H

#define INFO_ERR    -1
#define ASCII_SHIFT 48

#define HEAD_74XX   4
#define HEAD_CD     2

class Info
{
friend class Debug;
private:
  char buffer[20];
  uint16      get74XX___(Name name);
  uint16      getCD____(Name name);
  uint16      toNum(Name name,uint8 head_length);
public:
  Info();
  ~Info();
  const char* toString(Type type);
  Index       toIndex(Name name);
  Type        toType(Name name);
  Type        toType(Index* index);
  Name        toName(Index* index);
};


#endif


