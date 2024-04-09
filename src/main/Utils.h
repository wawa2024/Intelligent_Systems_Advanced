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
#define KEY_STAR            1
#define KEY_7               2
#define KEY_4               3
#define KEY_1               4
#define KEY_0               5
#define KEY_8               6
#define KEY_5               7
#define KEY_2               8
#define KEY_HASH            9
#define KEY_9               10
#define KEY_6               11
#define KEY_3               12
#define KEY_D               13
#define KEY_d               13
#define KEY_C               14
#define KEY_c               14
#define KEY_B               15
#define KEY_b               15
#define KEY_A               16
#define KEY_a               16

float Voltage(uint8_t PIN) { 
    return ( analogRead(PIN) * ref_voltage ) / (float)Max_ADC_Ret;
}
