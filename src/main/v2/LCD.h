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
            rs=         A0,
            rw=         A1,
            enable=     A2
            ;
        const int 
            lcd[4]=     { A3 , A5 , A6, A7 }
            ;
    } pin ;

    LiquidCrystal* lcd;
    char charsize= 4;

    struct 
    {
        const int
            columns=    16,
            rows=       4
            ;
    } env ;

    LCD()
    {
        static const LiquidCrystal dpy(
                    pin.rs,
                    pin.rw,
                    pin.enable,
                    pin.lcd[0],
                    pin.lcd[1],
                    pin.lcd[2],
                    pin.lcd[3]
                    );
        lcd = &dpy;

        lcd -> begin(env.columns,env.rows,charsize);
        lcd -> noCursor();
        lcd -> print("LCD Initialized");
    }

    void print(char* s)
    {
        lcd -> print(s);
    }

    void alphabet()
    {
        char col=0, row=0;
        char c = 'A';
        for(int i=0 ; !( c > 'Z' ) ; c++ , i++ )
        {
            if( i == 16 )
            {
                lcd -> setCursor(0,++row);
                i=0;
            }
            lcd -> write(c);
        }
    }

    void clear()
    {
        lcd -> clear();
    }
} display ;

