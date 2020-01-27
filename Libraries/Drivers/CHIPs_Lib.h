/*--------------------------------------------------------------------------
* @file         CHIPs_Lib.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides keys and acks for chips.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "common.h"
#ifndef _CHIPs_LIB_H
#define _CHIPs_LIB_H


/*---------------------------------------------------
Logic Gate Chips----Data Base for Input and Output
---------------------------------------------------*/
#define IO_16PIN(X)  (uint16)(X&(~(1<<7))|(1<<15))
#define IO_14PIN(X)  (uint16)(X&(~((1<<8)|(1<<7)))|((1<<15)|(1<<6)))

#define IO_RECV_16PIN(X) (uint16)(X&(~(1<<7))|(1<<15))  //VCC = 1; GND = 0; OUT = 1;IN = 0;
#define IO_RECV_14PIN(X) (uint16)(X&(~(1<<6))|(1<<15))  //VCC = 1; GND = 0; OUT = 1;IN = 0;

#define IO_SEND_16PIN(X) (uint16)(~(X|(1<<15)|(1<<7)))                 //VCC = 0; GND = 0; OUT = 0;IN = 1;
#define IO_SEND_14PIN(X) (uint16)(~(X|(1<<15)|(1<<8)|(1<<7)|(1<<6)))   //VCC = 0; GND = 0; OUT = 0;IN = 1;

#define IO__74XX00 0x9264       //x001 001x xx10 0100
#define IO__74XX02 0xc849       //x100 100x xx00 1001
#define IO__74XX03 0x9264       //x001 001x xx10 0100
#define IO__74XX04 0xaa6a       //x010 101x xx10 1010
#define IO__74XX08 0x9264       //x001 001x xx10 0100
#define IO__74XX09 0x9264       //x001 001x xx10 0100
#define IO__74XX20 0x8260       //x000 001x xx10 0000

extern uint16  IO__GATE[6];
/*---------------------------------------------------
Logic Gate Chips----Data Base for Logic Test
---------------------------------------------------*/
#define TWO_INPUT_CLEAR_MASK    (uint16)((0x03<<13)|(0x03<<10)|(0x03<<3)|(0x03<<0))
#define TWO_INPUT_MASK(X)       (uint16)((X<<13)|(X<<10)|(X<<3)|(X<<0))
#define TWO_INPUT(X)            (uint16)(X&(~TWO_INPUT_CLEAR_MASK)|(TWO_INPUT_MASK(X)))

//VCC = 1; GND = 0; IN = key; OUT = 1; NC = 0;
#define KEY__74XX00 {IO_SEND_14PIN(IO__74XX00),0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 0
#define KEY__74XX02 {IO_SEND_14PIN(IO__74XX02),0xC809,0xDA1B,0xEC2D,0xFE3F,'$'} // 1
#define KEY__74XX03 {IO_SEND_14PIN(IO__74XX03),0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 2
#define KEY__74XX04 {IO_SEND_14PIN(IO__74XX04),0xAA2A,0xFE3F,'$'}               // 3
#define KEY__74XX08 {IO_SEND_14PIN(IO__74XX08),0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 4
#define KEY__74XX09 {IO_SEND_14PIN(IO__74XX09),0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 5
#define KEY__74aa20 {IO_SEND_14PIN(IO__74XX20),0x8220,0x8621,0x8A22,0x8E23,'$'} // 6
#define KEY__74bb20 {IO_SEND_14PIN(IO__74XX20),0xA228,0xA629,0xAA2A,0xAE2B,'?'}
#define KEY__74cc20 {IO_SEND_14PIN(IO__74XX20),0xC230,0xC631,0xCA32,0xCE33,'?'}
#define KEY__74dd20 {IO_SEND_14PIN(IO__74XX20),0xE238,0xE639,0xEA3A,0xEE3B,'?'}
extern const uint16 GATE_KEYs[][6];

//VCC = 1; GND = 0; IN = key; OUT = ack; NC = 0;
#define ACK__74XX00 {IO_RECV_14PIN(IO__74XX00),0x9224,0xB62D,0xDA36,0xEC1B,'$'} //‬
#define ACK__74XX02 {IO_RECV_14PIN(IO__74XX02),0x8000,0xDA1B,0xEC2D,0xB636,'$'}
#define ACK__74XX03 {IO_RECV_14PIN(IO__74XX03),0x9224,0xB62D,0xDA36,0xEC1B,'$'} //
#define ACK__74XX04 {IO_RECV_14PIN(IO__74XX04),0xAA2A,0xD415,'$'}
#define ACK__74XX08 {IO_RECV_14PIN(IO__74XX08),0x8000,0xA409,0xC812,0xFE3F,'$'} ///
#define ACK__74XX09 {IO_RECV_14PIN(IO__74XX09),0x8000,0xA409,0xC812,0xFE3F,'$'} ///
#define ACK__74aa20 {IO_RECV_14PIN(IO__74XX20),0x8220,0x8621,0x8A22,0x8E23,'?'}
#define ACK__74bb20 {IO_RECV_14PIN(IO__74XX20),0xA228,0xA629,0xAA2A,0xAE2B,'?'}
#define ACK__74cc20 {IO_RECV_14PIN(IO__74XX20),0xC230,0xC631,0xCA32,0xCE33,'?'}
#define ACK__74dd20 {IO_RECV_14PIN(IO__74XX20),0xE238,0xE639,0xEA3A,0xEC1B,'$'}
extern const uint16 GATE_ACKs[][6];

/*---------------------------------------------------
Index----For All 74-series Chips
---------------------------------------------------*/
#define IDX__74XX00 0
#define IDX__74XX02 1
#define IDX__74XX03 2
#define IDX__74XX04 3
#define IDX__74XX08 4
#define IDX__74XX09 5
#define IDX__74XX20 6
#endif



