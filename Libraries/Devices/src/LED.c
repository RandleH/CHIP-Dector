/*--------------------------------------------------------------------------
* @file         LED.c
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for leds.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "LED.h"

void LED_Init(void)
{
  SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK|SIM_SCGC5_PORTC_MASK);
  PORTC->PCR[R_LED] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTC->PCR[G_LED] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTA->PCR[TEST_LED] &= ~(uint32)PORT_PCR_MUX_MASK;
  PORTC->PCR[R_LED] |= PORT_PCR_MUX(1);
  PORTC->PCR[G_LED] |= PORT_PCR_MUX(1);
  PORTA->PCR[TEST_LED]  |= PORT_PCR_MUX(1);
  PTC->PDDR |= (uint32_t)((1<<R_LED)|(1<<G_LED));
  PTA->PDDR |= (uint32_t)(1<<TEST_LED);
  RUN(OFF);
  ERR(OFF);
  LED(OFF);
}