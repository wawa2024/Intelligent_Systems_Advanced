/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1, def_key = 14;

    volatile uint8_t keycode = def_key;
    void Default(void) { keycode = def_key; }

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

    #ifdef DEBUG
        Debug();
    #endif

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

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    }
}
