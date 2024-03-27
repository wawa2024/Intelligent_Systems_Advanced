/******************************************************************************
 * File: ./WindSpeed.h
 * Requires: Utils.h
 ******************************************************************************/
namespace WindSpeed
{
    constexpr struct 
    {
        uint8_t
            input=      2
            ;
    } pin ;

    constexpr uint8_t 
        t_size=     10
        ;
    volatile unsigned long
        t_begin=    0,
        t_end=      0
        ;
    volatile unsigned long
        t_array[t_size] = {}
        ;

    void InterruptServiceRoutine(void)
    {
        static volatile int i = 0;

        t_begin = t_end;
        t_end = millis();

        i = i < t_size ? i : 0;

        t_array[i++] = t_end - t_begin;
    }

    inline float Value(void)
    {
        float sum = 0;
        for(int i=0 ; i < t_size ; i++)
        {
           sum += millis2hz(t_array[i]) * 0.699 ;
           sum -= sum > 0 ? 0.24 : 0 ;
        }
        float&& average = sum / t_size;
        return average;
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        attachInterrupt(
            digitalPinToInterrupt(pin.input),
            InterruptServiceRoutine,
            RISING
        );
    }
}
