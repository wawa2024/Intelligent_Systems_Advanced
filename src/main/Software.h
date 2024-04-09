/******************************************************************************
 * File: ./Software.h
 * Requires: Keypad.h LCD.h NET.h Utils.h
 ******************************************************************************/
#include "include/MusicPlayer.h"

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

    void Template(char* s, float max, float mean, float min, char* unit)
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
        LCD::Print(F("IP "));     LCD::Print(NET::ip);
        LCD::SetCursor(0,1);    
        LCD::Print(F("GW "));     LCD::Print(NET::gw);
        LCD::SetCursor(0,2);
        LCD::Print(F("DNS "));    LCD::Print(NET::dns);
        LCD::SetCursor(0,3);
        LCD::Print(F("MASK "));   LCD::Print(NET::subnet);
    }

    void HWstats(void)
    {
        LCD::Clear();
        LCD::Print( NET::Status::Hardware() );
        LCD::SetCursor(0,1);
        LCD::Print( NET::Status::Link() );
        LCD::SetCursor(0,2);
        LCD::Print(F("MAC "));     LCD::Print(NET::mac2string());
        LCD::SetCursor(0,3);
    #ifdef NET
    #ifdef DHCP
        LCD::Print(F("DHCP ON"));
    #else
        LCD::Print(F("DHCP OFF"));
    #endif
    #else

    #endif
    }
    
    void MQTTstats(void)
    {
        NET::Update::IP();
        LCD::Clear();
        LCD::Print(F("MQTT "));    LCD::Print(MQTT::Checkup());
        LCD::SetCursor(0,1);    
        LCD::Print(F("HOST "));    LCD::Print(MQTT::IP);
        LCD::SetCursor(0,2);
        LCD::Print(F("PORT "));    LCD::Print(MQTT::port);
        LCD::SetCursor(0,3);
        LCD::Print(F("ID "));      LCD::Print(MQTT::groupId);
    }
#endif

    void Bootmessage(void)
    {
        LCD::Clear();
        LCD::Print(F("ARDUINO BOOT ONLINE"));
    }

    void Default(void)
    {
        LCD::Clear();
        LCD::Print(F("Unmapped key"));
    }

    void Playlist(void)
    {
        LCD::Clear();
        LCD::Print(F("Playing Music~"));
        MusicPlayer::playSong();
        Keypad::Default();
    }

    inline void Init(void)
    {
        Bootmessage();
    }

    inline void Exec(void)
    {
        switch(Keypad::keycode)
        {
        #ifdef NET
            case KEY(A):    IPstats();          break;
            case KEY(B):    HWstats();          break;
            case KEY(C):    MQTTstats();        break;
        #endif
            case KEY(D):    Summary();          break;
            case KEY(STAR): WindDirection();    break;
            case KEY(HASH): WindSpeed();        break;
            case KEY(5):    Playlist();         break;
            default:        Default();          break;
        }
    }
}
