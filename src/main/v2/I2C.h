/******************************************************************************
 * File: ./I2C.h
 * Dependency: Wire.h
 * Board: Arduino Nano
 * I2C Serial Data Line (SDA) pin: A4
 * I2C Serial Clock Line (SLC) pin: A5
 ******************************************************************************/

    /////////////////
    // I2C Handler //
    /////////////////

#include <Wire.h>

struct I2C
{
    struct {
        unsigned char 
            slave[1] = { 0x1 }
            ;
    } addr ;

    unsigned char buf[32] = {};

    I2C()
    {
        Wire.begin();
    }

} com ;
