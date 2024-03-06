/******************************************************************************
 * File: ./LCD.h
 * Display: 16x4
 * Dependency: liquid-crystal
 ******************************************************************************/

    /////////////////
    // LCD Display //
    /////////////////

#include <LiquidCrystal.h>

struct Display
{
    struct 
    {
        const int
            rs=         12,
            enable=     11
            ;
        const int 
            lcd[4]=     { 3, 4, 5, 6 }
            ;
    } pin ;

    LiquidCrystal* lcd;

    struct 
    {
        const int
            columns=    16,
            rows=       2
            ;
    } env ;

    LCD()
    {
        static const LiquidCrystal dpy(
                    pin.rs,
                    pin.enable,
                    pin.lcd[0],
                    pin.lcd[1],
                    pin.lcd[2],
                    pin.lcd[3]
                    );
        lcd = &dpy;

        lcd -> begin(env.columns,env.rows);
        lcd -> noCursor();
        lcd -> print("LCD Initialized");
    }

} display ;

