/******************************************************************************
 * File: ./WindDirection.h
 * Requires: Utils.h
 ******************************************************************************/
namespace WindDirection 
{
    struct { uint8_t input = A7; } pin;

    const uint8_t t_size = 10;
    float t_array[t_size] = {};

    volatile float max = 0 , mean = 0 , min = 1000;

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
        for( uint8_t i=0 ; i < t_size ; i++)
            t_array[i] = Calculate();
    }

    void Update(void)
    {
        float sum = 0, t_min = 1000, t_max = 0;

        Fill();

        for( uint8_t i=0 ; i < t_size ; i++ )
        {
            float& tmp = t_array[i];
            sum += tmp;

            t_min = t_min > tmp ? tmp : t_min;
            t_max = t_max < tmp ? tmp : t_max;
        }

        mean = sum / t_size;
        max = t_max;
        min = t_min;

    }

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);
        Fill();
    }
}
