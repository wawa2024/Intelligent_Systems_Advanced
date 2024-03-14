/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: avr/interrupt.h
 ******************************************************************************/
//#include <avr/interrupt.h> //pending

namespace Keypad
{
    constexpr float V(float x){ return ( ( 5.0 / 16.0 ) * x ); }
    struct {
        int 
            input[1]  = { A6 },
            output[0] = {}
            ;
    } pin ;

    struct {
        const int 
            keycodes = 4 * 4,
            bus_size = 1,
            ref_voltage = 5
            ;
        const float 
            field[16] = {
                      V(1)  ,   V(2)    ,   V(3)    ,   V(4),
                      V(5)  ,   V(6)    ,   V(7)    ,   V(8),
                      V(9)  ,   V(10)   ,   V(11)   ,   V(12),
                      V(13) ,   V(14)   ,   V(15)   ,   V(16)
            };
        const float
            offset = V(1) / 2
            ;
    } env ;

    int keycode = 0;
    struct Key { 
        const char* name; 
        void (*handler)(void); 
    };
    Key key[16] = {
        { "*" , NULL },
        { "7" , NULL },
        { "4" , NULL },
        { "1" , NULL },
        { "0" , NULL },
        { "8" , NULL },
        { "5" , NULL },
        { "2" , NULL },
        { "#" , NULL },
        { "9" , NULL },
        { "6" , NULL },
        { "3" , NULL },
        { "D" , NULL },
        { "C" , NULL },
        { "B" , NULL },
        { "A" , NULL }
    };

    inline float Voltage()
    {
        float input = analogRead(pin.input[0]);
        float voltage = input * ( (float)env.ref_voltage / (float)1023 );

        #define DEBUG
        #ifdef DEBUG
        Serial.print("Pin: A6 { Voltage: ");
        Serial.print(voltage);
        Serial.println(" }");
        #endif

        return voltage;
    }

    void Scan(void)
    {
        float voltage = Voltage();
        static bool state = true;
       
        // Maybe add a delayed repeat rate functionality
        // static unsigned long t_press = 0;
        // unsigned long t_time = millis();
        //
        // A timed Interrupt handler could be used to
        // scan for keypress changes, which when read
        // trigger a flag which is used within all LCD
        // program bodies to determine if they should halt their
        // execution. The interrupt handler would only change
        // 2 values, keycode (through Scan()) and a flag value

        for(int i=0 ; i < env.keycodes ; i++)
        {
            float f = env.field[i];

            float low = f - env.offset, high = f + env.offset;
            if( ( low < voltage ) && ( high > voltage ) )
                keycode = i + 1; 
        }
    }

    void Task(void)
    {
        if(keycode)
        {
            keycode-=1;
            Key& k = key[keycode];
            #ifdef DEBUG
            Serial.print("Keycode: ");
            Serial.print(keycode);
            Serial.print(",Button: ");
            Serial.print(k.name);
            Serial.println("");
            #endif
            if(k.handler) k.handler();
        }
        keycode=0;
    }

    void Exec(void)
    {
        Scan(); Task();
    }

    void AttatchHandler(int i,void (*p)(void)){key[i-1].handler=p;}
    void Init(void)
    {
        for(int i=0; i < env.bus_size ; i++)
        {
            pinMode(pin.input[i] , INPUT);
            pinMode(pin.output[i] , OUTPUT);
        }
        #ifdef DEBUG
        Debug::dump_var(env.offset,"Offset");
        Debug::dump_array(env.field,16,"Field");
        #endif
        AttatchHandler(1,LCD::Draw::Stats);
        AttatchHandler(2,LCD::Draw::Alphabet);
    }
}
