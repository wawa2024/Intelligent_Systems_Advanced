/******************************************************************************
 * File: ./LCD.h
 * Display: 20x4
 * Dependency: liquid-crystal
 ******************************************************************************/
#include <LiquidCrystal.h>

namespace LCD
{
    struct 
    {
        const int
            rs=         A0,
            rw=         A1,
            enable=     A2
            ;
        const int 
            d[4]=     { A3 , A5 , 1 , 0 }
            ;
    } pin ;

    struct
    {
        const int
            cols=       20,
            rows=       4
            ;
    } env ;

    LiquidCrystal* lcd = 00;

    void Init(void)
    {
        if(!lcd)
        {
            static LiquidCrystal dpy(
                        pin.rs,
                        pin.rw,
                        pin.enable,
                        pin.d[0],
                        pin.d[1],
                        pin.d[2],
                        pin.d[3]
                        );
            dpy.begin(env.cols,env.rows);
            dpy.noCursor();
            dpy.clear();
            lcd = &dpy;
        }
    }

    template<typename T> void Print(T a){ lcd -> print(a); }
    void Clear(){ lcd -> clear(); }
    void SetCursor(int col,int row){ lcd -> setCursor(col,row); }
    void Write(unsigned char c){ lcd -> write(c); }

    namespace Sily
    {
        void P(bool* p){ if(p) *p=true; }
        void G(bool& b, char& val, const int& k, bool* p)
        {
            if(b) if( val == k ) b = false , val--, P(p); else val++;
            else  if( val  < 0 ) b = true  , val++, P(p); else val--;
        }
    }

    namespace Draw 
    {
        void Alphabet(void)
        {
            char col=0, row=0, c = 'A';
            bool x = true, y = true, z = false;
            do {
                Clear(); SetCursor(col,row); Write(c); delay(250);
                c = ++c > 'Z' ? 'A' : c;
                Sily::G(x,col,env.cols,&z);
                if(z) z = false, Sily::G(y,row,env.rows,NULL);
            } while ( col != 0 && row != 0 );
        }

        void Stats(void)
        {
            Clear();
            Print("WindDirection:"); SetCursor(0,1);
            Print("  Value: "); Print(WindDirection::Value()); Print(" deg"); SetCursor(0,2);
            Print("WindSpeed:"); SetCursor(0,3);
            Print("  Value: "); Print(WindSpeed::Value()); Print(" m/s");
        }
    }
}
