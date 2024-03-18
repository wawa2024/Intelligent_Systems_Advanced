/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: <TimerInterrupt.h>
 * Upstream: https://github.com/khoih-prog/TimerInterrupt
 * Alternative: <avr/interrupt.h>
 ******************************************************************************/

namespace Keypad
{
    constexpr float V(float x){ return ( ( 5.0 / 16.0 ) * x ); }
    const struct {
        constexpr static int 
            input[1]  = { A6 },
            output[0] = {}
            ;
    } pin ;

    const struct {
        constexpr static int 
            keycodes = 4 * 4,
            bus_size = 1,
            ref_voltage = 5
            ;
        const float 
            field[keycodes] = {
                      V(1)  ,   V(2)    ,   V(3)    ,   V(4),
                      V(5)  ,   V(6)    ,   V(7)    ,   V(8),
                      V(9)  ,   V(10)   ,   V(11)   ,   V(12),
                      V(13) ,   V(14)   ,   V(15)   ,   V(16)
            };
        const float offset = V(1) / 2;
    } env ;

    volatile int keycode = 0;
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

    volatile float Voltage()
    {
        float input = analogRead(pin.input[0]);
        volatile float voltage = input * ( (float)env.ref_voltage / (float)1023 );

        #define DEBUG
        #ifdef DEBUG
        Serial.print("Pin: A6 { Voltage: ");
        Serial.print(voltage);
        Serial.println(" }");
        #endif

        return voltage;
    }


    #include <setjmp.h>
    jmp_buf stack;
    int state;

    void ScanKeys(void)
    {
        volatile float voltage = Voltage();
        if( env.offset < voltage )
        {
            for(int i=0 ; i < env.keycodes ; i++)
            {
                const float& f = env.field[i];
                volatile float low = f - env.offset, high = f + env.offset;
                if( ( low < voltage ) && ( voltage < high ) )
                    keycode = i + 1; 
            }
            longjmp(stack,state);
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
        state=setjmp(stack); interrupts() ; Task();
    }

    void AttatchHandler(int i,void (*p)(void)){key[i-1].handler=p;}
    void AttatchKeys(void)
    {
        AttatchHandler(1,LCD::Draw::Stats);
        AttatchHandler(2,LCD::Draw::Alphabet);
    }


    #define USE_TIMER_1 true
    #include <TimerInterrupt.h>

    void AttatchTimer(void)
    {
        const unsigned long refresh_rate_milliseconds = 200;
        ITimer1.init();
        if(ITimer1.attachInterruptInterval(refresh_rate_milliseconds,ScanKeys))
        {
            Serial.print("Starting  ITimer1 OK, millis() = "); 
            Serial.println(millis());
        }
        else
            Serial.println(F("Can't set ITimer1. Select another freq. or timer"));

    }

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
        
        AttatchKeys();
        AttatchTimer();
    }
}
