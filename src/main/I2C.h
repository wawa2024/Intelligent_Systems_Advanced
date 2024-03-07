/******************************************************************************
 * File: ./I2C.h
 * Dependency: Wire.h
 * Board: Arduino Nano
 * I2C Serial Data Line (SDA) pin: A4
 * I2C Serial Clock Line (SLC) pin: A5
 ******************************************************************************/
#include <Wire.h>

namespace I2C
{
    struct {
        unsigned char 
            slave[1] = { 0x1 }
            ;
    } addr ;

    unsigned char buf[32] = {};

    void Init(void)
    {
        Wire.begin();
    }
}
