/* 
 * Display 16x4 Library: 	liquid-crystal	
 * 
 *	
 *	
 */

//#include "pins.h"

#define DELAY 100
#define VOLTAGE_REF 5


double mapd(double x, double in_min, double in_max, double out_min, double out_max){     
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; 
}


int WindDirection(int pin, int Max_ADC_Ret = 1023){

    int var = analogRead(pin);

    double voltage = (double)var * ( (double)VOLTAGE_REF / (double)Max_ADC_Ret ) ;

    int wind_direction = mapd(voltage, 0 , 3.8 , 0 , 359 );

    return wind_direction ;
}

void setup() {
//	pinMode(PIN(X),OUTPUT);
    Serial.begin(9600);
	pinMode(A4,INPUT);
}

void loop() {
	Serial.println(WindDirection(A4));
	delay(DELAY);
}
