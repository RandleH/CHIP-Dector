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
#include "common.h"
#include "MK60D10.h"
#include "SystickDelay.h"
#include "stdint.h"
#include "mathematics.h"
#ifndef _CHIPs_LIB_H
#define _CHIPs_LIB_H

#define ZERO(X) (uint16_t)(~(1<<X))
#define ONE(X)  (uint16_t)(1<<X)

#define PIN1_14  0
#define PIN2_14  1
#define PIN3_14  2
#define PIN4_14  3
#define PIN5_14  4
#define PIN6_14  5
#define PIN7_14  6
#define PIN8_14  9
#define PIN9_14  10
#define PIN10_14 11
#define PIN11_14 12
#define PIN12_14 13
#define PIN13_14 14
#define PIN14_14 15

#define REV_4BIT(X) ((0x0f)&(((X&0x55)<<1|(X>>1)&0x55)&0x33)<<2|(((X&0x55)<<1|(X>>1)&0x55)>>2)&0x33)
#define REV_8BIT(X) ((REV_4BIT(((X&0xf0)>>4)))|(REV_4BIT((X&0x0f))<<4)) 

/*---------------------------------------------------
Logic Gate Chips----General Format Mask
---------------------------------------------------*/
#define IO_16PIN(X)               (uint16_t)(X&ZERO(7)|ONE(15))                      //VCC = 1; GND = 0; OUT = 1;IN = 0;
//#define IO_14PIN(X)               (uint16_t)(X&ZERO(6)&ZERO(7)&ZERO(8)|ONE(15))      //VCC = 1; GND = 0; OUT = 1;IN = 0; VOID1 = 0; VOID2 = 0;
#define IO_14PIN(X)               (uint16_t)((X&0xff00)|REV_8BIT((uint8_t)X))      //VCC = 1; GND = 0; OUT = 1;IN = 0; VOID1 = 0; VOID2 = 0;
//#define IO_RAW(X)               (uint16_t)(X)
#define IO_RAW(X)                 (uint16_t)((X&0xff00)|REV_8BIT((uint8_t)X))

#define IO_INPUT_HIGH_16PIN(X)    (uint16_t)((~X)&ZERO(7)&ZERO(15))                 // IN = 1; OTHER = 0;
#define IO_INPUT_HIGH_14PIN(X)    (uint16_t)((~X)&ZERO(6)&ZERO(7)&ZERO(8)&ZERO(15)) // IN = 1; OTHER = 0;
#define IO_INPUT_LOW_16PIN(X)     (uint16_t)(X   |ONE(7) |ONE(15) )                 // IN = 0; OTHER = 1;
#define IO_INPUT_LOW_14PIN(X)     (uint16_t)(X   |ONE(6) |ONE(7) |ONE(8) |ONE(15))  // IN = 0; OTHER = 1;

#define IO_OUTPUT_HIGH_16PIN(X)   (uint16_t)(X   &ZERO(7)&ZERO(15))                 // OUT = 1; OTHER = 0;
#define IO_OUTPUT_HIGH_14PIN(X)   (uint16_t)(X   &ZERO(6)&ZERO(7)&ZERO(8)&ZERO(15)) // OUT = 1; OTHER = 0;
#define IO_OUTPUT_LOW_16PIN(X)    (uint16_t)((~X)|ONE(7) |ONE(15))                  // OUT = 0; OTHER = 1;
#define IO_OUTPUT_LOW_14PIN(X)    (uint16_t)((~X)|ONE(6) |ONE(7) |ONE(8) |ONE(15))  // OUT = 0; OTHER = 1;

#define SEND(PIN,LEVEL)           ( (LEVEL==0)?(PTD->PDOR&=~(uint32)(1<<PIN)):(PTD->PDOR|=(uint32)(1<<PIN)))
#define READ(PIN)                 ( (PIN<7)?(bool)(PTB->PDIR>>PIN&0x01):(bool)(PTE->PDIR>>(PIN-8)&0x01) )
#define SEND_A(PIN,VAL_12BIT)      DAC0->DAT[0].DATH = DAC1->DAT[0].DATH = ((uint16_t)map_linear(VAL_12BIT,0,3.3,0,4096)&0x0fff)>>8;\
                                   DAC0->DAT[0].DATL = DAC1->DAT[0].DATL = (uint8_t)map_linear(VAL_12BIT,0,3.3,0,4096) 
#define ENABLE_DAC
#define DISABLE_DAC

typedef struct
{
	uint8_t bit0 : 1;
	uint8_t bit1 : 1;
	uint8_t bit2 : 1;
	uint8_t bit6 : 1;
	uint8_t bit3 : 1;
	uint8_t bit4 : 1;
	uint8_t bit5 : 1;
	uint8_t bit7 : 1;
}toByte;

typedef union
{
	uint8_t val;
	toByte  bin;
}BYTE;

typedef struct 
{
	uint8_t numofInputs;
	uint8_t numofOutputs;
	uint8_t numofCases; 
	uint8_t width;
	uint8_t height;
	int*   ch;    
	const char* str[10]; //Only for notes
}TruthTable;

/*---------------------------------------------------
I/O Port Data -------- Logic Gate Chips
---------------------------------------------------*/
//Input = 0; Output = 1;             //1xxx xxx0 01xx xxxx
#define IO__74XX00      0x9264       //x001 001x xx10 0100
#define IO__74XX02      0xc849       //x100 100x xx00 1001
#define IO__74XX03      0x9264       //x001 001x xx10 0100
#define IO__74XX04      0xaa6a       //x010 101x xx10 1010
#define IO__74XX05      0xaa6a       //x010 101x xx10 1010
#define IO__74XX08      0x9264       //x001 001x xx10 0100
#define IO__74XX09      0x9264       //x001 001x xx10 0100
#define IO__74XX10      0xa260       //x010 0010 xx10 0000
#define IO__74XX11      0xa260       //x010 0010 xx10 0000
#define IO__74XX14      0xaa6a       //x010 101x xx10 1010
#define IO__74XX20      0x8260       //x000 001x xx10 0000
#define IO__74XX21      0x8260       //x000 001x xx10 0000
#define IO__74XX27      0xa260       //x010 001x xx10 0000
#define IO__74XX28      0xc849       //x100 100x xx00 1001
#define IO__74XX30      0x8240       //x000 001x xx00 0000
#define IO__74XX32      0x9264       //x001 001x xx10 0100
#define IO__74XX38      0x9264       //x001 001x xx10 0100
#define IO__74XX51      0x8260       //x000 001x xx10 0000
#define IO__74XX86      0x9264       //x001 001x xx10 0100
#define IO__74XX136     0x9264       //x001 001x xx10 0100
extern const uint16_t  IO__GATE[];

/*---------------------------------------------------
I/O Port Data -------- Triple State Gate
---------------------------------------------------*/
//Input = 0; Output = 1;             //1xxx xxx0 01xx xxxx
#define IO__74XX125     0x9264       //1001 0010 0110 0100
extern const uint16_t IO__TRISTATE[];

/*---------------------------------------------------
I/O Port Data -------- Serial-Parallel Shift Register 
---------------------------------------------------*/
//Input = 0; Output = 1;             //1xxx xxx0 01xx xxxx
#define IO__74XX164     0xf87c       //1111 1000 0111 1100
extern const uint16_t  IO__SP[];

/*---------------------------------------------------
I/O Port Data -------- Counter 
---------------------------------------------------*/
//Input = 0; Output = 1;             //1xxx xxx0 01xx xxxx
#define IO__74XX393     0x9e7c       //1001 1110 0111 1100
extern const uint16_t  IO__COUNTER[];

/*---------------------------------------------------
INDEX----For All 74-series Chips
---------------------------------------------------*/
extern TruthTable* ttb__null(TruthTable* p);

enum INDEX_LOGIC_GATE{
	IDX__LOGIC_GATE,
	IDX__74XX00   ,
	IDX__74XX02   ,
	IDX__74XX03   ,
	IDX__74XX04   ,
	IDX__74XX05   ,
	IDX__74XX08   ,
	IDX__74XX09   ,
	IDX__74XX10   ,
	IDX__74XX14   ,
	IDX__74XX20   ,
};
extern bool (*GATE_TESTs[])(bool*);
extern const char* (*GATE_INFOs[])(void);
extern TruthTable* (*GATE_TTBs[])(TruthTable* p);

enum INDEX_ENCODER{

};

enum INDEX_FLIPFLOP{

};

enum INDEX_COMPARATOR{

};

enum INDEX_SHIFT_REG{

};

enum INDEX_SERIALPARALLEL{
	IDX__SERIALPARALLEL,
	IDX__74XX164   ,
};
extern bool (*SP_TESTs[])(bool*);
extern const char* (*SP_INFOs[])(void);
extern TruthTable* (*SP_TTBs[])(TruthTable* p);

enum INDEX_COUNTER{
	IDX__COUNTER,
	IDX__74XX393,
};
extern bool (*COUNTER_TESTs[])(bool*);

enum INDEX_ADDER{

};

enum INDEX_TRISTATE{
	IDX__TRISTATE,
	IDX__74XX125,
};
extern bool (*TRISTATE_TESTs[])(bool*);
extern const char* (*TRISTATE_INFOs[])(void);
extern TruthTable* (*TRISTATE_TTBs[])(TruthTable* p);

enum INDEX_MULTIPLEXIER{

};

enum INDEX_DEMULTIPLEXER{

};

uint8_t sizeof_IO__GATE  (void);
uint8_t sizeof_IO__SP(void);
uint8_t sizeof_IO__COUNTER(void);
uint8_t sizeof_IO__TRISTATE(void);

uint8_t sizeof_GATE_TESTs(void);
uint8_t sizeof_TRISTATE_TESTs(void);
uint8_t sizeof_SP_TESTs(void);
uint8_t sizeof_COUNTER_TESTs(void);

/*---------------------------------------------------
Chip Info Data -------- Logic Gate
---------------------------------------------------*/
//                     [      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ]
#define INFO__74LS00  "7400            NAND            VCC:5.0  VIH:2.0VIL:0.8      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[6:18]     TL~H:[5:18] [ns]       End                      "
#define INFO__74HC00
#define INFO__74LS02  "7402            OR              VCC:5.0  VIH:2.0VIL:0.7      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[6:18]     TL~H:[5:18] [ns]       End                      "
#define INFO__74HC02
#define INFO__74LS03  "7403            NAND            VCC:5.0  VIH:2.0VIL:0.7      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[6:18]     TL~H:[5:18] [ns]       End                      "
#define INFO__74HC03
#define INFO__74LS04  "7404            NOT             VCC:5.0  VIH:2.0VIL:0.8      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[4:15]     TL~H:[4:15] [ns]       End                      "
#define INFO__74HC04
#define INFO__74LS05  "7405            NOT             VCC:5.0  VIH:2.0VIL:0.8      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[4:15]     TL~H:[4:15] [ns]       End                      "
#define INFO__74HC05
#define INFO__74LS08  "7408            AND             VCC:5.0  VIH:2.0VIL:0.7      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[6:18]     TL~H:[5:18] [ns]       End                      "
#define INFO__74HC08
#define INFO__74LS09  "7409            AND             VCC:5.0  VIH:2.0VIL:0.7      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[6:18]     TL~H:[5:18] [ns]       End                      "
#define INFO__74HC09
#define INFO__74LS10  "7410            NAND            VCC:5.0  VIH:2.0VIL:0.8      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[4:15]     TL~H:[4:15] [ns]       End                      "
#define INFO__74HC10
#define INFO__74LS14  "7414            <NOT>           VCC:5.0  Vt+:1.6Vt-:0.8      [V]It+:0.14It-:0.18IOS:20~100  [mA]IIH:20   IIL:400II@7v:100   [uA]TH~L:[10:33]    TL~H:[8:25] [ns]       End                      " 
#define INFO__74HC14
#define INFO__74LS20  "7420            AND             VCC:5.0  VIH:2.0VIL:0.8      [V]IOH:0.4  IOL:8.0IOS:20~100  [mA]IIH:20   IIL:360II@7v:100   [uA]TH~L:[4:15]     TL~H:[4:15] [ns]       End                      "
#define INFO__74HC20

/*---------------------------------------------------
Chip Info Data -------- Triple State Gate
---------------------------------------------------*/
//                     [      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ]
#define INFO__74LS125 "74125           Tri-S           Vcc:5.0  Vih:2.0Vil:0.7      [V]Ioh:2.6 Iol:24.0Ios:20~100  [mA]Iozh:20  Iozl:20Iih:20      [uA]Iil:0.4   Ii:0.1Icc:11~20   [mA]Th~l:[:22]      Tl~h:[:21]  [ns]Tz~h:[:35]      Th~z:[:20]  [ns]Tz~l:[:40]      Tl~z:[:20]  [ns]       End                      "
#define INFO__74HC125

/*---------------------------------------------------
Chip Info Data -------- Serial-Parallel Shift Register
---------------------------------------------------*/
//                     [      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ][      16      ]
#define INFO__74LS164 "74164            SI-PO           8-Bit Sin-Pout  Shift Register Vcc:5.0  Vih:2.0Vil:0.8      [V]Ioh:0.4  Iol:8.0Ios:20~100  [mA]Iil:0.4   Ii:0.1Icc:16~27   [mA]Trel:30     Th:5Tclk:20     [ns]Tclear:20       Tsu:17      [ns]       End                      " 
#define INFO__74HC164


#endif



