/******************************************************************************
 * File: ./LCD.h
 * Dependencies: LiquidCrystal.h
 ******************************************************************************/
#include <LiquidCrystal.h>

namespace LCD
{
    const struct {
        uint8_t rs = A0, rw = A1, enable = A2;
        uint8_t d[4] = { A3 , A5 , 4 , 5 };
    } pin;

    const struct { uint8_t cols = 20, rows = 4; } env;

    LiquidCrystal* lcd = 0;

    template<typename T> inline void Print(T a){ lcd -> print(a); }
    inline void Clear() { lcd -> clear(); }
    inline void SetCursor(int col,int row){ lcd -> setCursor(col,row); }
    inline void Write(uint8_t c){ lcd -> write(c); }
    inline void Flush(void){ Print(buf); }

    inline void Init(void)
    {
        if(!lcd)
        {
            static LiquidCrystal dpy( pin.rs
                        , pin.rw
                        , pin.enable
                        , pin.d[0]
                        , pin.d[1]
                        , pin.d[2]
                        , pin.d[3]
                        );
            dpy.begin(env.cols,env.rows);
            dpy.noCursor();
            dpy.clear();
            lcd = &dpy;
        }
    #ifdef DEBUG
        Serial.println(F("LCD initialized"));
    #endif
        Clear(); Print(F("EXECUTING BOOT"));
    }
}
