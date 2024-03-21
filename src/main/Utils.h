/******************************************************************************
 * File: ./Utils.h
 ******************************************************************************/
constexpr unsigned long     hz2millis(double f){return (int)(1000/f);}
constexpr double            millis2hz(unsigned long t){return 1000/(double)t;}
constexpr int               ref_voltage = 5;
constexpr int               char2key(char c)
{
        return 
            '*' == c ? 0 :
            '7' == c ? 1 :
            '4' == c ? 2 :
            '1' == c ? 3 :
            '0' == c ? 4 :
            '8' == c ? 5 :
            '5' == c ? 6 :
            '2' == c ? 7 :
            '#' == c ? 8 :
            '9' == c ? 9 :
            '6' == c ? 10 :
            '3' == c ? 11 :
            'd' == c or 'D' == c ? 12 :
            'c' == c or 'C' == c ? 13 :
            'b' == c or 'B' == c ? 14 :
            'a' == c or 'A' == c ? 15 : NULL;
}
