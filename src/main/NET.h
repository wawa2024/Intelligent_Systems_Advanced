/******************************************************************************
 * File: ./NET.h
 * Dependencies: Ethernet.h
 ******************************************************************************/
#include <Ethernet.h>

namespace NET 
{
    constexpr uint8_t MAC_6 = 0x73;
    uint8_t mac[6] = { 0x44 , 0x76 , 0x56 , 0x10 , 0x00 , MAC_6 };

    IPAddress
    #ifdef DHCP
            ip,
            dns,
            gw,
            subnet;
    #else
            ip{192,168,0,254},
            dns{1,1,1,1},
            gw{192,168,0,1},
            subnet{255,255,255,0};
    #endif

    EthernetClient interface;

    inline char bin2hex(char c,int i)
    { 
        uint8_t mask = 0b1111; mask = ( i ? compl mask : mask );
        char val = ( c & mask ) >> i;
        return val > 9 ? 87 + val : 48 + val;
    }

    inline char* mac2string(void)
    {
        static char s[13] = {};
        for( uint8_t j = 0, i = 0 ; i < sizeof(mac) ; i++ ) 
            for(uint8_t k = 0 ; k <= 4; k += 4) 
                s[j++] = bin2hex(mac[i],k);
        return s;
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

    inline void Init(void)
    {
        #ifdef DHCP
        if(Ethernet.begin(mac))
            Serial.println("DHCP success");
        else
            Serial.println("DHCP failed");
        #else
        Ethernet.begin(
                        mac,
                        ip,
                        dns,
                        gw,
                        subnet
                        );
        #endif
        Serial.println("NET initialized"); 
    }
}
