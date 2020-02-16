#include "LCD1602.h"
#include "IC_Test.h"
#include "information.h"
#include "headfiles.h"
#ifndef _DEBUG_H
#define _DEBUG_H

class Debug
{
private:
  Info info;
public:
  void ioPort(void);
  void ioPort(const Detector& p);
  void findType(const Detector& p);
  void findName(const Detector& p);
  void sendVector(uint16_t vector);
  uint16_t recvVector(void);
};


#endif