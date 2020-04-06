
#include "headfiles.h"
#ifndef UART_H
#define UART_H

#define UART_PORT     UART0
#define UART_GPIO     PORTA   
#define UART_TX_PIN   14     // A14
#define UART_RX_PIN   15     // A15
#define UART_BAUD     115200

void UART_Init(void);
static void UART_GPIO_Configuration(void);
#endif

