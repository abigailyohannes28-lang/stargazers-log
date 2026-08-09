#include "RP.h"
#include <iostream>

int main()
{
    RP myRPclass;
    mraa_i2c_context fd = myRPclass.start_i2c_MaqueenPlus();

    int lineBits;

    int baseSpd = 60;
    int fastSpd = 80;
    int slowSpd = 10;
    int sharpTurnSpd = 5;

    int lapCount = 0;
    bool finishDetected = false;

    int lostCounter = 0;
    const int lostLimit = 200;

    std::cout << "Starting Task 5..." << std::endl;

    while (lapCount < 2)
    {
        lineBits = myRPclass.getLineBits(fd);

        if (lineBits == 0x00)
        {
            lostCounter++;

            myRPclass.motorControl(fd, rpLEFT, rpFORWARD, 60);
            myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, 60);

            if (lostCounter >= lostLimit)
            {
                std::cout << "Line lost for 2 seconds. Stopping program." << std::endl;
                break;
            }
        }
        else
        {
            lostCounter = 0;

            if (lineBits == 0x3F || lineBits == 0x1F || lineBits == 0x3E || lineBits == 0x1E)
            {
                if (!finishDetected)
                {
                    lapCount++;
                    finishDetected = true;
                    std::cout << "Lap: " << lapCount << std::endl;
                }

                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, baseSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, baseSpd);
            }
            else if (lineBits == 0x0C)
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, baseSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, baseSpd);
            }
            else if (lineBits == 0x08 || lineBits == 0x04)
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, slowSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, fastSpd);
            }
            else if (lineBits == 0x06 || lineBits == 0x02 || lineBits == 0x03)
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, sharpTurnSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, fastSpd);
            }
            else if (lineBits == 0x10 || lineBits == 0x08)
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, fastSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, slowSpd);
            }
            else if (lineBits == 0x18 || lineBits == 0x20 || lineBits == 0x30)
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, fastSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, sharpTurnSpd);
            }
            else
            {
                finishDetected = false;
                myRPclass.motorControl(fd, rpLEFT, rpFORWARD, baseSpd);
                myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, baseSpd);
            }
        }

        myRPclass.RP_wait(0.005);
    }

    myRPclass.motorControl(fd, rpLEFT, rpFORWARD, 0);
    myRPclass.motorControl(fd, rpRIGHT, rpFORWARD, 0);

    std::cout << "Program ended." << std::endl;
    return 0;
}