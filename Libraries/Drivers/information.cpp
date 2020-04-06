#include "information.h"
#include <iostream>
#include <string>
using namespace std;

Info::Info(){}
Info::~Info(){}

const char* Info::toString(Type type)
{
  char* str;
  switch((int)type)
  {
  	case logic_gate:      str = (char*)"Logic Gate";break;
  	case and_gate:        str = (char*)"AND";       break;
  	case or_gate:         str = (char*)"OR";        break;
  	case not_gate:        str = (char*)"NOT";       break;
  	case nand_gate:       str = (char*)"NAND";      break;
  	case nor_gate:        str = (char*)"NOR";       break;
  	case eor_gate:        str = (char*)"EOR";       break;
  	case encoder:         str = (char*)"ECoder";    break;
  	case decoder:         str = (char*)"DCoder";    break;
  	case flip_flop:       str = (char*)"F-Flop";    break;
  	case comparator:      str = (char*)"CMP";       break;
  	case multiplexer:     str = (char*)"MPlex";     break;
  	case demultiplexer:   str = (char*)"De-MPlex";  break;
  	case tri_state:       str = (char*)"Tri State"; break;
  	case shift_reg:       str = (char*)"Shift-Reg"; break;
  	case serial_parallel: str = (char*)"S-P COV";	  break;
    case counter:         str = (char*)"Counter";   break;
  	default:              str = (char*)"N/A";       break;
  	case unknown:         str = (char*)"Unknown";	  break;
  }
  return (const char*) str;
}

uint16 Info::toNum(Name name,uint8 head_length)
{
  string str(name);
  uint8 cnt   = str.size();
  uint16 num = 0;
  while(cnt-->head_length){
    num += (str.at(cnt)-ASCII_SHIFT)<<((str.size()-cnt-1)<<2);
  }
  return num;
}

Index Info::toIndex(Name name)
{
  string str(name);
  Index index = 0xffff;
  uint16 id = get74XX___(name);
  switch(id){
    case 0x00:  index = IDX__74XX00;break;
    case 0x02:  index = IDX__74XX02;break;
    case 0x03:  index = IDX__74XX03;break;
    case 0x04:  index = IDX__74XX04;break;
    case 0x05:  index = IDX__74XX05;break;
    case 0x08:  index = IDX__74XX08;break;
    case 0x09:  index = IDX__74XX09;break;
    case 0x10:  index = IDX__74XX10;break;
    case 0x14:  index = IDX__74XX14;break;
    case 0x20:  index = IDX__74XX20;break; 
    /* ... */
    case 0x125: index = IDX__74XX125;break;
    case 0x164: index = IDX__74XX164;break;
    case 0x393: index = IDX__74XX393;break;
    default : index = 0xffff;break;
  }
  return index;
}

Type Info::toType(Name name)
{
  string str(name);
  Type type = unknown;
  uint16 id = get74XX___(name);
  switch(id){
    case 0x00: //__74XX00;
    case 0x02: //__74XX02;
    case 0x03: //__74XX03;
    case 0x04: //__74XX04;
    case 0x05:
    case 0x08: //__74XX08;
    case 0x09: //__74XX09;
    case 0x10:
    case 0x14:
    case 0x20: //__74XX20;
    case 0x21: //__74XX21;
    case 0x27: //__74XX27;
    case 0x28: //__74XX28;
    case 0x30: //__74XX30;
    case 0x32: //__74XX32;
    case 0x38: //__74XX38;
    case 0x51: //__74XX51;
    case 0x86: //__74XX86;
    case 0x136://__74XX136;
               type = logic_gate; break;
    
    /* ... */
    case 0x164:
               type = serial_parallel; break;
    case 0x125:
               type = tri_state;  break;
    case 0x393:
               type = counter;    break;

    default:   type = unknown;    break; 
  }

  return type;
}

Type Info::toType(Index* index)
{
  Type type;
  switch(index[logic_gate]){
    case IDX__LOGIC_GATE:   break;
    case IDX__74XX00:  type = nand_gate; return type;
    case IDX__74XX02:  type = nor_gate;  return type;
    case IDX__74XX03:  type = nand_gate; return type;
    case IDX__74XX04: 
    case IDX__74XX05:  type = not_gate;  return type;
    case IDX__74XX08: 
    case IDX__74XX09:  type = and_gate;  return type;
    case IDX__74XX10:  type = nand_gate; return type;
    case IDX__74XX14:  type = not_gate;  return type;
    case IDX__74XX20:  type = and_gate;  return type;
  }
  switch(index[serial_parallel]){
    case IDX__SERIALPARALLEL:break; 
    case IDX__74XX164: type = serial_parallel;return type;
  }
  switch(index[tri_state]){
    case IDX__TRISTATE:break;
    case IDX__74XX125: type = tri_state;return type;
  }
  switch(index[counter]){
    case IDX__COUNTER:      break;
    case IDX__74XX393: type = counter;  return type;
  }
  type = unknown;  return type;
}

Name Info::toName(Index* index)
{
  Name name;
  switch(index[logic_gate]){
    case IDX__LOGIC_GATE:   break;
    case IDX__74XX00:  name = (char*)"74XX00/03"; return name;
    case IDX__74XX02:  name = (char*)"74XX02";    return name;
    case IDX__74XX03:  name = (char*)"74XX00/03"; return name;
    case IDX__74XX04:
    case IDX__74XX05:  name = (char*)"74XX04/05"; return name;
    case IDX__74XX08:  
    case IDX__74XX09:  name = (char*)"74XX08/09"; return name;
    case IDX__74XX10:  name = (char*)"74XX10";    return name;
    case IDX__74XX14:  name = (char*)"74XX14";    return name;
    case IDX__74XX20:  name = (char*)"74XX20";    return name;
  }
  switch(index[encoder]){
    case 0:  break;
    case 1:  name = (char*)"74xx";return name;
  }
  switch(index[serial_parallel]){
    case IDX__SERIALPARALLEL: break;
    case IDX__74XX164:  name = (char*)"74XX164";  return name;
  }
  switch(index[tri_state]){
    case IDX__TRISTATE:break;
    case IDX__74XX125:  name = (char*)"74XX125";  return name;
  }

  switch(index[counter]){
    case IDX__COUNTER:  break;
    case IDX__74XX393:  name = (char*)"74XX393";  return name;
  }
  name = (char*)"N/A"; return name;
}

uint16 Info::get74XX___(Name name)
{
  return this->toNum(name,HEAD_74XX);
}

uint16 Info::getCD____(Name name)
{
  return this->toNum(name,HEAD_CD);;
}





