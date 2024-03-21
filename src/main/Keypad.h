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
        int input = A6;
    } pin ;

    constexpr struct {
        const float 
            field[num_keys] = {
                      1.30  ,  1.50  ,  1.70  ,  1.90,
                      2.07  ,  2.30  ,  2.53  ,  2.77,
                      2.96  ,  3.22  ,  3.49  ,  3.77,
                      4.01  ,  4.32  ,  4.65  ,  5.00
            };
        const float offset =0.07; 
    } env ;

    volatile int keycode = 0;
    volatile float voltage = 0;

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
        { "d" , NULL },
        { "c" , NULL },
        { "b" , NULL },
        { "a" , NULL }
    };

    #ifdef DEBUG
    inline void Debug(void)
    {
       Serial.print("Pin: "); Serial.print(pin.input); Serial.print(": ");
       Serial.print("{ ");
       Serial.print("Voltage: "); Serial.print(voltage); 
       Serial.print(", ");
       Serial.print("Keycode: "); Serial.print(keycode);
       Serial.print(", ");
       Serial.print("Button: "); Serial.print(key[keycode-1].name);
       Serial.println(" }");
    }
    #endif

    volatile float Voltage()
    {
        return voltage 
            = analogRead(pin.input) * ( (float)ref_voltage / (float)1023 );
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
        int Fork(unsigned int pid){return setjmp(ring[pid].stack);}
    }

    static jmp_buf stack;
    static volatile int state;
    void ScanKeys(void)
    {
        volatile float voltage{0},tmp{0};
        for(int i=0;i<100;i++) 
            voltage = ( ( tmp=Voltage() ) > voltage ? tmp : voltage );
        if( env.offset < voltage )
        {
            for(int i=0 ; i < num_keys ; i++)
            {
                const float& f = env.field[i];
                volatile float low = f - env.offset, high = f + env.offset;
                if( ( low < voltage ) && ( voltage < high ) )
                { 
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
            Key& k = key[keycode-1];
            #ifdef DEBUG
            Debug();
            #endif
            if(k.handler) k.handler();
        }
        keycode=0;
    }

    // Currently this logic allows only single threaded processing
    inline void Exec(void){state=setjmp(stack);interrupts();Task();}

    namespace Attach
    {
        inline void Handler(int i,void (*p)(void)){key[i].handler=p;}
        inline void Keys(void)
        {
            Handler(char2key('*'),LCD::Draw::Stats);
            Handler(char2key('7'),LCD::Draw::Alphabet);
        }

        #define USE_TIMER_1 true
        #include <TimerInterrupt.h>

        // This could in the future be replaced with comparator interrupt.
        // The overhead caused by this polling might be an issue in the future
        // for a concurrent job scheduler.
        inline void Timer(void)
        {
            unsigned long&& refresh_rate_milliseconds = hz2millis(15);
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

    inline void Init(void)
    {
        pinMode(pin.input,INPUT);

        Attach::Keys();
        Attach::Timer();
    }
}
