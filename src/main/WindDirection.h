/******************************************************************************
 * File: ./WindDirection.h
 * Requires: Utils.h
 ******************************************************************************/
namespace WindDirection 
{
    constexpr struct
    {
        uint8_t
            input=  A7
            ;
    } pin ;

    inline float mapd(float x, float in_min, float in_max, float out_min, float out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    inline int Value(void)
    {
        return mapd( Voltage(pin.input) , 0 , 3.8 , 0 , 359 );
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    }
}
