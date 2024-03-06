/******************************************************************************
 * File: ./WindSpeed.h
 ******************************************************************************/
    ////////////////
    // Wind Speed //
    ////////////////

namespace WindSpeed
{
    struct 
    {
        const int
            input=      2
            ;
    } pin ;

    const int
        t_size=     10
        ;
    volatile unsigned long
        t_begin=    0,
        t_end=      0
        ;
    volatile unsigned long
        t_array[t_size] = {}
        ;

    void Interrupt(void)
    {
        static int i{0};

        t_begin = t_end;
        t_end = millis();

        i = i < t_size ? i : 0;

        t_array[i++] = t_end - t_begin;
    }

    double Millis2Time(unsigned long int t)
    {
        return 1000 / (double)t ;
    }

    double Average (void)
    {
        double tmp = 0;

        for(int i=0 ; i < t_size ; i++)
        {
           tmp += Millis2Time(t_array[i]) * 0.699 ;
           tmp -= tmp > 0.24 ? 0.24 : 0 ;
        }
        
        return tmp / t_size;
    }

    void Reset(void) // This should be removed later
    {
        for(int i=0 ; i < t_size ; i++)
            t_array[i]=0;
    }

    void Print(void)
    {
        double wind_speed = Average();
        Reset(); // This should be removed later

        Serial.print("Wind Speed: ");
        Serial.print(wind_speed);
        Serial.println(" m/s");
    }

    void Init(void)
    {
        pinMode(pin.input,INPUT);
        attachInterrupt(
            digitalPinToInterrupt(pin.input),
            Interrupt,
            RISING
        );
    }
}
