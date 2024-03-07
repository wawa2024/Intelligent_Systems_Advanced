/******************************************************************************
 * File: ./Keypad.h
 ******************************************************************************/
namespace Keypad
{
    struct {
        int 
            input[4] = { 0 , 0 , 0 , 0 },
            output[4] = { 0 , 0 , 0 , 0 }
            ;
    } pin ;

    struct {
        const int 
            bus_size = 4,
            keycodes = 4 * 4
            ;
    } env ;

    unsigned char keypad[16] = {};

    void Scan(void)
    {
        for(int i=0 ; i < env.bus_size; i++)
        {
            digitalWrite( pin.input[i] , HIGH );
            for(int j=0 ; j < env.bus_size ; j++)
                keypad[ ( i * env.bus_size ) + j ] = ( i + 1 ) * digitalRead(pin.output[j]);
            digitalWrite( pin.input[i] , LOW );
        }
    }

    // The loop should be 'exec -> main -> scan -> repeat'
    void Exec(void)
    {

        for(int i=0 ; i < env.keycodes ; i++)
        {
            unsigned char keycode = keypad[i];

            // A global jmptbl could replace this.
            // Would allow multi hierarchy management.
            // A common "Get" object API should be used to set
            // internal flags.
            switch(keycode) 
            {
                default:
                    Serial.print("{ Keycode: ");
                    Serial.print(i);
                    Serial.print(", State: ");
                    Serial.print(keycode);
                    Serial.print(" }");
                    break;
            }
            Serial.println("");
        }
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
