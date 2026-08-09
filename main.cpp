#include "RP.h"
#include <iostream>

int main()
{
    RP myRPclass;
    mraa_i2c_context fd = myRPclass.start_i2c_MaqueenPlus();

    std::cout << "Forward rotation test start...\n";
    myRPclass.motorControl(fd, rpBOTH, rpFORWARD, 100);
    myRPclass.RP_wait(1.5);
    myRPclass.motorControl(fd, rpBOTH, rpFORWARD, 0);
    std::cout << "Forward rotation test complete!\n";

    return 0;
}