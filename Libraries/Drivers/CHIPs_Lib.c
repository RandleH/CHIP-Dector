/*--------------------------------------------------------------------------
* @file         CHIPs_Lib.c
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides keys and acks for chips.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "CHIPs_Lib.h"

const uint16_t  IO__GATE[] = {
  IO__74XX00,   
  IO__74XX02,     
  IO__74XX03,     
  IO__74XX04,
  IO__74XX05,
  IO__74XX08,   
  IO__74XX20,
};

const uint16_t GATE_KEYs[][6]={
  KEY__NULL,  // 0
  KEY__74XX00,// 1
  KEY__74XX02,// 2
  KEY__74XX03,// 3
  KEY__74XX04,// 4
  KEY__74XX05,// 5
  KEY__74XX08,// 6
  KEY__74XX09,// 7
  KEY__74aa20,
  KEY__74bb20,
  KEY__74cc20,
  KEY__74dd20 // 11
};
const uint16_t GATE_ACKs[][6]={
  ACK__NULL,  // 0
  ACK__74XX00,// 1
  ACK__74XX02,// 2
  ACK__74XX03,// 3
  ACK__74XX04,// 4
  ACK__74XX05,// 5
  ACK__74XX08,// 6
  ACK__74XX09,// 7
  ACK__74aa20,
  ACK__74bb20,
  ACK__74cc20,
  ACK__74dd20 // 11
};

const uint16_t GATE_BASEs[]={
  IDX__NULL  ,
  IDX__74XX00,
  IDX__74XX02,
  IDX__74XX03,
  IDX__74XX04,
  IDX__74XX05,
  IDX__74XX08,
  IDX__74XX09,
  IDX__74XX20,
};



uint8_t sizeof_GATE_KEYs(void)  {return sizeof(GATE_KEYs)/sizeof(*GATE_KEYs);}
uint8_t sizeof_GATE_ACKs(void)  {return sizeof(GATE_ACKs)/sizeof(*GATE_ACKs);}
uint8_t sizeof_IO__GATE (void)  {return sizeof(IO__GATE) /sizeof(*IO__GATE); }
uint8_t sizeof_GATE_BASEs(void) {return sizeof(GATE_BASEs) /sizeof(*GATE_BASEs); }


