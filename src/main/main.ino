/* 
 * Display 16x4 Library: 	liquid-crystal	
 * 
 *	
 *	
 */

//#include "pins.h"

#define DELAY 100
#define MAX_VOLTAGE 5

int WindDirection(int pin, int reference=1023){

    int var = analogRead(pin);

    double voltage = (double)var * ( (double)MAX_VOLTAGE / (double)reference ) ;

    int wind_direction = map(voltage, 0 , 3.8 , 0 , 359 );

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
