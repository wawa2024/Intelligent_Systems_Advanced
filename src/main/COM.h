/******************************************************************************
 * File: ./COM.h
 ******************************************************************************/
namespace COM
{
    constexpr struct { uint16_t refresh_rate = 1000, baud_rate = 9600; } env;

    inline void Init(void)
    { 
        Serial.begin(env.baud_rate); 
    }
}
