/******************************************************************************
 * File: ./Software.h
 * Requires: Keypad.h LCD.h NET.h Utils.h
 ******************************************************************************/
namespace Software
{
    char s_wd[] = "WindDirection:"
            , s_ws[] = "WindSpeed:"
            , s_deg[] = " deg"
            , s_mps[] = " m/s"
            , s_max[] = "  max "
            , s_mean[] = "  mean "
            , s_min[] = "  min "
            ;

    void Summary(void)
    {
        LCD::Clear();
        LCD::Print(s_wd); 
        LCD::SetCursor(0,1);
        LCD::Print(s_mean); 
        LCD::Print(WindDirection::mean,1); LCD::Print(s_deg);
        LCD::SetCursor(0,2);
        LCD::Print(s_ws);
        LCD::SetCursor(0,3);
        LCD::Print(s_mean); 
        LCD::Print(WindSpeed::mean,1); 
        LCD::Print(s_mps);
    }

    void Template(char* s, int max, int mean, int min, char* unit)
    {
        LCD::Clear();
        LCD::Print(s);
        LCD::SetCursor(0,1);
        LCD::Print(s_max); LCD::Print( max,1 ); LCD::Print(unit);
        LCD::SetCursor(0,2);
        LCD::Print(s_mean); LCD::Print( mean,1 ); LCD::Print(unit);
        LCD::SetCursor(0,3);
        LCD::Print(s_min); LCD::Print( min,1 ); LCD::Print(unit);
    }

    void WindDirection(void)
    {
        Template(s_wd
                ,WindDirection::max
                ,WindDirection::mean
                ,WindDirection::min
                ,s_deg
                );
    }

    void WindSpeed(void)
    {
        Template(s_ws
                ,WindSpeed::max
                ,WindSpeed::mean
                ,WindSpeed::min
                ,s_mps
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
        LCD::Print("ARDUINO BOOT ONLINE");
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
        Keypad::AttachKeyHandler(KEY(C),MQTTstats);
    #endif
        Keypad::AttachKeyHandler(KEY(D),Summary);
        Keypad::AttachKeyHandler(KEY(STAR),WindDirection);
        Keypad::AttachKeyHandler(KEY(HASH),WindSpeed);
    #endif
    #ifdef DEBUG_SOFTWARE
        Serial.println("Software initialized");
    #endif
        Bootmessage();
    }
}
