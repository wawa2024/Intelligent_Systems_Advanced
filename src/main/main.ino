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

    int voltage = var * ( MAX_VOLTAGE / reference ) ;

    int wind_direction = map(voltage, 0 , 3.8 , 0 , 359 );

    return wind_direction ;
}

void setup() {
//	pinMode(PIN(X),OUTPUT);

	  pinMode(A3,INPUT);
}

void loop() {
	Serial.println(WindDirection(A3));
	delay(DELAY);
}
