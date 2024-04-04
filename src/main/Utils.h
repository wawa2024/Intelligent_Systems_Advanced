/******************************************************************************
 * File: ./Utils.h
 ******************************************************************************/
#define hz2millis(X)        ( (unsigned long) ( 1000 / (float) X ) )
#define millis2hz(X)        ( 1000 / (float) X ) 
#define seconds2millis(X)   ( X * 1000 )
#define millis2seconds(X)   ( X / 1000 )
#define ref_voltage         5
#define Max_ADC_Ret         1023
#define KEY(X)              KEY_ ## X
#define KEY_STAR            0
#define KEY_7               1
#define KEY_4               2
#define KEY_1               3
#define KEY_0               4
#define KEY_8               5
#define KEY_5               6
#define KEY_2               7
#define KEY_HASH            8
#define KEY_9               9
#define KEY_6               10
#define KEY_3               11
#define KEY_D               12
#define KEY_d               12
#define KEY_C               13
#define KEY_c               13
#define KEY_B               14
#define KEY_b               14
#define KEY_A               15
#define KEY_a               15

float Voltage(uint8_t PIN) { 
    return (float)analogRead(PIN) * (float)ref_voltage / (float)Max_ADC_Ret;
}

int round2int(float x)
{
    return (int)( ( x - (int) x ) >= 0.5 ? x + 1 : x );
}

void Wait(uint16_t t){ delay(seconds2millis(t)); }
