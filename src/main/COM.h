/******************************************************************************
 * File: ./COM.h
 ******************************************************************************/
namespace COM
{
    constexpr struct { uint16_t baud_rate = 9600; } env;

    inline void Init(void)
    { 
        Serial.begin(env.baud_rate); 
    }
}
