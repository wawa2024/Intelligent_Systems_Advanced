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
            d[4]=     { A3 , A5 , 3 , 4 }
            ;
    } pin ;

    struct
    {
        const unsigned char 
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
        char col=0, row=0;
        bool x=true, y=true;
        char S(void){static char c='A'-1;return c=++c>'Z'?'A':c;}
        char I(bool& b,char& val){if(b)val++;else val--;return val;}
        void G(void){Clear();SetCursor(col,row);Write(S());delay(150);}
        void M(bool& b,char& val,unsigned char max,unsigned char i){
            static bool f=false;if(i){
                I(b,val);
                if(val==max)b=false,f=true;else if(val<0)b=true,f=true;
                if(f){f=false;I(b,val);M(y,row,env.rows,i-1);}
            }else I(x,col);}
        void A(void){do{G();M(x,col,env.cols,2);}while(!(col==0&&row==0));}
    }

    namespace Draw 
    {
        void Alphabet(void){Sily::A();}
        void Stats(void)
        {
            double wind_speed = WindSpeed::Value();
            int wind_direction = WindDirection::Value();
            static int direction = wind_direction;
            static double speed = wind_speed;
            static bool state = true;
           
           if( not state && not ( wind_direction == direction and speed == wind_speed ) )
                state = false;

            if(state)
            {
                Clear();
                Print("WindDirection:"); SetCursor(0,1);
                Print("  Value: "); Print(wind_direction); Print(" deg"); SetCursor(0,2);
                Print("WindSpeed:"); SetCursor(0,3);
                Print("  Value: "); Print(wind_speed); Print(" m/s");
                state = false;
            }
        }
    }
}
