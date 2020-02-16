
#include "headfiles.h"
#include "CHIPs_Lib.h"


Detector detector_NO1;
int main()
{
  $system$.init();
  $system$.regDetector(&detector_NO1);

  detector_NO1.init();
  while(1)
  {
    detector_NO1.main();
  }
}


