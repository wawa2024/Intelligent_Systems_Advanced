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

    int max = 0, mean = 0, min = 0;

    void InterruptServiceRoutine(void)
    {
        static volatile char i = 0;

        t_begin = t_end;
        t_end = millis();

        i = i < t_size ? i : 0;

        t_array[i++] = t_end - t_begin;
    }

    void Update(void)
    {
        float sum = 0, t_max = 0 , t_min = 1000, tmp = 0;

    #ifdef DEBUG_WINDSPEED
        Serial.print(STRING_WindSpeed);
        Serial.print(STRING_COLON);
        Serial.print(STRING_SPACE);
        Serial.print(STRING_BRACKET_START);
    #endif

        for(int i=0 ; i < t_size ; i++)
        {
           sum += tmp = millis2hz(t_array[i]) * 0.699 ;
           sum -= sum > 0 ? 0.24 : 0 ;

           t_max = t_max < tmp ? tmp : t_max;
           t_min = t_min > tmp ? tmp : t_min;

       #ifdef DEBUG_WINDSPEED
           Serial.print("t_array[");    Serial.print(i); 
           Serial.print("]: ");         Serial.print(tmp);
           if( i != ( t_size - 1 ) )    Serial.print(STRING_COMMA);
       #endif
        }

    #ifdef DEBUG_WINDSPEED
        Serial.println(STRING_BRACKET_END);
    #endif

        mean = round2int( sum / t_size );
        max = t_max;
        min = t_min;

    #ifdef DEBUG_WINDSPEED
        printJSON(STRING_WindSpeed,max,mean,min);
    #endif

    }

    inline int Value(void) { return mean; }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        attachInterrupt(
            digitalPinToInterrupt(pin.input),
            InterruptServiceRoutine,
            RISING
        );
    #ifdef DEBUG_WINDSPEED
        msgSerial(STRING_WindSpeed,STRING_initialized);
    #endif
        return;
    }
}
