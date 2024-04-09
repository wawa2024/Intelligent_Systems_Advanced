/******************************************************************************
 * File: ./NET.h
 * Dependencies: Ethernet.h
 ******************************************************************************/
#include <Ethernet.h>

namespace NET 
{
    uint8_t mac[6] = { 0x44 , 0x76 , 0x56 , 0x10 , 0x00 , 0x62 };

    IPAddress
            ip{192,168,0,254},
            dns{1,1,1,1},
            gw{192,168,0,1},
            subnet{255,255,255,0};

    char* mac2string(void)
    {
        sprintf(buf,"%02x%02x%02x%02x%02x%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
        return buf;
    }

    namespace Status 
    {
        char* Hardware(void){
            EthernetHardwareStatus hw = Ethernet.hardwareStatus();
            return (char*)(
                                hw == EthernetNoHardware ? "HW NoHardware" :
                                hw == EthernetW5100      ? "HW W5100"      :
                                hw == EthernetW5200      ? "HW W5200"      :
                                hw == EthernetW5500      ? "HW W5500"      :
                                                           "HW Undefined"  );
        }
        char* Link(void){
            EthernetLinkStatus stat = Ethernet.linkStatus();
            return (char*)(
                                stat == Unknown ? "LINK Unknown" :
                                stat == LinkON  ? "LINK ON"      :
                                stat == LinkOFF ? "LINK OFF"     :
                                                  "LINK Undefined");
        }
    }

    namespace Update
    {
        void IP(void)
        {
            ip = Ethernet.localIP();
            gw = Ethernet.gatewayIP();
            dns = Ethernet.dnsServerIP();
            subnet = Ethernet.subnetMask();
        }
    }

    inline void Init(void)
    {
    #ifdef DHCP
        if( Ethernet.begin(mac) )
            Serial.println(F("DHCP success"));
        else
            Serial.println(F("DHCP failed"));
    #else
        Serial.println(F("DHCP off"));
        Ethernet.begin(
                        mac,
                        ip,
                        dns,
                        gw,
                        subnet
                        );
    #endif
    }
}
