/*--------------------------------------------------------------------------
* @file         IC_Test.c
* @author       Randle_H
* @version      V2.0.1
* @date         2019/11/24
* @Software     IAR 7.7 or MDK 5.17
* @Target core  MK60DN512VLL10
* @brief        This file provides all the algorithms for tests.
* COPYRIGHT NOTICE
 Copyright (c) 2019 Randle_H. All rights reserved.
----------------------------------------------------------------------------*/

#include "IC_Test.h"
#include "iostream"
#include "sstream"
#include "string"
using namespace std;
System   $system$;

Detector::Detector():state(__StandBy__),last_state(__Uninitialized__)
{
  this->tagName.x = 0;
  this->tagName.y = 0;
  this->tagType.x = 0;
  this->tagType.y = 1;
  this->tagFig .x = 0;
  this->tagFig .y = 0;
  this->tagResult.x = 0;
  this->test.title[__StandBy__]    = (char*)"[Stand By]";
  this->test.title[__AutoTest__]   = (char*)"[Auto Test]";
  this->test.title[__ManTest__]    = (char*)"[Manual Test]";
  this->test.title[__ShowResult__] = (char*)"";
  this->test.title[__ShowFig__]    = (char*)"";
  this->tagText.x = 0;
  this->tagText.y = 1;
}
Detector::~Detector(){}

void Detector::init(void)
{
  // Port for Seading Data = D[15:0]
  // Port for Rending Data = E[7:0] & B[7:0]
  uint8 cnt = 16;
  systick_delay_ms(20);
  SIM->SCGC5 |= ( SIM_SCGC5_PORTB_MASK
                 |SIM_SCGC5_PORTD_MASK
                 |SIM_SCGC5_PORTE_MASK);
  while(cnt--)
  {
    PORTD->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTD->PCR[cnt] |= PORT_PCR_MUX(1); //Alternative 1 (GPIO).
    PORTD->PCR[cnt] |= (uint32)(1<<6);  //Drive Strength Enable
  }
  cnt = 8;
  while(cnt--)
  {
    PORTE->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTE->PCR[cnt] |= PORT_PCR_MUX(1);
    PORTE->PCR[cnt] |= (1<<PORT_PCR_PE_SHIFT)|(0<<PORT_PCR_PS_SHIFT);
    PORTB->PCR[cnt] &= ~(uint32)PORT_PCR_MUX_MASK;
    PORTB->PCR[cnt] |= PORT_PCR_MUX(1);
    PORTE->PCR[cnt] |= (1<<PORT_PCR_PE_SHIFT)|(0<<PORT_PCR_PS_SHIFT);
  }
  PTB->PDDR &= ~(uint32)(0XFF);
  PTE->PDDR &= ~(uint32)(0XFF);
  PTD->PDDR |= (uint32)(0XFFFF);
  PTD->PDOR  = 0X00;
}

void Detector::main(void)
{
  if(this->state == this->last_state) return;
  this->clearScreen();
  switch(this->state){
    case __StandBy__:
    case __AutoTest__:
                          this->displayTitle();
                          this->displayText();
                          this->led(OFF);
                          UPDATE_STATE(this);                 break;
    case __ManTest__:
                          this->displayTitle();
                          this->led(OFF);
                          UPDATE_STATE(this);
                          this->scanfName();
                          NEW_STATE(this,__ManTesting__);     break;
    case __AutoTesting__:
                          this->test.reset();
                          this->test.ioPort();
                          this->test.findType();
                          this->test.findName();
                          RECORD_STATE(this);
                          NEW_STATE(this,__ShowResult__);     break;
    case __ShowResult__:
                          this->displayName();
                          this->displayType();
                          this->led();
                          UPDATE_STATE(this);                 break;
    case __ManTesting__:
                          this->analyzeName();
                          this->test.checkPort();
                          RECORD_STATE(this);
                          NEW_STATE(this,__ShowFig__);        break;
    case __ShowFig__:
                          this->displayFig();                 
                          UPDATE_STATE(this);                 break;
    default:return;
  }
  
}

void Detector::analyzeName(void)
{
  Info info;
  this->test.type = info.toType(this->test.name);
  this->test.index[this->test.type] = info.toIndex(this->test.name);
}

void Detector::close(void)
{
  
}

void Detector::displayTitle(void)
{
  this->display(this->tagName.x,this->tagName.y,(const char*)this->test.title[this->state]);
}

void Detector::displayName(void)
{
  this->display(this->tagName.x,this->tagName.y,(const char*)this->test.name);
}

void Detector::displayType(void)
{
  Info info;
  this->display(this->tagType.x,this->tagType.y,info.toString(this->test.type));
}

void Detector::displayFig(void)
{
  uint8 cnt = 7;
  LCD1602_Char(15,0,RU);
  LCD1602_Char(15,1,RD);
  LCD1602_Char(7,0,LU);
  LCD1602_Char(7,1,LD);
  while(cnt--)
  {
    if(this->test.pin[6-cnt]==false)
      LCD1602_Char(14-cnt,1,ED);
    else
      LCD1602_Char(14-cnt,1,D);
    
    if(this->test.pin[cnt+9]==false)
      LCD1602_Char(14-cnt,0,EU);
    else
      LCD1602_Char(14-cnt,0,U);
  }
}

void Detector::displayResult(void)
{

}

void Detector::displayText(void)
{
  switch(this->state){
    case __AutoTest__:  this->display(this->tagText.x,this->tagText.y,"Press <test> ");    break;
    case __StandBy__:   this->display(this->tagText.x,this->tagText.y,"<A>=auto <B>=man"); break;
    default: return;
  }
}

void Detector::display(uint8 x,uint8 y, const char* str)
{
  uint8 cursor;
  cursor = LCD1602_Str(x,y,str);
  LCD1602_CleanLine(cursor,y);
}

void Detector::led(void)
{
  uint8 cnt = sizeof(this->test.index)/sizeof(*(this->test.index));
  bool run,err;
  run = OFF;err = ON;
  while(cnt--)
  {
    if(*(this->test.index)!=0)
    {
      run = ON;
      err = OFF;
      break;
    }
  }
  RUN(run);
  ERR(err);
}

void Detector::led(uint8 stat)
{
  if(stat==OFF){
    RUN(OFF);
    ERR(OFF);
  }
}

void Detector::clearScreen(void)
{
  LCD1602_CleanScreen();
}

void Detector::scanfName(void)
{
  static string buffer;
  string buf74("74XX___");
  //string bufCD("CD____");
  const uint8 buf_head = buf74.find('_');
  uint8 cnt            = buf_head;
  char key;
  __disable_irq();
  this->display(0,1,buf74.c_str());
  while(cnt<buf74.size()&&!GET_TestKey()){
    if(KEY_DETECTED){
      key = GET_Keyboard();
      switch(key){
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':buf74.replace(buf74.begin()+cnt, buf74.end()-buf74.size()+cnt+1, 1, key);
                   cnt++;
                   break;
          case 'A':
          case 'B':
          case 'C':
          case 'D':break;

          case '*':
          case '#':if(cnt>buf_head){
                     --cnt;
                     buf74.replace(buf74.begin()+cnt, buf74.end()-buf74.size()+cnt+1, 1, '_');
                   }
                   break;
          
      }
      this->display(0,1,(const char*)buf74.c_str());
    }
  }
  buffer = buf74.substr(0,buf74.find('_'));
  this->test.name = (Name)buffer.c_str();
  
  NVIC_SetPriority(PORTE_IRQn, 1U);
  NVIC_EnableIRQ(PORTE_IRQn);
  NVIC_SetPriority(PORTA_IRQn, 1U);
  NVIC_EnableIRQ(PORTA_IRQn);
  __enable_irq();
}

Test::Test(){}
Test::~Test(){}

void Test::reset(void)
{
  this->dir_flag  = false;
  this->type_flag = false;
  this->name_flag = false;
  this->pin_dir   = 0xffff;
  this->type      = unknown;
  this->name      = (char*)"N/A";
  this->init_flag = true;
}

bool Test::ioPort(void)
{
  uint32 send = 0;
  uint32 read = 0;
  uint32 dir  = 0;

  for(send=0;send<=0XFFFF;send++)
  {
    PTD->PDOR = send;
    systick_delay(10);
    read  = (uint8)(PTB->PDIR);
    read |= (PTE->PDIR<<8);
    dir  |= send^read;
  }
  this->pin_dir = dir;
  this->dir_flag = true;
  return true;
}

bool Test::checkPort(void)
{
  bool isFinished = false;
  switch(this->type){
    case logic_gate:      this->checkGate();           isFinished = true;  break;
    case encoder:         this->checkEncoder();        isFinished = true;  break;
    case decoder:         this->checkDecoder();        isFinished = true;  break;
    case flip_flop:       this->checkFlipFlop();       isFinished = true;  break;
    case comparator:      this->checkComparator();     isFinished = true;  break;
    case multiplexer:     this->checkMultiplexer();    isFinished = true;  break;
    case demultiplexer:   this->checkDeMultiplexer();  isFinished = true;  break;
    case tri_state:       this->checkTriState();       isFinished = true;  break;
    case shift_reg:       this->checkShiftReg();       isFinished = true;  break;
    case serial_parallel: this->checkSPConvertor();    isFinished = true;  break;
    case unknown:         this->checkAll();            isFinished = true;  break;
    default:              isFinished = false;
  }
  return isFinished;
}

bool Test::checkGate(void)
{
  bool isFinished        = true;
  uint8  cnt             = 0;
  uint16 read            = 0;
  const Index  baseIndex = this->index[logic_gate];
  uint16       shift     = 0;
  if(baseIndex == 0)
    isFinished = false;
  memset(this->pin,1,sizeof(this->pin));
  
  while(GATE_KEYs[baseIndex-shift][cnt+1]!='$'){
    if(GATE_KEYs[baseIndex-shift][cnt+1]=='?'){
      shift++;
      cnt = 0;
      continue;
    }
    SEND_WORD(GATE_KEYs[baseIndex-shift][++cnt]);
    read  = (uint8)(PTB->PDIR&0x000000FF);
    read |= (PTE->PDIR<<8);
    for(int i=0;i<SUPPORT_MAX_PINs;i++){
      if((1<<i)&((read&GATE_ACKs[baseIndex-shift][0])^(GATE_ACKs[baseIndex-shift][cnt]&GATE_ACKs[baseIndex-shift][0])))
        this->pin[i] = false; // bad pin
    }
  }
  return isFinished;
}

bool Test::checkEncoder(void){return 0;}
bool Test::checkDecoder(void){return 0;}
bool Test::checkFlipFlop(void){return 0;}
bool Test::checkComparator(void){return 0;}
bool Test::checkMultiplexer(void){return 0;}
bool Test::checkDeMultiplexer(void){return 0;}
bool Test::checkTriState(void){return 0;}
bool Test::checkShiftReg(void){return 0;}
bool Test::checkSPConvertor(void){return 0;}

bool Test::checkAll(void)
{
  if(this->checkEncoder())        return true;
  if(this->checkDecoder())        return true;
  if(this->checkFlipFlop())       return true;
  if(this->checkComparator())     return true;
  if(this->checkMultiplexer())    return true;
  if(this->checkDeMultiplexer())  return true;
  if(this->checkTriState())       return true;
  if(this->checkShiftReg())       return true;
  if(this->checkSPConvertor())    return true;
  return false;
}

bool Test::findType(void)
{
  if(this->dir_flag == false)
  	return false;

  if(isGate())                this->type = logic_gate;
  else if(isEncoder())        this->type = encoder;
  else if(isDecoder())        this->type = decoder;
  else if(isFlipFlop())       this->type = flip_flop;
  else if(isComparator())     this->type = comparator;
  else if(isMultiplexer())    this->type = multiplexer;
  else if(isDeMultiplexer())  this->type = demultiplexer; 
  else if(isTriState())       this->type = tri_state;
  else if(isShiftReg())       this->type = shift_reg;
  else if(isSPConvertor())    this->type = serial_parallel;
  else                        this->type = unknown;
  this->type_flag = true;
  return true;
}

bool Test::isGate(void)
{
  uint8 cnt    = sizeof_IO__GATE();
  bool  isGate = false;
  while(cnt--)
  {
    if(IO_14PIN(this->pin_dir)==IO__GATE[cnt])
    {
      isGate = true;
      break;
    }
  }
  return isGate;
}

bool Test::isEncoder(void){return 0;}
bool Test::isDecoder(void){return 0;}
bool Test::isFlipFlop(void){return 0;}
bool Test::isComparator(void){return 0;}
bool Test::isMultiplexer(void){return 0;}
bool Test::isDeMultiplexer(void){return 0;}
bool Test::isTriState(void){return 0;}
bool Test::isShiftReg(void){return 0;}
bool Test::isSPConvertor(void){return 0;}

bool Test::findName(void)
{
  uint16 index;
  Info info;
  if(this->type_flag == false)
    return false;

  memset(this->index,0,sizeof(this->index));  // Clear the information
  if(this->type==logic_gate)
  {
    index = this->searchGate();
    this->index[logic_gate] = index;          // Load the information
    this->name = info.toName(this->index);    // Convert the information
    this->type = info.toType(this->index);
  }
  return true;
}

uint8 Test::searchGate(void)
{
  uint8_t   cnt   = 0;
  uint8_t   shift = 0; 
  uint16_t  read;
  uint16_t const*  base  = GATE_BASEs+sizeof_GATE_BASEs()-1;
  while(*base != IDX__NULL)
  {
  	while(GATE_KEYs[*(base-shift)][cnt+1]!='$')
    {
      if(GATE_KEYs[*(base-shift)][cnt+1]=='?')
      {
      	shift++;
      	cnt = 0;
      	continue;
      }
      cnt++;
      SEND_WORD(GATE_KEYs[*(base-shift)][cnt]);
      read  = (uint8)(PTB->PDIR&0x000000FF);
      read |= (PTE->PDIR<<8);
      if(  (read&GATE_ACKs[*(base-shift)][0]) != (GATE_ACKs[*(base-shift)][cnt]&GATE_ACKs[*(base-shift)][0])  )
      {
        cnt   = 0;
        base--;
        shift = 0;
        break;
      }
    }
    if(cnt != 0)  // Matched logic gate is found!  
      break;	
  }
  return (*base); // Index/Base: 0 is NULL(not found).
}


System::System():mcgout_clk_mhz(100),core_clk_mhz(100),bus_clk_mhz(100)
{
  this->getClock();
}

System::~System()
{
  while(1);//System halted
}

void System::init(void)
{
  key_board_Init();
  KEYs_Init();
  LED_Init();
  LCD1602_Init();
  LCD1602_ImportGraph();
}

void System::irq_setting(void)
{
  NVIC_SetPriority(PORTE_IRQn, 1U);
  NVIC_EnableIRQ(PORTE_IRQn);
  NVIC_SetPriority(PORTA_IRQn, 1U);
  NVIC_EnableIRQ(PORTA_IRQn);
  __enable_irq();
}

void System::getClock(void)
{
  this->mcgout_clk_mhz = EX_REF_CLK * ((MCG->C6 & MCG_C6_VDIV0_MASK) + 24) / ((MCG->C5 & MCG_C5_PRDIV0_MASK) + 1);
  this->core_clk_mhz = mcgout_clk_mhz / ((SIM->CLKDIV1 >> SIM_CLKDIV1_OUTDIV1_SHIFT) + 1);
  this->bus_clk_mhz = mcgout_clk_mhz / (((SIM->CLKDIV1 >> SIM_CLKDIV1_OUTDIV2_SHIFT) & 0x0f) + 1);
}

void System::taskAllocate(void (*handler)(void))
{
  if(handler == PORTA_IRQHandler){
    if(GET_TestKey()){

      RECORD_STATE(detector_cur);
      if(CURRENT_STATE(detector_cur) == __ShowResult__||CURRENT_STATE(detector_cur) == __AutoTest__)
        NEW_STATE(detector_cur,__AutoTesting__);
    }
  }
  else if(handler == PORTE_IRQHandler){
    RECORD_STATE(detector_cur);
    char key = GET_Keyboard();
    switch(key){
      case 'A':NEW_STATE(detector_cur,__AutoTest__);   break;
      case 'B':NEW_STATE(detector_cur,__ManTest__ );   break;
      case 'C':break;
      case 'D':break;
      case '*':NEW_STATE(detector_cur,__StandBy__ );   break;
      default:return;
    }
  }
}

void System::regDetector(Detector* p)
{
  this->detector_cur = p;
}

void System::mode(SysMode mode)
{
  __disable_irq();
}

