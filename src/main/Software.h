/******************************************************************************
 * File: ./Software.h
 * Requires: Keypad.h LCD.h NET.h Utils.h
 ******************************************************************************/
namespace Software
{
    void Summary(void)
    {
        LCD::Clear();
        snprintf(buf,format_header,STRING_WindDirection); LCD::Flush();
        LCD::SetCursor(0,1);
        snprintf(buf,format_indent,STRING_mean,WindDirection::mean,STRING_deg); LCD::Flush();
        LCD::SetCursor(0,2);
        snprintf(buf,format_header,STRING_WindSpeed); LCD::Flush();
        LCD::SetCursor(0,3);
        snprintf(buf,format_indent,STRING_mean,WindSpeed::mean,STRING_mps); LCD::Flush();
    }

    void Template(char* s, int max, int mean, int min, char* unit)
    {
        LCD::Clear();
        snprintf(buf,format_header,s); LCD::Flush();
        LCD::SetCursor(0,1);
        snprintf(buf,format_indent,STRING_max,max,unit); LCD::Flush();
        LCD::SetCursor(0,2);
        snprintf(buf,format_indent,STRING_mean,mean,unit); LCD::Flush();
        LCD::SetCursor(0,3);
        snprintf(buf,format_indent,STRING_min,min,unit); LCD::Flush();
    }

    void WindDirection(void)
    {
        Template(STRING_WindDirection
                ,WindDirection::max
                ,WindDirection::mean
                ,WindDirection::min
                ,STRING_deg
                );
    }

    void WindSpeed(void)
    {
        Template(STRING_WindSpeed
                ,WindSpeed::max
                ,WindSpeed::mean
                ,WindSpeed::min
                ,STRING_mps
                );
    }

#ifdef NET
    void IPstats(void)
    {
        NET::Update::IP();
        LCD::Clear();
        LCD::Print("IP ");     LCD::Print(NET::ip);
        LCD::SetCursor(0,1);    
        LCD::Print("GW ");     LCD::Print(NET::gw);
        LCD::SetCursor(0,2);
        LCD::Print("DNS ");    LCD::Print(NET::dns);
        LCD::SetCursor(0,3);
        LCD::Print("MASK ");   LCD::Print(NET::subnet);
    }

    void HWstats(void)
    {
        LCD::Clear();
        LCD::Print( NET::Status::Hardware() );
        LCD::SetCursor(0,1);
        LCD::Print( NET::Status::Link() );
        LCD::SetCursor(0,2);
        LCD::Print("MAC ");     LCD::Print(NET::mac2string());
        LCD::SetCursor(0,3);
    #ifdef NET
    #ifdef DHCP
        LCD::Print("DHCP ON");
    #else
        LCD::Print("DHCP OFF");
    #endif
    #else

    #endif
    }

    void MQTTstats(void)
    {
        NET::Update::IP();
        LCD::Clear();
        LCD::Print("MQTT ");    LCD::Print(MQTT::Checkup());
        LCD::SetCursor(0,1);    
        LCD::Print("HOST ");    LCD::Print(MQTT::IP);
        LCD::SetCursor(0,2);
        LCD::Print("PORT ");    LCD::Print(MQTT::port);
        LCD::SetCursor(0,3);
        LCD::Print("ID ");      LCD::Print(MQTT::groupId);
    }
#endif

    void Bootmessage(void)
    {
        LCD::Clear();
        LCD::Print("ARDUINO BOOT ");
        LCD::Print(STRING_ONLINE);
        LCD::SetCursor(0,1);
    #ifdef NET
        LCD::Print(STRING_DHCP);
        LCD::Print(STRING_SPACE);
    #ifdef DHCP
        LCD::Print(STRING_ON);
    #else
        LCD::Print(STRING_OFF);
    #endif
        LCD::Print(STRING_NET);
        LCD::Print(STRING_SPACE);
        LCD::Print(STRING_DISABLED);
    #endif
    }

    void Default(void)
    {
        LCD::Clear();
        LCD::Print("Unmapped key");
    }

    inline void Init(void)
    {
    #ifdef KEYPAD
        for(uint8_t i=0 ; i < Keypad::num_keys ; i++)
            Keypad::AttachKeyHandler(i,Default);
    #ifdef NET
        Keypad::AttachKeyHandler(KEY(A),IPstats);
        Keypad::AttachKeyHandler(KEY(B),HWstats);
        Keypad::AttachKeyHandler(KEY(1),MQTTstats);
    #endif
        Keypad::AttachKeyHandler(KEY(2),Summary);
        Keypad::AttachKeyHandler(KEY(3),WindDirection);
        Keypad::AttachKeyHandler(KEY(4),WindSpeed);
        Keypad::AttachKeyHandler(KEY(C),Bootmessage);
    #endif
    #ifdef DEBUG_SOFTWARE
        msgSerial(STRING_Software,STRING_initialized);
    #endif
        Bootmessage();
    }
}
