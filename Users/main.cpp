
#include "headfiles.h"
#include "CHIPs_Lib.h"

//If you have any, please list all and don't forget to regist it.
Detector detector_NO1;

int main()
{
  $system$.init();
  $system$.regDetector(&detector_NO1);
  detector_NO1.init();
  LED(OFF);
  $system$.selfLoopBack(&detector_NO1);
  while(1)
  {
    //detector_NO1.main();
  }
}


