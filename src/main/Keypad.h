/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1, defkey = 14;

    volatile uint8_t keycode = defkey;
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
    #ifdef DEBUG_KEYPAD
        const char* name; 
    #endif
        void (*handler)(void); 
    };

    Key key[16] = {
    #ifdef DEBUG_KEYPAD
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

    inline void Default(void)
    {
        keycode = defkey;
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
        volatile float tmp = 0 , volt = 0;

        for( uint8_t i = 0 ; i < 100 ; i++ ) 
        {
            tmp = Voltage(pin.input);
            volt = tmp > volt ? tmp : volt;
        }

        if( volt < 1 ) return;

        for( uint8_t i = 0 ; i < num_keys ; i++ )
        {
            tmp = env.field[i];

            float low = tmp - env.offset;
            float high = tmp + env.offset;

            if( ( low < volt ) and ( volt < high ) )
            { 
                keycode = i + 1; 
                break; 
            }
        }

        voltage = volt;
    }

    inline void EnableAC(void)
    { 
        ACSR = 0b01000000; 
        Wait(1);
        ACSR|= 0b00001000;
    }

    ISR(ANALOG_COMP_vect)
    {
        ScanKeys(); 
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
        EnableAC();
    }
}
