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

    LiquidCrystal dpy( pin.rs
                , pin.rw
                , pin.enable
                , pin.d[0]
                , pin.d[1]
                , pin.d[2]
                , pin.d[3]
                );

    template<typename T> inline void Print(T a){ dpy.print(a); }
    inline void Print(float a, uint8_t i){ dpy.print(a,i); }
    inline void Clear() { dpy.clear(); }
    inline void SetCursor(int col,int row){ dpy.setCursor(col,row); }
    inline void Write(uint8_t c){ dpy.write(c); }

    inline void Init(void)
    {
        dpy.begin(env.cols,env.rows);
        dpy.noCursor();
        Clear();
        Print(F("EXECUTING BOOT"));
    }
}
