
#ifdef __cplusplus
extern "C" {
#endif
#include "debug.h"
void Debug::ioPort(const Detector& p)
{
  LCD_Print_BIN(0,0,p.test.pin_dir);
}

void Debug::findType(const Detector& p)
{
  LCD1602_Str(0,1,this->info.toString(p.test.type));
}

void Debug::findName(const Detector& p)
{
  LCD_Printf((const char*)p.test.name);
}

void Debug::ioPort(void)
{
	static uint16_t vector = 0;
        
	if(GET_TestKey()||GET_Keyboard()!='$'){
		this->sendVector(vector);
		LCD_Print_BIN(0,0,vector);
		LCD_Print_BIN(0,1,this->recvVector());	
		vector++;
	}
}

void Debug::sendVector(uint16_t vector)
{
	SEND_WORD(vector);
}

uint16_t Debug::recvVector(void)
{
	uint16_t read = 0;
	systick_delay_ms(1);
	read  = (uint8)(PTB->PDIR&0x000000FF);
    read |= (PTE->PDIR<<8);
    return read;
}

uint8 GET_Keyboard(void)
{
  uint8 key,letter='$';
  key = (uint8)((PTE->PDIR&0x00000F00)>>8);
  systick_delay_ms(1);
  if(key != ((uint8)((PTE->PDIR&0x00000F00)>>8)))
    return '$';
  PTE->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTB->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTE->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  systick_delay_ms(1);
  key |= (PTB->PDIR&0x00000F00)>>4;
  switch(key)
  {
  case 0x81:letter = '1';break;// 1
  case 0x41:letter = '2';break;// 2
  case 0x21:letter = '3';break;// 3
  case 0x11:letter = 'A';break;// A
  case 0x82:letter = '4';break;// 4
  case 0x42:letter = '5';break;// 5
  case 0x22:letter = '6';break;// 6
  case 0x12:letter = 'B';break;// B
  case 0x84:letter = '7';break;// 7
  case 0x44:letter = '8';break;// 8
  case 0x24:letter = '9';break;// 9
  case 0x14:letter = 'C';break;// C
  case 0x88:letter = '*';break;// *
  case 0x48:letter = '0';break;// 0
  case 0x28:letter = '#';break;// #
  case 0x18:letter = 'D';break;// D
  }
  systick_delay_ms(200);
  PTB->PDDR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  PTE->PDDR &= (uint32)(~((1<<11)|(1<<10)|(1<<9)|(1<<8)));
  PTB->PDOR |= (uint32)((1<<11)|(1<<10)|(1<<9)|(1<<8));
  return letter;
}


bool GET_TestKey(void)
{
  //return 1 = Button Down
  //return 0 = Button Up
  systick_delay_ms(1);
  return (!(uint8)((PTA->PDIR>>TEST_KEY)&0x01));
}
#ifdef __cplusplus
}
#endif



