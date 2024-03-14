/******************************************************************************
 * File: ./Debug.h
 ******************************************************************************/
namespace Debug
{
    template<typename T>inline void dump_array(T& a,int size){ 
        dump_array(a,size,"Array");}
    template<typename T>void dump_array(T& a,int size,char* str){
        for(int i=0 ; i < size ; i++)
        {
            Serial.print(str);
            Serial.print("["); Serial.print(i); Serial.print("]: ");
            Serial.println(a[i]);
        }}
    template<typename T>inline void dump_var(T& a){
            dump_var(a,"Variable");}
    template<typename T>void dump_var(T& a,char* str){
            Serial.print(str); Serial.print(": "); Serial.println(a);}
}
