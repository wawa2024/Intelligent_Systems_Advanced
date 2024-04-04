/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1;

    volatile uint8_t keycode = 14;
    volatile float voltage = 0.0;

    constexpr struct { uint8_t input = A6; } pin;

    constexpr struct {
        float field[num_keys] = {
                      1.30  ,  1.50  ,  1.70  ,  1.90,
                      2.07  ,  2.30  ,  2.53  ,  2.77,
                      2.96  ,  3.22  ,  3.49  ,  3.77,
                      4.01  ,  4.32  ,  4.65  ,  5.00
            };
        float offset = 0.07; 
    } env;

    struct Key { 
    #ifdef DEBUG
        const char* name; 
    #endif
        void (*handler)(void); 
    };

    Key key[16] = {
    #ifdef DEBUG
        { "*" , NULL },
        { "7" , NULL },
        { "4" , NULL },
        { "1" , NULL },
        { "0" , NULL },
        { "8" , NULL },
        { "5" , NULL },
        { "2" , NULL },
        { "#" , NULL },
        { "9" , NULL },
        { "6" , NULL },
        { "3" , NULL },
        { "D" , NULL },
        { "C" , NULL },
        { "B" , NULL },
        { "A" , NULL }
    #else
    #endif
    };

    inline void AttachKeyHandler( uint8_t i, void(*p)(void) ) 
    {
        key[i].handler=p;
    }

#ifdef DEBUG_KEYPAD
    void Debug(void)
    {
        Serial.print(F("Voltage = ")); Serial.print( voltage ); 
        Serial.print(F(", Keycode = ")); Serial.print( keycode ); 
        Serial.print(F(", Button = ")); Serial.println( key[keycode-1].name );
    }
#endif

    void ScanKeys(void)
    {
        static unsigned long t_begin = 0, t_end = 0;
        volatile float tmp = 0 , volt = 0;

        while( ( ( t_end = millis() ) - t_begin ) < seconds2millis(1) )
        {
            for( uint8_t i=0 ; i < 100 ; i++ ) 
            {
                tmp = Voltage(pin.input);
                volt = tmp > volt ? tmp : volt;
            }

            if( volt < 1 ) continue;

            for( uint8_t i = 0 ; i < num_keys ; i++ )
            {
                float low = env.field[i] - env.offset;
                float high = env.field[i] + env.offset;

                if( ( low < volt ) and ( volt < high ) )
                { 
                    keycode = i + 1; 
                    break; 
                }
            }

            voltage = volt;
        }

        t_begin = t_end;
    }

    void Exec(void)
    {
        if(keycode)
        {
        #ifdef DEBUG_KEYPAD
            Debug();
        #endif
            key[keycode-1].handler();
        }
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    }
}
