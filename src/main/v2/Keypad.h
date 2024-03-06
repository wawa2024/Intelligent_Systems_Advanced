/******************************************************************************
 * File: ./Keypad.h
 ******************************************************************************/

struct Keypad
{
    struct {
        int 
            input[4] = { 0 , 0 , 0 , 0 },
            output[4] = { 0 , 0 , 0 , 0 }
            ;
    } pin ;

    unsigned char keypad[16] = {};

    const int 
        bus_size = 4,
        keycodes = 4 * 4
        ;

    Keypad()
    {
        for(int i=0; i < bus_size ; i++)
            pinMode(pin.input[i] , INPUT);
        for(int i=0; i < bus_size ; i++)
            pinMode(pin.output[i] , OUTPUT);
    }

    void scan(void)
    {
        for(int i=0 ; i < bus_size; i++)
        {
            digitalWrite( pin.input[i] , HIGH );
            for(int j=0 ; j < bus_size ; j++)
                keypad[ ( i * bus_size ) + j ] = ( i + 1 ) * digitalRead(pin.output[j]);
            digitalWrite( pin.input[i] , LOW );
        }
    }

    void exec(void)
    {
        scan();
        for(int i=0 ; i < keycodes ; i++)
        {
            unsigned char keycode = keypad[i];
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

} keypad ;
