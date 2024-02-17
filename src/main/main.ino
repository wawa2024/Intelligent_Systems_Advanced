/* 
 * Display 16x4 Library: 	liquid-crystal	
 * 
 *	
 *	
 */

    //////////////////////
    // Global Variables //
    //////////////////////

namespace var
{
    int refresh_rate    = 100,
        baud_rate       = 9600,
        ref_voltage     = 5,
        wind_speed      = 0
        ;
}

namespace pin
{
    int wind_direction = A4,
        wind_speed     = 2
        ;
}

    ////////////////////
    // Wind Direction //
    ////////////////////

double mapd(double x, double in_min, double in_max, double out_min, double out_max)
{     
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
}

int WindDirection(int pin)
{
    static const int Max_ADC_Ret = 1023;

    double voltage = (double)analogRead(pin) * 
                     ( 
                        (double)var::ref_voltage / 
                        (double)Max_ADC_Ret 
                     );

    int wind_direction = mapd(voltage, 0 , 3.8 , 0 , 359 );

    return wind_direction ;
}

void PrintWindDirection(void)
{
    Serial.print("Wind Direction: ");
    Serial.println(WindDirection(pin::wind_direction));
}

    ////////////////
    // Wind Speed //
    ////////////////

void WindSpeed(void)
{
    var::wind_speed += digitalRead(pin::wind_speed);
}

void PrintWindSpeed(void)
{
    Serial.print("Wind Speed: ");
    Serial.println(var::wind_speed);
    var::wind_speed = 0 ;
}

    //////////
    // Main //
    //////////

void PrintStats(void)
{
    PrintWindDirection();
    PrintWindSpeed();
}

void InitPins(int* a, int size, int mode)
{
    for(int i=0 ; i < size ; i++)
        pinMode(a[i],mode);
}

void setup()
{
    int a[] = { pin::wind_direction , pin::wind_speed };

    InitPins(a,sizeof(a)/sizeof(int),INPUT);

    Serial.begin(var::baud_rate);

    attachInterrupt(
        digitalPinToInterrupt(pin::wind_speed),
        WindSpeed,
        RISING
    );
}

void loop()
{
    PrintStats();
	delayMicroseconds(var::refresh_rate);
}
