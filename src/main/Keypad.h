/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1;

    volatile uint8_t keycode = 16;
    volatile float voltage = 0.0;

    constexpr struct {
        uint8_t input = A6;
    } pin ;

    constexpr struct {
        float 
            field[num_keys] = {
                      1.30  ,  1.50  ,  1.70  ,  1.90,
                      2.07  ,  2.30  ,  2.53  ,  2.77,
                      2.96  ,  3.22  ,  3.49  ,  3.77,
                      4.01  ,  4.32  ,  4.65  ,  5.00
            };
        float offset = 0.07; 
    } env ;

    struct Key { 
        const char* name; 
        void (*handler)(void); 
    };

    Key key[17] = {
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
        { "A" , NULL },
        { "@" , NULL }
    };

    inline void AttachKeyHandler( uint8_t i, void(*p)(void) ) 
    {
        key[i].handler=p;
    }

    #ifdef DEBUG
    inline void Debug(void)
    {
       Serial.print("Pin: "); Serial.print(pin.input); Serial.print(": ");
       Serial.print("{ ");
       Serial.print("Voltage: "); Serial.print( voltage ); 
       Serial.print(", ");
       Serial.print("Keycode: "); Serial.print( keycode );
       Serial.print(", ");
       Serial.print("Button: "); Serial.print( key[keycode-1].name );
       Serial.println(" }");
    }
    #endif

    void ScanKeys(void)
    {
        float tmp = 0 ;
        for( uint8_t i=0 ; i < 100 ; i++ ) 
            voltage = ( ( tmp = Voltage(pin.input) ) > voltage ? tmp : voltage );

        if( voltage < env.offset ) return;

        for( uint8_t i=0 ; i < num_keys ; i++ )
        {
            const float& f = env.field[i];
            float low = f - env.offset, high = f + env.offset;
            if( ( low < voltage ) and ( voltage < high ) )
            { 
                keycode = i + 1; 
                break; 
            }
        }
    }

    inline void Exec(void)
    {
        if(keycode)
        {
            Key& k = key[keycode-1];
            #ifdef DEBUG
            Debug();
            #endif
            if(k.handler) k.handler();
        }
        delay(hz2millis(1));
    }

    #define USE_TIMER_1 true
    #include <TimerInterrupt.h>
    inline void InitTimer(void)
    {
        ITimer1.init();
        if( ITimer1.attachInterruptInterval( hz2millis(15) , ScanKeys ) )
            Serial.print("ITimer1 ON"); 
        else
            Serial.println("ITimer1 ERROR");
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        InitTimer();
    }
}
