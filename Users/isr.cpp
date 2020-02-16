#include "isr.h"

#ifdef __cplusplus
extern "C"{
#endif

void PORTA_IRQHandler(void)
{
  $system$.taskAllocate(PORTA_IRQHandler);
  systick_delay_ms(10);
  PORTA->ISFR |= (uint32)(1<<TEST_KEY);
}

void PORTE_IRQHandler(void)
{
  $system$.taskAllocate(PORTE_IRQHandler);
  systick_delay_ms(10);
  PORTE->ISFR = 0xffffffff;
}


#ifdef __cplusplus
}
#endif
