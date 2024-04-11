/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: TimerInterrupt.h
 ******************************************************************************/
namespace Keypad
{
    constexpr uint8_t num_keys = 4 * 4, bus_size = 1, def_key = KEY(D);

    volatile uint8_t keycode = def_key;
    inline void Default(void) { keycode = def_key; }

    constexpr struct { uint8_t input = A6; } pin;

    struct {
        uint16_t field[num_keys] = {
                      130  ,  150  ,  170  ,  190,
                      207  ,  230  ,  253  ,  277,
                      296  ,  322  ,  349  ,  377,
                      401  ,  432  ,  465  ,  500
            };
        uint8_t offset = 007; 
    } env;

    void ScanKeys(void)
    {
        volatile float tmp = 0 , volt = 0;

        for( uint8_t i=0 ; i < 100 ; i++ ) 
        {
            tmp = Voltage(pin.input);
            volt = tmp > volt ? tmp : volt;
        }

        for( uint8_t i = 0 ; i < num_keys ; i++ )
        {
            uint16_t  tmp  = env.field[i];
            uint16_t  val  = volt * 100;
            uint16_t  low  = tmp - env.offset;
            uint16_t  high = tmp + env.offset;

            if( ( low < val ) and ( val < high ) )
            { 
                keycode = i + 1; 
                break; 
            }
        }
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    }
}
