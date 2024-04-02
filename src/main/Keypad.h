/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1;

    volatile uint8_t keycode = 16;
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
        Serial.print("Keypad::Exec "); 
        Serial.print(STRING_BRACKET_START);
        Serial.print("Pin: "); Serial.print(pin.input); Serial.print(": ");
        Serial.print(STRING_COMMA);
        Serial.print("Voltage: "); Serial.print( voltage ); 
        Serial.print(STRING_COMMA);
        Serial.print("Keycode: "); Serial.print( keycode );
        Serial.print(STRING_COMMA);
        Serial.print("Button: "); Serial.print( key[keycode-1].name );
        Serial.println(STRING_BRACKET_END);
    }
#endif

    void ScanKeys(void)
    {
        volatile float tmp = 0 , volt = 0;

        for( uint8_t i=0 ; i < 100 ; i++ ) 
        {
            tmp = Voltage(pin.input);
            volt = tmp > volt ? tmp : volt ;
        }

        if( volt < 1 ) return;

        for( uint8_t i=0 ; i < num_keys ; i++ )
        {
            const float& f = env.field[i];
            volatile float low = f - env.offset, high = f + env.offset;
            if( ( low < volt ) and ( volt < high ) )
            { 
                keycode = i + 1; 
                break; 
            }
        }

        voltage = volt;
    }

    void Exec(void)
    {
        if(keycode)
        {
        #ifdef DEBUG_KEYPAD
            msgSerial(STRING_Function,STRING_call);
            Debug();
        #endif
            if(keycode) key[keycode-1].handler();
        }
    }

#ifdef TIMER
    #define USE_TIMER_1 true
    #include <TimerInterrupt.h>

    inline void InitTimer(void)
    {
        ITimer1.init();
        if( ITimer1.attachInterruptInterval( hz2millis(15) , ScanKeys ) )
            Serial.println("ITimer1 ON"); 
        else
            Serial.println("ITimer1 ERROR");
    }
#else
    #include <avr/interrupt.h>

    inline void EnableAC(void)
    { 
        ACSR = 0b01000000; 
        Wait(3);
        ACSR|= 0b00001000;
    }

    ISR(ANALOG_COMP_vect)
    {
    #ifdef DEBUG_KEYPAD
        Serial.println("ANALOG_COMP_vect triggered");
        Debug();
    #endif
        ScanKeys(); 
    }
#endif

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    #ifdef TIMER
        InitTimer();
    #else
        EnableAC();
    #endif
    #ifdef DEBUG_KEYPAD
        msgSerial(STRING_Keypad,STRING_initialized);
    #endif
    }
}
