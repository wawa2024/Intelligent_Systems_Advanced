/******************************************************************************
 * File: ./IO.h
 ******************************************************************************/

const uint16_t buf_size = 256;

char buf[buf_size] = {} ;

const char* format_header = "%s: "
            , format_object = "%s: { %s: %i, %s: %i, %s: %i }"
            , format_indent = "  %s %i %s"
            , format_msg = "%s %i %s"
            , STRING_mps = "m/s"
            , STRING_SPACE = " "
            , STRING_COMMA = ", "
            , STRING_BRACKET_START = "{ "
            , STRING_BRACKET_END = " }"
            , STRING_COLON = ":"
            , STRING_DOT = "."
            , STRING_NONE = ""
            ;

#define STRING(NAME) char STRING_ ## NAME[] = #NAME;
STRING(deg)
STRING(ON)
STRING(OFF)
STRING(ONLINE)
STRING(OFFLINE)
STRING(DHCP)
STRING(DISABLED)
STRING(WindDirection)
STRING(WindSpeed)
STRING(max)
STRING(mean)
STRING(min)
STRING(LCD)
STRING(NET)
STRING(COM)
STRING(MQTT)
STRING(Keypad)
STRING(Software)
STRING(initialized)
STRING(failed)
STRING(success)
STRING(call)
STRING(Function)
STRING(Waiting)
STRING(seconds)

#ifdef DEBUG
inline void flush(void)
{
    Serial.println(buf);
}

inline void dump(void)
{
    Serial.print(buf);
}

void printJSON(char* s, int max, int mean, int min)
{
    snprintf(buf,format_object,s,STRING_max,max,STRING_mean,mean,STRING_min,min);
    flush();
}

void msgSerial(char* s, char* msg)
{
    Serial.print(s);
    Serial.print(STRING_SPACE);
    Serial.print(msg);
}
#endif
