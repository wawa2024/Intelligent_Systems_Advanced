/******************************************************************************
 * File: ./Keypad.h
 * Dependencies: <TimerInterrupt.h>
 * Upstream: https://github.com/khoih-prog/TimerInterrupt
 * Alternative: <avr/interrupt.h>
 ******************************************************************************/

namespace Keypad
{
    constexpr int num_keys = 4 * 4, bus_size = 1;
    constexpr float V(float x){return(((float)ref_voltage/(float)num_keys)*x);}
    constexpr struct {
        int 
            input[1]  = { A6 },
            output[0] = {}
            ;
    } pin ;
    const struct {
        const float 
            field[num_keys] = {
                      1.28  ,  1.47  ,  1.67  ,  1.89,
                      2.05  ,  2.27  ,  2.50  ,  2.74,
                      2.94  ,  3.20  ,  3.47  ,  3.75,
                      3.99  ,  4.31  ,  5.00  ,  5.00
            };
        const float offset =0.08; 
    } env ;
    volatile int keycode = 0;
    struct Key { const char* name; void (*handler)(void); };
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
        volatile float voltage = input * ( (float)ref_voltage / (float)1023 );

        #ifdef DEBUG
        Serial.print("Pin: A6 { Voltage: ");
        Serial.print(voltage);
        Serial.println(" }");
        #endif

        return voltage;
    }

    #include <setjmp.h>
    namespace Kernel 
    {
        // A future potential job scheduler
        constexpr int pids=2;
        struct Thread
        {jmp_buf stack;int state,pid{0};Thread* p;Thread(Thread* p):p(p){}};
        volatile Thread ring[pids]{ring,ring+1};
        volatile static Thread* ps=ring;
        void Scheduler(void){
            ps->state=setjmp(ps->stack);
            if(not ps->state){ps=ps->p;longjmp(ps->stack,true);}
        }
        inline int Fork(unsigned int pid){return setjmp(ring[pid].stack);}
    }

    static jmp_buf stack;
    static volatile int state;
    void ScanKeys(void)
    {
        volatile float voltage = Voltage();
        if( env.offset < voltage )
        {
            for(int i=0 ; i < num_keys ; i++)
            {
                const float& f = env.field[i];
                volatile float low = f - env.offset, high = f + env.offset;
                if( ( low < voltage ) && ( voltage < high ) )
                { 
                    Serial.print("High: "); Serial.println(high);
                    Serial.print("Low: "); Serial.println(low);
                    keycode = i + 1; 
                    break; 
                }
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
            //#ifdef DEBUG
            Serial.print("Keycode: ");
            Serial.print(keycode);
            Serial.print(",Button: ");
            Serial.print(k.name);
            Serial.println("");
            //#endif
            if(k.handler) k.handler();
        }
        keycode=0;
    }

    // Currently this logic allows only single threaded processing
    void Exec(void){state=setjmp(stack);interrupts();Task();}

    namespace Attach
    {
        void Handler(int i,void (*p)(void)){key[i-1].handler=p;}
        void Keys(void)
        {
            Handler(1,LCD::Draw::Stats);
            Handler(2,LCD::Draw::Alphabet);
        }

        #define USE_TIMER_1 true
        #include <TimerInterrupt.h>

        // This could in the future be replaced with comparator interrupt.
        // The overhead caused by this polling might be an issue in the future
        // for a concurrent job scheduler.
        void Timer(void)
        {
            const unsigned long refresh_rate_milliseconds = hz2millis(20);
            ITimer1.init();
            if(ITimer1.attachInterruptInterval(refresh_rate_milliseconds,ScanKeys))
            {
                Serial.print("Starting  ITimer1 OK, millis() = "); 
                Serial.println(millis());
            }
            else
                Serial.println("Can't set ITimer1. Select another freq. or timer");

        }
    }

    void Init(void)
    {
        pinMode(pin.input[0],INPUT);

        #ifdef DEBUG
        Debug::dump_var(env.offset,"Offset");
        Debug::dump_array(env.field,16,"Field");
        #endif
        
        Attach::Keys();
        Attach::Timer();
    }
}
