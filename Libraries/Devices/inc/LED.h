/*--------------------------------------------------------------------------
* @file         LED.h
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides drivers for leds.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/
#include "headfiles.h"

#ifndef _LED_H
#define _LED_H

#define R_LED     12//PORTC
#define G_LED     11//PORTC
#define TEST_LED  28//PORTA

#define ON  0
#define OFF 1

#define RUN(x) ((x==0)?(PTC->PDOR&=~(uint32)(1<<G_LED)):(PTC->PDOR|=(uint32)(1<<G_LED)))
#define ERR(x) ((x==0)?(PTC->PDOR&=~(uint32)(1<<R_LED)):(PTC->PDOR|=(uint32)(1<<R_LED)))
#define LED(x) ((x==0)?(PTA->PDOR&=~(uint32)(1<<TEST_LED)):(PTA->PDOR|=(uint32)(1<<TEST_LED)))
void LED_Init(void);
#endif
