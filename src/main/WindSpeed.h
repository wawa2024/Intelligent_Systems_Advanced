/******************************************************************************
 * File: ./WindSpeed.h
 * Requires: Utils.h
 ******************************************************************************/
#include <TimerOne.h>

namespace WindSpeed
{
    constexpr struct { uint8_t input = 2; } pin;

    constexpr uint8_t t_size = 10;
    volatile uint16_t spins = 0;
    volatile uint16_t t_array[t_size] = {};

    volatile float max = 0, mean = 0, min = 0;

    void InterruptServiceRoutine0(void)
    {
        spins++;
    }

    void InterruptServiceRoutine1(void)
    {
        static uint8_t i = 0;
        i = i < 10 ? i : 0;
        t_array[i] = spins;
        spins = 0;
        i++;
    }

    void Update(void)
    {
        uint16_t sum = 0, t_max = 0 , t_min = 0xffff;

        for(int i=0 ; i < t_size ; i++)
        {
           uint16_t tmp = t_array[i];
           sum += tmp;
           t_max = t_max < tmp ? tmp : t_max;
           t_min = t_min > tmp ? tmp : t_min;
        }

        mean    = sum / t_size * 0.699;
        max     = t_max        * 0.699;
        min     = t_min        * 0.699;
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        attachInterrupt( digitalPinToInterrupt(pin.input)
            , InterruptServiceRoutine0
            , RISING
            );
        Timer1.initialize(1000000);
        Timer1.attachInterrupt(InterruptServiceRoutine1);
    }
}
