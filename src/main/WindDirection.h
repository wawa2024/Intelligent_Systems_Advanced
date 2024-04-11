/******************************************************************************
 * File: ./WindDirection.h
 * Requires: Utils.h
 ******************************************************************************/
namespace WindDirection 
{
    constexpr struct { uint8_t input = A7; } pin;

    constexpr uint8_t t_size = 10;
    float t_array[t_size] = {};

    volatile float max = 0 , mean = 0 , min = 0; 

    float mapd(float x, float in_min, float in_max, float out_min, float out_max)
    {     
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
    }

    float Calculate(void)
    {
        return mapd( Voltage( pin.input ) , 0 , 3.8 , 0 , 359 );
    }

    void Refresh(void)
    {
        static uint8_t i=0; 
        i = i < 10 ? i : 0;
        t_array[i] = Calculate();
        i++;
    }

    void Update(void)
    {
        Refresh();

        float sum = 0, t_min = 1000, t_max = 0;

        for( uint8_t i = 0 ; i < t_size ; i++ )
        {
            float& tmp = t_array[i];
            sum += tmp;

            t_min = t_min > tmp ? tmp : t_min;
            t_max = t_max < tmp ? tmp : t_max;
        }

        mean -= ( ( mean = sum / t_size ) < 0.24 ) ? 0 : 0.24 ;
        max  -= ( ( max = t_max         ) < 0.24 ) ? 0 : 0.24 ;
        min  -= ( ( min = t_min         ) < 0.24 ) ? 0 : 0.24 ;
    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        for(uint8_t i = 0 ; i < 10 ; i++)
            Refresh();
    }
}
