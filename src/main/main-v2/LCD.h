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
            lcd[4]=     { A3 , A5 , 4, 5 }
            ;
    } pin ;

    LiquidCrystal* lcd;

    struct 
    {
        const int
            columns=    20,
            rows=       4,
            charsize=   4
            ;
    } env ;

    void Init(void)
    {
        static LiquidCrystal dpy(
                    pin.rs,
                    pin.rw,
                    pin.enable,
                    pin.lcd[0],
                    pin.lcd[1],
                    pin.lcd[2],
                    pin.lcd[3]
                    );
        lcd = &dpy;
        
        dpy . begin(env.columns,env.rows,env.charsize);
        lcd -> noCursor();
        dpy . clear();
        //dpy . print("LCD Initialized");
    }

    void print(char* s)
    {
        lcd -> print(s);
    }

    void alphabet()
    {
        static char col=0, row=0;
        static char c = 'A';

        lcd -> write(c++);
        for( ; col < env.columns ; )
        {
            delay(1000);
            c = c > 'Z' ? 'A' : c;
            //lcd -> setCursor(col,row);
            //lcd -> write(' ');
            lcd -> clear();
            lcd -> setCursor(++col,row);
            lcd -> write(c++);
        }
        row++;
        lcd -> write(c++);
        for( ; ! ( col < 0 ) ; )
        {
            delay(1000);
            c = c > 'Z' ? 'A' : c;
            
            //lcd -> setCursor(col,row);
            //lcd -> write(' ');
            lcd -> clear();
            lcd -> setCursor(--col,row);
            lcd -> write(c++);
        }
        row--; col++;
    }

    void clear()
    {
        lcd -> clear();
    }
} display ;

