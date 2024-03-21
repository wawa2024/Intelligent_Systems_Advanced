/******************************************************************************
 * File: ./Utils.h
 ******************************************************************************/
constexpr unsigned long     hz2millis(double f){return (int)(1000/f);}
constexpr double            millis2hz(unsigned long t){return 1000/(double)t;}
constexpr int               ref_voltage = 5;
