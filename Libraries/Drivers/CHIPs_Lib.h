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
#include "stdint.h"
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

/*---------------------------------------------------
Logic Gate Chips----Data Base for Logic Test
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
#define IO__74XX26
#define IO__74XX27      0xa260       //x010 001x xx10 0000
#define IO__74XX28      0xc849       //x100 100x xx00 1001
#define IO__74XX30      0x8240       //x000 001x xx00 0000
#define IO__74XX32      0x9264       //x001 001x xx10 0100
#define IO__74XX38      0x9264       //x001 001x xx10 0100
#define IO__74XX51      0x8260       //x000 001x xx10 0000
#define IO__74XX86      0x9264       //x001 001x xx10 0100
#define IO__74XX136     0x9264       //x001 001x xx10 0100
extern const uint16  IO__GATE[];

//VCC = 1; GND = 0; IN = key; OUT = 1; NC = 0;
#define KEY__NULL       {0xffff                    ,0xffff,0xffff,0xffff,0xffff,'$'} // [null]
#define KEY__74XX00     {IO_SEND_14PIN(IO__74XX00) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 1
#define KEY__74XX02     {IO_SEND_14PIN(IO__74XX02) ,0xC809,0xDA1B,0xEC2D,0xFE3F,'$'} // 2
#define KEY__74XX03     {IO_SEND_14PIN(IO__74XX03) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 3
#define KEY__74XX04     {IO_SEND_14PIN(IO__74XX04) ,0xAA2A,0xFE3F,'$'}               // 4  
#define KEY__74XX05     {IO_SEND_14PIN(IO__74XX04) ,0xAA2A,0xFE3F,'$'}               // 5
#define KEY__74XX08     {IO_SEND_14PIN(IO__74XX08) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 6
#define KEY__74XX09     {IO_SEND_14PIN(IO__74XX09) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'} // 7
#define KEY__74aa20     {IO_SEND_14PIN(IO__74XX20) ,0x8220,0x8621,0x8A22,0x8E23,'$'} // [8]
#define KEY__74bb20     {IO_SEND_14PIN(IO__74XX20) ,0xA228,0xA629,0xAA2A,0xAE2B,'?'} // [9]
#define KEY__74cc20     {IO_SEND_14PIN(IO__74XX20) ,0xC230,0xC631,0xCA32,0xCE33,'?'} // [10]
#define KEY__74dd20     {IO_SEND_14PIN(IO__74XX20) ,0xE238,0xE639,0xEA3A,0xEE3B,'?'} // 11
/*
#define KEY__74XX21
#define KEY__74XX26
#define KEY__74XX27
#define KEY__74XX28
#define KEY__74XX30
#define KEY__74XX32     {IO_SEND_14PIN(IO__74XX32) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'}
#define KEY__74XX38     {IO_SEND_14PIN(IO__74XX38) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'}
#define KEY__74XX51     {IO_SEND_14PIN(IO__74XX51) ,}
#define KEY__74XX86     {IO_SEND_14PIN(IO__74XX86) ,0x9224,0xB62D,0xDA36,0xFE3F,'$'}
#define KEY__74XX136    {IO_SEND_14PIN(IO__74XX136),0x9224,0xB62D,0xDA36,0xFE3F,'$'}*/
extern const uint16 GATE_KEYs[][6];

//VCC = 1; GND = 0; IN = key; OUT = ack; NC = 0;
#define ACK__NULL       {0xffff                   ,0xffff,0xffff,0xffff,0xffff,'$'} // [null]
#define ACK__74XX00     {IO_RECV_14PIN(IO__74XX00),0x9224,0xB62D,0xDA36,0xEC1B,'$'} //‬ 1
#define ACK__74XX02     {IO_RECV_14PIN(IO__74XX02),0x8000,0xDA1B,0xEC2D,0xB636,'$'} // 2
#define ACK__74XX03     {IO_RECV_14PIN(IO__74XX03),0x9224,0xB62D,0xDA36,0xEC1B,'$'} // 3
#define ACK__74XX04     {IO_RECV_14PIN(IO__74XX04),0xAA2A,0xD415,'$'}               // 4
#define ACK__74XX05     {IO_RECV_14PIN(IO__74XX04),0xAA2A,0xD415,'$'}               // 5
#define ACK__74XX08     {IO_RECV_14PIN(IO__74XX08),0x8000,0xA409,0xC812,0xFE3F,'$'} // 6
#define ACK__74XX09     {IO_RECV_14PIN(IO__74XX09),0x8000,0xA409,0xC812,0xFE3F,'$'} // 7
#define ACK__74aa20     {IO_RECV_14PIN(IO__74XX20),0x8220,0x8621,0x8A22,0x8E23,'$'} // [8]
#define ACK__74bb20     {IO_RECV_14PIN(IO__74XX20),0xA228,0xA629,0xAA2A,0xAE2B,'?'} // [9]
#define ACK__74cc20     {IO_RECV_14PIN(IO__74XX20),0xC230,0xC631,0xCA32,0xCE33,'?'} // [10]
#define ACK__74dd20     {IO_RECV_14PIN(IO__74XX20),0xE238,0xE639,0xEA3A,0xEC1B,'?'} // 11
/*
#define ACK__74XX21
#define ACK__74XX26
#define ACK__74XX27
#define ACK__74XX28
#define ACK__74XX30
#define ACK__74XX32
#define ACK__74XX38
#define ACK__74XX51
#define ACK__74XX86
#define ACK__74XX136*/
extern const uint16 GATE_ACKs[][6];



/*---------------------------------------------------
INDEX----For All 74-series Chips
---------------------------------------------------*/
enum BASE_INDEX_LOGIC_GATE{
	IDX__NULL     ,
	IDX__74XX00   ,
	IDX__74XX02   ,
	IDX__74XX03   ,
	IDX__74XX04   ,
	IDX__74XX05   ,
	IDX__74XX08   ,
	IDX__74XX09   ,
	IDX__74XX20 = IDX__74XX09+4,//11
};
extern const uint16_t GATE_BASEs[];

enum INDEX_ENCODER{

};

enum INDEX_FLIPFLOP{

};

enum INDEX_COMPARATOR{

};

enum INDEX_SHIFT_REG{

};

enum INDEX_COUNTER{

};

enum INDEX_ADDER{

};

enum INDEX_TRISTATE{

};

enum INDEX_MULTIPLEXIER{

};

enum INDEX_DEMULTIPLEXER{

};


uint8_t sizeof_GATE_KEYs (void);
uint8_t sizeof_GATE_ACKs (void);
uint8_t sizeof_IO__GATE  (void);
uint8_t sizeof_GATE_BASEs(void);
#endif



