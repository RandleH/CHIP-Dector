#ifndef _BIT_H
#define _BIT_H

#define Bit4_Rev(X) ((0x0f)&(((X&0x55)<<1|(X>>1)&0x55)&0x33)<<2|(((X&0x55)<<1|(X>>1)&0x55)>>2)&0x33)

#define Bit8_Rev(X) ((Bit4_Rev(X)&0x0F)<<4|(Bit4_Rev(X)>>4)&0x0F)
 

#endif