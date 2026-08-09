#include "RP.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    RP myRPclass;
    mraa_i2c_context fd = myRPclass.start_i2c_MaqueenPlus();

    int leftSpd = 100;
    int rightSpd = 100;

    float leftDist, rightDist;
    int lineBits;

    int colors[7] = {rpRED, rpGREEN, rpBLUE, rpYELLOW, rpPINK, rpCYAN, rpWHITE};
    int used[7] = {0};
    int idx, count = 0;

    std::srand(std::time(0));

    std::cout << "Starting Task 4...\n";

    myRPclass.setRGB(fd, rpBOTH, rpRED);
    myRPclass.RP_wait(0.5);
    myRPclass.setRGB(fd, rpBOTH, rpGREEN);
    myRPclass.RP_wait(0.5);
    myRPclass.setRGB(fd, rpBOTH, rpBLUE);
    myRPclass.RP_wait(0.5);
    myRPclass.setRGB(fd, rpBOTH, rpYELLOW);
    myRPclass.RP_wait(0.5);
    myRPclass.setRGB(fd, rpBOTH, rpPINK);
    myRPclass.RP_wait(0.5);
    myRPclass.clearRGB(fd, rpBOTH);

    lineBits = myRPclass.getLineBits(fd);
    std::cout << "Line bits: " << lineBits << std::endl;

    myRPclass.clearDistance(fd, rpLEFT);
    myRPclass.clearDistance(fd, rpRIGHT);

    myRPclass.motorControl(fd, rpLEFT, rpFORWARD, leftSpd);
    myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, rightSpd);
    myRPclass.RP_wait(2.0);
    myRPclass.motorControl(fd, rpLEFT, rpFORWARD, 0);
    myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, 0);

    leftDist = myRPclass.getDistance(fd, rpLEFT);
    rightDist = myRPclass.getDistance(fd, rpRIGHT);

    std::cout << "Left distance: " << leftDist << std::endl;
    std::cout << "Right distance: " << rightDist << std::endl;

    myRPclass.motorControl(fd, rpLEFT, rpFORWARD, leftSpd);
    myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, rightSpd);

    while (count < 5)
    {
        idx = std::rand() % 7;

        if (used[idx] == 0)
        {
            used[idx] = 1;
            myRPclass.setRGB(fd, rpBOTH, colors[idx]);
            myRPclass.RP_wait(0.5);
            count++;
        }
    }

    myRPclass.motorControl(fd, rpLEFT, rpFORWARD, 0);
    myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, 0);
    myRPclass.clearRGB(fd, rpBOTH);

    std::cout << "Task 4 complete.\n";
    return 0;
}