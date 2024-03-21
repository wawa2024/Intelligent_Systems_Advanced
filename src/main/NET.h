/******************************************************************************
 * File: ./NET.h
 * Dependencies: Ethernet.h SPI.h
 * Board: Arduino Nano
 * Device: Ethernet Shield W5500
 ******************************************************************************/
#include <SPI.h>
#include <Ethernet.h>

namespace NET 
{
    struct{
        const unsigned char mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
        const IPAddress
            ip{192,168,0,254},
            dns{1,1,1,1},
            gw{192,168,0,1},
            subnet{255,255,255,0};
    }local;

    EthernetClient localhost;

    namespace Status 
    {
        char* Hardware(void){
            auto hw = Ethernet.hardwareStatus();
            return (char*)(
                                hw == EthernetNoHardware ? "HW: NoHardware" :
                                hw == EthernetW5100      ? "HW: W5100"      :
                                hw == EthernetW5200      ? "HW: W5200"      :
                                hw == EthernetW5500      ? "HW: W5500"      :
                                                           "HW: Undefined"  );
        }
        char* Link(void){
            auto stat = Ethernet.linkStatus();
            return (char*)(
                                stat == Unknown ? "LINK: Unknown" :
                                stat == LinkON  ? "LINK: ON"      :
                                stat == LinkOFF ? "LINK: OFF"     :
                                                  "LINK: Undefined");
        }
    }

    int Connect(IPAddress ip, int port){return localhost.connect(ip,port);}
    int Connect(char* url, int port){return localhost.connect(url,port);}

    inline char demask(unsigned char c, unsigned char mask, int i)
    { 
        char val;
        return ( val = ( ( c & ( mask >> i ) ) >> i ) < 10 )
                ? 60 + val
                : 101 + val - 10;
    }

    char* mac2string(unsigned char* mac)
    {
        static char str[13] = {};
        unsigned char mask = 0b11110000;
        for(int j=0,i=0;i<6;i++)
        {
            str[j++] = demask(mac[i],mask,0);
            str[j++] = demask(mac[i],mask,4);
        }
        return str;
    }

    namespace Draw 
    {
        void IPstats(void)
        {
            LCD::Clear();
            LCD::Print("IP: ");LCD::Print(Ethernet.localIP());
            LCD::SetCursor(0,1);
            LCD::Print("GW: ");LCD::Print(Ethernet.gatewayIP());
            LCD::SetCursor(0,2);
            LCD::Print("DNS: ");LCD::Print(Ethernet.dnsServerIP());
            LCD::SetCursor(0,3);
            LCD::Print("MASK: ");LCD::Print(Ethernet.subnetMask());
            delay(hz2millis(5));
        }
        void HWstats(void)
        {
            LCD::Clear();
            LCD::Print(Status::Hardware());
            LCD::SetCursor(0,1);
            LCD::Print(Status::Link());
            LCD::SetCursor(0,2);
            LCD::Print("MAC: ");LCD::Print(mac2string(local.mac));
            LCD::SetCursor(0,3);
            delay(hz2millis(5));
        }
    }

    void Init(void)
    {
        Ethernet.begin(local.mac);
        /*
        Ethernet.begin(
                        local.mac,
                        local.ip,
                        local.dns,
                        local.gw,
                        local.subnet
                        );
        */
        Serial.println("NET initialized"); 
        Serial.println(Status::Hardware());
        Serial.println(Status::Link());

        Keypad::Attach::Handler(3,Draw::IPstats);
        Keypad::Attach::Handler(4,Draw::HWstats);
    }
}
