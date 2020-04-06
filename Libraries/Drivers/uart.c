#include "uart.h"


void UART_Init(void)
{

	UART_GPIO_Configuration();
	switch(UART_PORT){
		case UART0:
			SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
			//port
	}
	
}

static void UART_GPIO_Configuration(void)
{
	switch(UART_PORT){
		case PORTA:
			SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
			if(UART_TX_PIN == 14 && UART_RX_PIN == 15){
				PORTA->PCR[UART_TX_PIN] &= ~(uint32)PORT_PCR_MUX_MASK;
				PORTA->PCR[UART_RX_PIN] &= ~(uint32)PORT_PCR_MUX_MASK;
				PORTA->PCR[UART_TX_PIN] |= PORT_PCR_MUX(?);
  				PORTA->PCR[UART_RX_PIN] |= PORT_PCR_MUX(?);
  				PTA->PDDR &= ~(uint32)((1<<UART_TX_PIN)|(1<<UART_RX_PIN));
			}
			break;
		default:break;
	}

}

