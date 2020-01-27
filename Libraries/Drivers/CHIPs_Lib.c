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

uint16  IO__GATE[] = {
  IO__74XX00,   IO__74XX02,     IO__74XX03,     IO__74XX04,
  IO__74XX08,   IO__74XX20,
};

const uint16 GATE_KEYs[][6]={
  KEY__74XX00,
  KEY__74XX02,
  KEY__74XX03,
  KEY__74XX04,
  KEY__74XX08,
  KEY__74XX09,
  KEY__74aa20,
  KEY__74bb20,
  KEY__74cc20,
  KEY__74dd20
};
const uint16 GATE_ACKs[][6]={
  ACK__74XX00,
  ACK__74XX02,
  ACK__74XX03,
  ACK__74XX04,
  ACK__74XX08,
  ACK__74XX09,
  ACK__74aa20,
  ACK__74bb20,
  ACK__74cc20,
  ACK__74dd20
};



