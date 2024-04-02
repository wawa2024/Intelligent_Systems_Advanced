/******************************************************************************
 * File: ./WindDirection.h
 * Requires: Utils.h
 ******************************************************************************/
namespace WindDirection 
{
    struct { uint8_t input = A7; } pin;

    const uint8_t t_size = 10;
    float t_array[t_size] = {};

    int max = 0 , mean = 0 , min = 0;

    void Push(float x)
    {
        static uint8_t i = 0;
        i = i < 10 ? i : 0;
        t_array[i++] = x;
    }

    float mapd(float x, float in_min, float in_max, float out_min, float out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    float Calculate(void)
    {
        return mapd( Voltage( pin.input ) , 0 , 3.8 , 0 , 359 );
    }

    void Fill(void)
    {
    #ifdef DEBUG_WINDDIRECTION
        Serial.print("Filling ");
        Serial.print(STRING_WindDirection);
        Serial.print("Array");
    #endif
        for( uint8_t i=0 ; i < t_size ; i++)
        {
            Push( Calculate() );
        #ifdef DEBUG_WINDDIRECTION
            Serial.print(STRING_DOT);
        #endif
            delay(seconds2millis(1));
        }
    #ifdef DEBUG_WINDDIRECTION
        Serial.println(STRING_NONE);
    #endif
        return;
    }

    void Update(void)
    {
        float sum = 0, t_min = 1000, t_max = 0;

        Push( Calculate() );

    #ifdef DEBUG_WINDDIRECTION
        Serial.print(STRING_WindDirection);
        Serial.print(STRING_COLON);
        Serial.print(STRING_SPACE);
        Serial.print(STRING_BRACKET_START);
    #endif
        for( uint8_t i=0 ; i < t_size ; i++ )
        {
            float& tmp = t_array[i];
            sum += tmp;

            t_min = t_min > tmp ? tmp : t_min;
            t_max = t_max < tmp ? tmp : t_max;

        #ifdef DEBUG_WINDDIRECTION
            Serial.print("\"t_array[");  Serial.print(i); 
            Serial.print("]\": ");       Serial.print(tmp);
            if( i != ( t_size - 1 ) )    Serial.print(", ");
        #endif
        }
    #ifdef DEBUG_WINDDIRECTION
        Serial.println(STRING_BRACKET_END);
    #endif

        mean = round2int( sum / t_size );
        max = t_max;
        min = t_min;

    #ifdef DEBUG_WINDDIRECTION
        printJSON(STRING_WindDirection,max,mean,min);
    #endif
    }

    inline int Value(void) { return mean; }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        Fill();
    #ifdef DEBUG_WINDDIRECTION
        msgSerial(STRING_WindDirection,STRING_initialized);
    #endif
    }
}
