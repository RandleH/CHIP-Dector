/*
** ###################################################################
**     Processors:          MK60DN512VLL10
**
**     Compilers:           ARM Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    74 ALL SERIES/ National Semiconductor / 
**     Version:             rev. 1.1, 2020-02-15
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MK60D10
**
**     Copyright (c) 2019 Randle_H. All rights reserved.
**
**     github:                 github.com/RandleH
**     mail:                   RandleH@163.com/1748171073@qq.com
**
**     Revisions:
**     - rev. 1.0 (2019-11-03)
**         Initial version
**     - rev. 1.1 (2012-04-13)
**         Added new #define symbol MCU_MEM_MAP_VERSION_MINOR.
**         Added new #define symbols <peripheralType>_BASE_PTRS.
**
** ###################################################################
*/
#include "CHIPs_Lib.h"
#include "stdlib.h"

bool TEST_FINISHED(bool*){return false;}

//GATE_TESTs==================================================================================================================//
bool is__74xx00(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 4};
  while(vector.val--){
    SEND(0 ,vector.bin.bit0); SEND(1, vector.bin.bit1);
    SEND(3 ,vector.bin.bit0); SEND(4, vector.bin.bit1);
    SEND(PIN9_14,vector.bin.bit0); SEND(11,vector.bin.bit1);
    SEND(13,vector.bin.bit0); SEND(14,vector.bin.bit1);
    systick_delay(100);
    if(READ(PIN1_14)  != (!(vector.bin.bit0&vector.bin.bit1)))   { result = false; p[PIN1_14]  = false; }
    if(READ(PIN4_14)  != (!(vector.bin.bit0&vector.bin.bit1)))   { result = false; p[PIN4_14]  = false; }
    if(READ(PIN8_14)  != (!(vector.bin.bit0&vector.bin.bit1)))   { result = false; p[PIN8_14]  = false; }
    if(READ(PIN11_14) != (!(vector.bin.bit0&vector.bin.bit1)))   { result = false; p[PIN11_14] = false; }
  }
  return result;
}

bool is__74xx02(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 4};
  while(vector.val--){
    SEND(1 ,vector.bin.bit0); SEND(2, vector.bin.bit0);
    SEND(4 ,vector.bin.bit0); SEND(5, vector.bin.bit0);
    SEND(9,vector.bin.bit0);  SEND(PIN9_14,vector.bin.bit0);
    SEND(12,vector.bin.bit0); SEND(13,vector.bin.bit0);
    systick_delay(100);
    if(READ(PIN1_14)  != !((vector.bin.bit0|vector.bin.bit1)))   { result = false; p[PIN1_14]  = false; }
    if(READ(PIN4_14)  != !((vector.bin.bit0|vector.bin.bit1)))   { result = false; p[PIN4_14]  = false; }
    if(READ(PIN10_14) != !((vector.bin.bit0|vector.bin.bit1)))   { result = false; p[PIN10_14] = false; } 
    if(READ(PIN13_14) != !((vector.bin.bit0|vector.bin.bit1)))   { result = false; p[PIN13_14] = false; }
  }
  return result;
}

bool is__74xx03(bool* p){return is__74xx00(p);}

bool is__74xx04(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 2};
  while(vector.val--){
    SEND(0 ,vector.bin.bit0); SEND(2 ,vector.bin.bit0);
    SEND(4 ,vector.bin.bit0); SEND(PIN9_14,vector.bin.bit0);
    SEND(12,vector.bin.bit0); SEND(14,vector.bin.bit0);
    systick_delay(100);
    if(READ(PIN2_14)  != !(vector.bin.bit0))  { result = false; p[PIN2_14]  = false; }
    if(READ(PIN4_14)  != !(vector.bin.bit0))  { result = false; p[PIN4_14]  = false; }
    if(READ(PIN6_14)  != !(vector.bin.bit0))  { result = false; p[PIN6_14]  = false; }
    if(READ(PIN8_14)  != !(vector.bin.bit0))  { result = false; p[PIN8_14]  = false; }
    if(READ(PIN10_14) != !(vector.bin.bit0))  { result = false; p[PIN10_14] = false; }
    if(READ(PIN12_14) != !(vector.bin.bit0))  { result = false; p[PIN12_14] = false; }
  }
  return result;
}

bool is__74xx05(bool* p){return is__74xx04(p);}

bool is__74xx08(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 4};
  SEND(PIN14_14,1);SEND(PIN7_14,0);
  systick_delay(10);
  while(vector.val--){
    SEND(0 ,vector.bin.bit0); SEND(1, vector.bin.bit1);
    SEND(3 ,vector.bin.bit0); SEND(4, vector.bin.bit1);
    SEND(PIN9_14,vector.bin.bit0); SEND(11,vector.bin.bit1);
    SEND(13,vector.bin.bit0); SEND(14,vector.bin.bit1);
    systick_delay(100);
    if(READ(PIN3_14)  != (bool)(vector.bin.bit0&vector.bin.bit1))   { result = false; p[PIN3_14]  = false; }
    if(READ(PIN6_14)  != (bool)(vector.bin.bit0&vector.bin.bit1))   { result = false; p[PIN6_14]  = false; }
    if(READ(PIN8_14)  != (bool)(vector.bin.bit0&vector.bin.bit1))   { result = false; p[PIN8_14]  = false; }
    if(READ(PIN11_14) != (bool)(vector.bin.bit0&vector.bin.bit1))   { result = false; p[PIN11_14] = false; }
  }
  return result;
}

bool is__74xx09(bool* p){return is__74xx08(p);}

bool is__74xx10(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 8};
  while(vector.val--){
    SEND(PIN1_14 ,vector.bin.bit0); SEND(PIN2_14 ,vector.bin.bit1); SEND(PIN13_14,vector.bin.bit2);
    SEND(PIN3_14 ,vector.bin.bit0); SEND(PIN4_14 ,vector.bin.bit1); SEND(PIN5_14 ,vector.bin.bit2); 
    SEND(PIN9_14,vector.bin.bit0);  SEND(PIN10_14,vector.bin.bit1); SEND(PIN11_14, vector.bin.bit2);
    systick_delay(100);
    if(READ(PIN12_14) != !(vector.bin.bit0&vector.bin.bit1&vector.bin.bit2))   { result = false; p[PIN12_14] = false; }
    if(READ(PIN6_14)  != !(vector.bin.bit0&vector.bin.bit1&vector.bin.bit2))   { result = false; p[PIN6_14] = false; }
    if(READ(PIN8_14)  != !(vector.bin.bit0&vector.bin.bit1&vector.bin.bit2))   { result = false; p[PIN8_14] = false; }
  }
  return result;
}

bool is__74xx14(bool* p)
{/*
  bool result = true;
  BYTE vector = {.val = 2};
  while(vector.val--){
    SEND(0 ,vector.bin.bit0); SEND(2 ,vector.bin.bit0);
    SEND(4 ,vector.bin.bit0); SEND(PIN9_14,vector.bin.bit0);
    SEND(12,vector.bin.bit0); SEND(14,vector.bin.bit0);
    systick_delay(100);
    if(READ(1) != !(vector.bin.bit0))  { result = false; p[] = false; }
    if(READ(3) != !(vector.bin.bit0))  { result = false; p[] = false; }
    if(READ(5) != !(vector.bin.bit0))  { result = false; p[] = false; }
    if(READ(9) != !(vector.bin.bit0))  { result = false; p[] = false; }
    if(READ(11)!= !(vector.bin.bit0))  { result = false; p[] = false; }
    if(READ(13)!= !(vector.bin.bit0))  { result = false; p[] = false; }
  }*/
  return false;
}

bool is__74xx20(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 16};
  while(vector.val--){
    SEND(PIN1_14 ,vector.bin.bit0); SEND(PIN2_14, vector.bin.bit1);SEND(PIN4_14 ,vector.bin.bit2); SEND(PIN5_14, vector.bin.bit3);
    SEND(PIN9_14,vector.bin.bit0); SEND(PIN10_14,vector.bin.bit1);SEND(PIN12_14,vector.bin.bit2); SEND(PIN13_14,vector.bin.bit3);
    systick_delay(100);
    if( READ(PIN6_14) != (!(vector.bin.bit0&vector.bin.bit1&vector.bin.bit2&vector.bin.bit3)) )   { result = false; p[PIN6_14] = false; }
    if( READ(PIN8_14) != (!(vector.bin.bit0&vector.bin.bit1&vector.bin.bit2&vector.bin.bit3)) )   { result = false; p[PIN8_14] = false; }
  }
  return result;
}

//TRISTATE_TESTs==============================================================================================================//
bool is__74xx125(bool* p)
{
  bool result = true;
  BYTE vector = {.val = 2};
  SEND(PIN1_14,0);SEND(PIN4_14,0);SEND(PIN10_14,0);SEND(PIN13_14,0);
  systick_delay(1);
  while(vector.val--){
    SEND(PIN2_14 ,vector.bin.bit0);
    SEND(PIN5_14 ,vector.bin.bit0); 
    SEND(PIN9_14 ,vector.bin.bit0); 
    SEND(PIN12_14,vector.bin.bit0);
    systick_delay(100);
    if(READ(PIN3_14)  != (bool)(vector.bin.bit0))  { result = false; p[PIN3_14]  = false;}
    if(READ(PIN6_14)  != (bool)(vector.bin.bit0))  { result = false; p[PIN6_14]  = false;}
    if(READ(PIN8_14)  != (bool)(vector.bin.bit0))  { result = false; p[PIN8_14]  = false;}
    if(READ(PIN11_14) != (bool)(vector.bin.bit0))  { result = false; p[PIN11_14] = false;}
  }

  vector = {.val = 4};
  SEND(PIN1_14,1);SEND(PIN4_14,1);SEND(PIN10_14,1);SEND(PIN13_14,1);
  systick_delay(1);
  while(vector.val--){
    SEND(PIN2_14 ,vector.bin.bit0);SEND(PIN3_14 ,vector.bin.bit1);
    SEND(PIN5_14 ,vector.bin.bit0);SEND(PIN6_14 ,vector.bin.bit1);
    SEND(PIN9_14 ,vector.bin.bit0);SEND(PIN8_14 ,vector.bin.bit1);
    SEND(PIN12_14,vector.bin.bit0);SEND(PIN11_14,vector.bin.bit1);
    systick_delay(100);
    if(READ(PIN3_14)  != (bool)(vector.bin.bit1))  { result = false; p[PIN3_14]  = false;}
    if(READ(PIN6_14)  != (bool)(vector.bin.bit1))  { result = false; p[PIN6_14]  = false;}
    if(READ(PIN8_14)  != (bool)(vector.bin.bit1))  { result = false; p[PIN8_14]  = false;}
    if(READ(PIN11_14) != (bool)(vector.bin.bit1))  { result = false; p[PIN11_14] = false;}
  }
  return result;
}

//SP_TESTs====================================================================================================================//
bool is__74xx164(bool* p)
{
  bool result     = true;
  BYTE vector1     = {.val = (uint8_t)(rand()%256)};
  BYTE vector2     = {.val = (uint8_t)(rand()%256)};
  const bool clk  = 0;
  const uint8_t clear = rand()%16;
  uint8_t temp = 0;

  SEND(PIN9_14,1);
  systick_delay_ms(1);
  SEND(PIN9_14,0);
  systick_delay_ms(1);
  SEND(PIN9_14,1);
  systick_delay_ms(1);
  for(uint8_t cnt=0;cnt<sizeof(BYTE)*8;cnt++){
    SEND(PIN8_14 ,clk);
    systick_delay_ms(10);
    SEND(PIN1_14,(vector1.val<<cnt&0x80));//MSB Shift
    SEND(PIN2_14,(vector2.val<<cnt&0x80));
    systick_delay_ms(10);
    SEND(PIN8_14 ,~clk);
    systick_delay_ms(10);
  }
  temp = READ(PIN13_14) <<7
        |READ(PIN12_14) <<6
        |READ(PIN11_14) <<5
        |READ(PIN10_14) <<4
        |READ(PIN6_14)  <<3
        |READ(PIN5_14)  <<2
        |READ(PIN4_14)  <<1
        |READ(PIN3_14)  <<0;
  if(temp != (vector1.val&vector2.val))   
  {
    result = false;
    p[PIN13_14]=p[PIN12_14]=p[PIN11_14]=p[PIN10_14]=p[PIN6_14]=p[PIN5_14]=p[PIN4_14]=p[PIN3_14]=false;
  }
  return result;
}

//COUNTER_TESTs===============================================================================================================//
bool is__74xx390(bool* p)
{
  bool result    = true;
  /*BYTE vector    = {.val = 0};
  const bool clk = 0;
  const uint8_t clear = rand()%16; 
  SEND(0 ,clk);SEND(14,clk);
  SEND(1 ,0);SEND(13,0);
  systick_delay(100);
  SEND(1 ,1);SEND(13,1);
  systick_delay(100);
  SEND(1 ,0);SEND(13,0);
  for(vector.val=0;vector.val<16;vector.val++){
    SEND(0 ,clk);SEND(14,clk);
    systick_delay(1);
    if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != vector.val%10) result = false;
    if(((READ(9)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != vector.val%10) result = false;
    SEND(0 ,~clk);SEND(14,~clk);
    systick_delay(1);
  }
  for(vector.val=0;vector.val<16;vector.val++){
    SEND(0 ,clk);SEND(14,clk);
    systick_delay(1);
    if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != vector.val%10) result = false;
    if(((READ(9)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != vector.val%10) result = false;
    SEND(0 ,~clk);SEND(14,~clk);
    systick_delay(1);
    if(vector.val == clear){
      SEND(1 ,0);SEND(13,0);
      systick_delay(100);
      SEND(1 ,1);SEND(13,1);
      systick_delay(100);
      SEND(1 ,0);SEND(13,0);
      if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != 0) result = false;
      if(((READ(9)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != 0) result = false;
      break;
    }
  }*/
  return result;
}

bool is__74xx393(bool* p)
{
  bool result    = true;
  BYTE vector    = {.val = 0};
  const bool clk = 0;
  const uint8_t clear = rand()%16; 
  SEND(PIN14_14,1);SEND(PIN7_14,0);
  systick_delay(10);
  SEND(0 ,clk);SEND(14,clk);
  SEND(1 ,0);SEND(13,0);
  systick_delay(100);
  SEND(1 ,1);SEND(13,1);
  systick_delay(100);
  SEND(1 ,0);SEND(13,0);
  for(vector.val=0;vector.val<16;vector.val++){
    SEND(0 ,clk);SEND(14,clk);
    systick_delay(1);
    if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != vector.val) {
      p[PIN6_14]=p[PIN5_14]=p[PIN4_14]=p[PIN3_14]=false;
      result = false;
    }
    if(((READ(9)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != vector.val) {
      p[PIN8_14]=p[PIN9_14]=p[PIN10_14]=p[PIN11_14]=false;
      result = false;
    }
    SEND(0 ,~clk);SEND(14,~clk);
    systick_delay(1);
  }
  for(vector.val=0;vector.val<16;vector.val++){
    SEND(0 ,clk);SEND(14,clk);
    systick_delay(1);
    if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != vector.val) {
      p[PIN6_14]=p[PIN5_14]=p[PIN4_14]=p[PIN3_14]=false;
      result = false;
    }
    if(((READ(9)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != vector.val) {
      p[PIN8_14]=p[PIN9_14]=p[PIN10_14]=p[PIN11_14]=false;
      result = false;
    }
    SEND(0 ,~clk);SEND(14,~clk);
    systick_delay(1);
    if(vector.val == clear){
      SEND(1 ,0);SEND(13,0);
      systick_delay(100);
      SEND(1 ,1);SEND(13,1);
      systick_delay(100);
      SEND(1 ,0);SEND(13,0);
      if(((READ(5)<<3) |(READ(4)<<2)  |(READ(3)<<1)  |(READ(2)))  != 0) {
        p[PIN6_14]=p[PIN5_14]=p[PIN4_14]=p[PIN3_14]=false;
        result = false;
      }
      if(((READ(PIN8_14)<<3) |(READ(PIN9_14)<<2) |(READ(11)<<1) |(READ(12))) != 0) {
        p[PIN8_14]=p[PIN9_14]=p[PIN10_14]=p[PIN11_14]=false;
        result = false;
      }
      break;
    }
  }
  return result;
}

//============================================================================================================================//
const uint16_t  IO__GATE[] = {
  IO__74XX00,   
  IO__74XX02,     
  IO__74XX03,     
  IO__74XX04,
  IO__74XX05,
  IO__74XX08,   
  IO__74XX10,
  IO__74XX20,
};

const uint16_t IO__TRISTATE[] = {
  IO__74XX125,
};

const uint16_t  IO__SP[] = {
  IO__74XX164,
};

const uint16_t  IO__COUNTER[] = {
  IO__74XX393,
};

//============================================================================================================================//
bool (*GATE_TESTs[])(bool*) = {
  TEST_FINISHED,
  is__74xx00,
  is__74xx02,
  is__74xx03,
  is__74xx04,
  is__74xx05,
  is__74xx08,
  is__74xx09,
  is__74xx10,
  is__74xx14,
  is__74xx20,
};

bool (*TRISTATE_TESTs[])(bool*) = {
  TEST_FINISHED,
  is__74xx125,
};

bool (*SP_TESTs[])(bool*) = {
  //TEST_FINISHED,
  NULL,
  is__74xx164,
};

bool (*COUNTER_TESTs[])(bool*) = {
  //TEST_FINISHED,
  NULL,
  is__74xx393,
};

uint8_t sizeof_IO__GATE(void)      {return sizeof(IO__GATE)      / sizeof(*IO__GATE); }
uint8_t sizeof_IO__TRISTATE(void)  {return sizeof(IO__TRISTATE)  / sizeof(*IO__TRISTATE);}
uint8_t sizeof_IO__SP(void)        {return sizeof(IO__SP)        / sizeof(*IO__SP); }
uint8_t sizeof_IO__COUNTER(void)   {return sizeof(IO__COUNTER)   / sizeof(*IO__COUNTER); }

uint8_t sizeof_GATE_TESTs(void)    {return sizeof(GATE_TESTs)    / sizeof(*GATE_TESTs); }
uint8_t sizeof_TRISTATE_TESTs(void){return sizeof(TRISTATE_TESTs)/ sizeof(*TRISTATE_TESTs);}
uint8_t sizeof_COUNTER_TESTs(void) {return sizeof(COUNTER_TESTs) / sizeof(*COUNTER_TESTs);}
uint8_t sizeof_SP_TESTs(void)      {return sizeof(SP_TESTs)      / sizeof(*SP_TESTs);}

//GATE_INFOs==================================================================================================================//
const char* info__GATE(void)       {return "NULL";}
const char* info__74LS00(void)     {return INFO__74LS00;}
const char* info__74LS02(void)     {return INFO__74LS02;}
const char* info__74LS03(void)     {return INFO__74LS03;}
const char* info__74LS04(void)     {return INFO__74LS04;}
const char* info__74LS05(void)     {return INFO__74LS05;}
const char* info__74LS08(void)     {return INFO__74LS08;}
const char* info__74LS09(void)     {return INFO__74LS09;}
const char* info__74LS10(void)     {return INFO__74LS10;}
const char* info__74LS14(void)     {return INFO__74LS14;}
const char* info__74LS20(void)     {return INFO__74LS20;}
const char* (*GATE_INFOs[])(void) = {
  info__GATE,
  info__74LS00,
  info__74LS02,
  info__74LS03,
  info__74LS04,
  info__74LS05,
  info__74LS08,
  info__74LS09,
  info__74LS10,
  info__74LS14,
  info__74LS20,
};

//TRISTATE_INFOs==================================================================================================================//
const char* info__TRISTATE(void)   {return "NULL";}
const char* info__74LS125(void)    {return INFO__74LS125;}
const char* (*TRISTATE_INFOs[])(void) = {
  info__TRISTATE,
  info__74LS125,
};

//SP_INFOs==================================================================================================================//
const char* info__SP(void)         {return "NULL";}
const char* info__74LS164(void)    {return INFO__74LS164;}
const char* (*SP_INFOs[])(void) = {
  info__SP,
  info__74LS164,
};

//GATE_TRUETHTABLEs==================================================================================================================//
TruthTable* ttb__null(TruthTable* p)
{
  p->numofInputs  = 0;
  p->numofOutputs = 0;
  p->numofCases   = 0;
  p->width  =  0;
  p->height = 0;
  p->ch = NULL;
  return p;
}

TruthTable* ttb__74xx00(TruthTable* p)
{
  p->numofInputs  = 2;
  p->numofOutputs = 1;
  p->numofCases   = (1<<p->numofInputs);
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+0)  = 'A'; *(p->ch+1)  = 'B';*(p->ch+2)  = 'Y';
  *(p->ch+3)  = 'L'; *(p->ch+4)  = 'L';*(p->ch+5)  = 'H';  
  *(p->ch+6)  = 'L'; *(p->ch+7)  = 'H';*(p->ch+8)  = 'H';  
  *(p->ch+9)  = 'H'; *(p->ch+10) = 'L';*(p->ch+11) = 'H';
  *(p->ch+12) = 'H'; *(p->ch+13) = 'H';*(p->ch+14) = 'L';
  return p;
}

TruthTable* ttb__74xx02(TruthTable* p)
{
  p->numofInputs  = 2;
  p->numofOutputs = 1;
  p->numofCases   = (1<<p->numofInputs);
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+0)  = 'A'; *(p->ch+1)  = 'B';*(p->ch+2)  = 'Y';
  *(p->ch+3)  = 'L'; *(p->ch+4)  = 'L';*(p->ch+5)  = 'H';  
  *(p->ch+6)  = 'L'; *(p->ch+7)  = 'H';*(p->ch+8)  = 'L';  
  *(p->ch+9)  = 'H'; *(p->ch+10) = 'L';*(p->ch+11) = 'L';
  *(p->ch+12) = 'H'; *(p->ch+13) = 'H';*(p->ch+14) = 'L';
  return p;
}

TruthTable* ttb__74xx03(TruthTable* p){return ttb__74xx00(p);}

TruthTable* ttb__74xx04(TruthTable* p)
{
  p->numofInputs  = 1;
  p->numofOutputs = 1;
  p->numofCases   = (1<<p->numofInputs);
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+0)  = 'A'; *(p->ch+1)  = 'Y';
  *(p->ch+2)  = 'L'; *(p->ch+3)  = 'H';  
  *(p->ch+4)  = 'H'; *(p->ch+5)  = 'L';  
  return p;
}

TruthTable* ttb__74xx05(TruthTable* p){return ttb__74xx04(p);}

TruthTable* ttb__74xx08(TruthTable* p)
{
  p->numofInputs  = 2;
  p->numofOutputs = 1;
  p->numofCases   = (1<<p->numofInputs);
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+0)  = 'A'; *(p->ch+1)  = 'B';*(p->ch+2)  = 'Y';
  *(p->ch+3)  = 'L'; *(p->ch+4)  = 'L';*(p->ch+5)  = 'L';  
  *(p->ch+6)  = 'L'; *(p->ch+7)  = 'H';*(p->ch+8)  = 'L';  
  *(p->ch+9)  = 'H'; *(p->ch+10) = 'L';*(p->ch+11) = 'L';
  *(p->ch+12) = 'H'; *(p->ch+13) = 'H';*(p->ch+14) = 'H';
  return p;
}

TruthTable* ttb__74xx09(TruthTable* p){return ttb__74xx08(p);}

TruthTable* ttb__74xx10(TruthTable* p)
{
  p->numofInputs  = 3;
  p->numofOutputs = 1;
  p->numofCases   = 4;
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+0)  = 'A';*(p->ch+1)  = 'B';*(p->ch+2)  = 'C';*(p->ch+3)  = 'Y';
  *(p->ch+4)  = 'X';*(p->ch+5)  = 'X';*(p->ch+6)  = 'L';*(p->ch+7)  = 'H';  
  *(p->ch+8)  = 'X';*(p->ch+9)  = 'L';*(p->ch+10) = 'X';*(p->ch+11) = 'H';  
  *(p->ch+12) = 'L';*(p->ch+13) = 'X';*(p->ch+14) = 'X';*(p->ch+15) = 'H';
  *(p->ch+16) = 'H';*(p->ch+17) = 'H';*(p->ch+18) = 'H';*(p->ch+19) = 'L';
  return p;
}

TruthTable* ttb__74xx14(TruthTable* p)
{
  p->numofInputs  = 1;
  p->numofOutputs = 1;
  p->numofCases   = 2;
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+ 0) = 'A';*(p->ch+ 1) = 'Y';
  *(p->ch+ 2) = 'L';*(p->ch+ 3) = 'H';
  *(p->ch+ 4) = 'H';*(p->ch+ 5) = 'L';
  return p;
}

TruthTable* ttb__74xx20(TruthTable* p)
{
  p->numofInputs  = 4;
  p->numofOutputs = 1;
  p->numofCases   = 5;
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+ 0) = 'A';*(p->ch+ 1) = 'B';*(p->ch+ 2) = 'C';*(p->ch+ 3) = 'D';*(p->ch+ 4) = 'Y';
  *(p->ch+ 5) = 'X';*(p->ch+ 6) = 'X';*(p->ch+ 7) = 'X';*(p->ch+ 8) = 'L';*(p->ch+ 9) = 'H';
  *(p->ch+10) = 'X';*(p->ch+11) = 'X';*(p->ch+12) = 'L';*(p->ch+13) = 'X';*(p->ch+14) = 'H';
  *(p->ch+15) = 'X';*(p->ch+16) = 'L';*(p->ch+17) = 'X';*(p->ch+18) = 'X';*(p->ch+19) = 'H';
  *(p->ch+20) = 'L';*(p->ch+21) = 'X';*(p->ch+22) = 'X';*(p->ch+23) = 'X';*(p->ch+24) = 'H';
  *(p->ch+25) = 'H';*(p->ch+26) = 'H';*(p->ch+27) = 'H';*(p->ch+28) = 'H';*(p->ch+29) = 'L';
  return p;
}

TruthTable* (*GATE_TTBs[])(TruthTable* p) = {
  ttb__null,
  ttb__74xx00,
  ttb__74xx02,
  ttb__74xx03,
  ttb__74xx04,
  ttb__74xx05,
  ttb__74xx08,
  ttb__74xx09,
  ttb__74xx10,
  ttb__74xx14,
  ttb__74xx20,
};

//TRISTATE_TRUETHTABLEs==================================================================================================================//
TruthTable* ttb__74xx125(TruthTable* p)
{
  p->numofInputs  = 2;
  p->numofOutputs = 1;
  p->numofCases   = 3;
  p->width = p->numofInputs+p->numofOutputs;
  p->height = p->numofCases+1;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+ 0) = 'A';*(p->ch+ 1) = 'E';*(p->ch+ 2) = 'Y';
  *(p->ch+ 3) = 'L';*(p->ch+ 4) = 'L';*(p->ch+ 5) = 'L';
  *(p->ch+ 6) = 'H';*(p->ch+ 7) = 'L';*(p->ch+ 8) = 'H';
  *(p->ch+ 9) = 'X';*(p->ch+10) = 'H';*(p->ch+11) = 'Z';
  return p;
}

TruthTable* (*TRISTATE_TTBs[])(TruthTable* p) = {
  ttb__null,
  ttb__74xx125,
};

//SP_TRUETHTABLEs==================================================================================================================//
TruthTable* ttb__74xx164(TruthTable* p)
{
  p->numofInputs  = 4;
  p->numofOutputs = 8;
  p->numofCases   = 5;
  p->width = 1;
  p->height = 6;
  p->ch = (int*)malloc(p->height*p->width*sizeof(char));
  *(p->ch+ 0) = 0;
  *(p->ch+ 1) = -1;
  *(p->ch+ 2) = -2;
  *(p->ch+ 3) = -3;
  *(p->ch+ 4) = -4;
  *(p->ch+ 5) = -5;


  p->str[0] = "CE  CK AB D[a:h]";
  p->str[1] = "L   X  XX LL...L";
  p->str[2] = "H   L  XX ab...h";
  p->str[3] = "H   UP HH Ha...g";
  p->str[4] = "H   UP LX La...g";
  p->str[5] = "H   UP XL La...g";
  return p;
}

TruthTable* (*SP_TTBs[])(TruthTable* p) = {
  ttb__null,
  ttb__74xx164,
};
