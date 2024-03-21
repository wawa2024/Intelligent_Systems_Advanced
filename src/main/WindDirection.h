/******************************************************************************
 * File: ./WindDirection.h
 * Dependency: ./Utils.h
 ******************************************************************************/
namespace WindDirection 
{
    struct
    {
        const int
            input=  A7
            ;
    } pin ;

    inline double mapd(double x, double in_min, double in_max, double out_min, double out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    inline int Value(void)
    {
        constexpr int Max_ADC_Ret = 1023;

        double voltage = (double)analogRead(pin.input) * 
                         ( 
                            (double)ref_voltage / 
                            (double)Max_ADC_Ret 
                         );

        return mapd(voltage, 0 , 3.8 , 0 , 359 );
    }

    #ifdef LEAN
    #else
    inline void Print(void)
    {
        Serial.print("Wind Direction: ");
        Serial.print(Value());
        Serial.println(" deg");
    }
    #endif

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
    }
}
