/******************************************************************************
 * File: ./COM.h
 ******************************************************************************/
namespace COM
{
    struct
    {
        const int
            refresh_rate=       1000,
            baud_rate=          9600
            ;
    } env ;

    namespace Get
    {
        int Ram(void)
        {
            extern int __heap_start, *__brkval;
            int v;
            return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
        }
    }

    namespace Print
    {
        void Stats(void)
        {
            WindDirection::Print();
            WindSpeed::Print();
        }
        void Ram(void)
        {
            Serial.print("RAM = ");
            Serial.println(Get::Ram());
        }
    }

    void Init(void)
    {
        Serial.begin(env.baud_rate);
    }
}
