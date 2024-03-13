/******************************************************************************
 * File: ./Keypad.h
 ******************************************************************************/

namespace Keypad
{
    struct {
        int 
            input[0]  = {},
            output[0] = {}
            ;
    } pin ;

    struct {
        const int 
            keycodes = 4 * 4,
            ref_voltage = 5
            ;
        const float 
            field[16] = 
                      { 0.3125 , 0.6250 , 0.9375 , 1.25 , 
                        1.5625 , 1.8750 , 2.1875 , 2.50 ,
                        2.8125 , 3.1250 , 3.4375 , 3.75 ,
                        4.0625 , 4.3750 , 4.6875 , 5.00 };
        const float
            offset = ( 5/16 ) / 2
            ;
    } env ;

    int keycode = 0;

    float Voltage()
    {
        return    (float)analogRead(pin.input[0]) * 
                ( (float)env.ref_voltage / (float)1023 );
    }

    void Scan(void)
    {
        float val = Voltage();
        for(int i=0 ; i < env.keycodes ; i++)
        {
            float f = env.field[i];
            if( ( f - env.offset ) <= val &&
                ( f + env.offset ) >= val )
            {
                keycode = i + 1; 
            }
        }
    }

    void Task(void)
    {
        switch(keycode) 
        {
            case 1 : case 2 : case 3 : case 4 :
            case 5 : case 6 : case 7 : case 8 :
            case 9 : case 10: case 11: case 12:
            case 13: case 14: case 15: case 16:
                Serial.print("Keycode: ");
                Serial.print(keycode);
                Serial.println("");
                break;
            default:
                break;
        }
    }

    void Exec(void)
    {
        Scan(); Task();
    }

    void Init(void)
    {
        for(int i=0; i < env.bus_size ; i++)
        {
            pinMode(pin.input[i] , INPUT);
            pinMode(pin.output[i] , OUTPUT);
        }
    }
}
