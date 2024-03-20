/******************************************************************************
 * File: ./WindSpeed.h
 * Dependency: ./Utils.h
 ******************************************************************************/
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
        static volatile int i{0};

        t_begin = t_end;
        t_end = millis();

        i = i < t_size ? i : 0;

        t_array[i++] = t_end - t_begin;
    }

    double Value(void)
    {
        double sum = 0;
        for(int i=0 ; i < t_size ; i++)
        {
           sum += millis2hz(t_array[i]) * 0.699 ;
           sum -= sum > 0 ? 0.24 : 0 ;
        }
        double average = sum / t_size;
        return average;
    }

    void Print(void)
    {
        double wind_speed = Value();
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
