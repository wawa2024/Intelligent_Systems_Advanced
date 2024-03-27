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

    constexpr uint8_t a_size = 10;
    double array[a_size] = {};

    inline double mapd(double x, double in_min, double in_max, double out_min, double out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    void Push(uint16_t a)
    {
        static uint8_t i = 0;
        array[i] = a;
        i = i < 10 ? i : 0;
    }

    double Calculate(void)
    {
        return mapd( Voltage( pin.input ) , 0 , 3.8 , 0 , 359 );
    }

    void Fill(void)
    {
        static bool flag = true;
        if(flag){
            for( uint8_t i=0 ; i < a_size ; i++)
            {
                Push( Calculate() );
                delay( hz2millis(1) );
            }
            flag = false;
        }
    }

    double Average(void)
    {
        Push( Calculate() );
        uint16_t sum = 0;
        for( uint8_t i=0 ; i < a_size ; i++ )
        {
            sum += array[i];

           #ifdef DEBUG
           Serial.print("WindDirection: array["); Serial.print(i); 
           Serial.print("] = "); Serial.println(array[i]);
           #endif
        }
        return sum / a_size;
    }

    inline double Value(void)
    {
        return Average();
    }

    void Init(void)
    {
        pinMode(pin.input,INPUT);
        Fill();
    }
}
