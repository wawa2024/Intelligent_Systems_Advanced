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
    double a_array[a_size] = {};

    inline double mapd(double x, double in_min, double in_max, double out_min, double out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    void Push(uint16_t a)
    {
        static uint8_t i = 0;
        a_array[i] = a;
        i = i < 10 ? i : 0;
        i++;
    }

    double Calculate(void)
    {
        return mapd( Voltage( pin.input ) , 0 , 3.8 , 0 , 359 );
    }

    void Fill(void)
    {
        static bool flag = true;
        Serial.println("Filling WindDirection Array...");
        if(flag){
            for( uint8_t i=0 ; i < a_size ; i++)
            {
                Push( Calculate() );
                delay( seconds2millis(1) );
            }
            flag = false;
        }
    }

    int Update(void)
    {
        Push( Calculate() );
        uint16_t sum = 0;
        for( uint8_t i=0 ; i < a_size ; i++ )
        {
            sum += a_array[i];

           #ifdef DEBUG
           Serial.print("WindDirection: a_array["); Serial.print(i); 
           Serial.print("] = "); Serial.println(a_array[i]);
           #endif
        }
        
        double avg = sum / a_size;
        
        #ifdef DEBUG
        Serial.print("WindDirection avg: "); Serial.println(avg);
        #endif

        return (int)( ( avg - (int)avg ) >= 0.5 ? avg + 1 : avg );
    }

    inline int Value(void)
    {
        return Update();
    }

    void Init(void)
    {
        pinMode(pin.input,INPUT);
        Fill();
    }
}
