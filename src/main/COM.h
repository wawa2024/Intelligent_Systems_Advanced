/******************************************************************************
 * File: ./COM.h
 ******************************************************************************/
namespace COM
{
    constexpr struct
    {
        const int
            refresh_rate=       1000,
            baud_rate=          9600
            ;
    } env ;

    namespace Get
    {
        inline int Ram(void)
        {
            extern int __heap_start, *__brkval;
            int v;
            return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
        }
    }

    namespace Print
    {
        inline void Stats(void)
        {
            WindDirection::Print();
            WindSpeed::Print();
        }
        inline void Ram(void)
        {
            Serial.print("RAM = ");
            Serial.println(Get::Ram());
        }
    }

    inline void Init(void)
    {
        Serial.begin(env.baud_rate);
    }
}
