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
#include "string.h"
#include "Num_Convert.h"
#include "CHIPs_Lib.h"
#include "isr.h"


#ifndef _IC_TEST_H
#define _IC_TEST_H

#define EX_REF_CLK  50 
#define UPDATE_STATE(OBJ) OBJ->last_state = OBJ->state
#define RECORD_STATE(OBJ) OBJ->last_state = OBJ->state
#define NEW_STATE(OBJ,X)  OBJ->state = (State)X    
#define CURRENT_STATE(OBJ)    OBJ->state 

#define SUPPORT_MAX_PINs 16
#define NOT_FOUND 0

#define SEND_WORD(X) PTD->PDOR = (uint16)(X);systick_delay(100)
#define READ_WORD    (uint16)(PTB->PDIR)|(PTE->PDIR<<8)

typedef enum
{
  __StandBy__,__AutoTest__,__AutoTesting__,__ManTest__,__ManTesting__,__ShowResult__,__ShowFig__,__Uninitialized__
}State;

typedef enum 
{
  logic_gate=0  ,and_gate       ,or_gate      ,not_gate       ,nand_gate      ,nor_gate     ,
  eor_gate      ,encoder        ,decoder      ,flip_flop      ,comparator     ,multiplexer  ,
  demultiplexer ,tri_state      ,shift_reg    ,serial_parallel,counter        ,unknown      ,numofType
}Type;

typedef enum{
  //and_gate,or_gate,not_gate,
}subType;

typedef enum {standard,debug}SysMode;

typedef char*  Name;
typedef uint16 Index;
typedef char*  Title;

class Test
{
friend class Debug;
friend class Display;
private:
  bool   init_flag;
  bool   dir_flag;
  bool   type_flag;
  bool   name_flag;

  void   importTruthTable(TruthTable* p);

  bool   isGate(void);
  bool   isEncoder(void);
  bool   isDecoder(void);
  bool   isFlipFlop(void);
  bool   isComparator(void);
  bool   isMultiplexer(void);
  bool   isDeMultiplexer(void);
  bool   isTriState(void);
  bool   isShiftReg(void);
  bool   isSPConvertor(void);
  bool   isCounter(void);

  bool   checkGate(void);
  bool   checkEncoder(void);
  bool   checkDecoder(void);
  bool   checkFlipFlop(void);
  bool   checkComparator(void);
  bool   checkMultiplexer(void);
  bool   checkDeMultiplexer(void);
  bool   checkTriState(void);
  bool   checkShiftReg(void);
  bool   checkCounter(void);
  bool   checkSPConvertor(void);
  bool   checkAll(void);

  uint8_t  searchGate(void);
  uint8_t  searchEcoder(void);
  uint8_t  searchTriState(void);
  uint8_t  searchSP(void);
  uint8_t  searchCounter(void);
public:
  Test();
  ~Test();
  uint16 pin_dir;
  Name   name;
  Type   type;
  Title  title[20];
  Index  index[numofType];
  TruthTable ttb;
  bool   pin[16];
  void   reset();
  bool   ioPort();
  bool   testPort(void);
  bool   findName(void);
  bool   checkPort(void);
};

typedef struct 
{
  uint8 x:4;
  uint8 y:1;
}Pos;

class Detector
{
friend class Debug;
friend class System;
private:
  State state;
  State last_state;
  Pos   tagName;
  Pos   tagType;
  Pos   tagFig;
  Pos   tagResult;
  Pos   tagText;
  char  getKeyBoard();
  void  display(uint8 x,uint8 y, const char* str);
public:
  Detector();
  ~Detector();
  Test    test;
  void    displayTitle(void);
  void    displayName(void);
  void    displayType(void);
  void    displayFig(void);
  void    displayResult(void);
  void    displayText(void);
  void    clearScreen(void);
  void    scanfName(void);
  void    analyzeName(void);
  void    led(void);
  void    led(uint8 stat);
  void    init(void);
  void    close(void);
  void    main(void);
};

class System{
public:
  System();
  ~System();
  void   init(void);
  void   regDetector(Detector* p);
  void   taskAllocate(void (*handler)(void));
  void   startTimer();
  uint16 getTimer();
  void   stopTimer();
  void   displaySetting();
  void   getClock();
  void   irq_setting(void);
  void   mode(SysMode mode);
  void   selfLoopBack(Detector* p);
private:
  uint32 mcgout_clk_mhz;
  uint32 core_clk_mhz;
  uint32 bus_clk_mhz;
  Detector* detector_cur;
};

extern System   $system$;
extern char sprint_buf[32];


#endif


