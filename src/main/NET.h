/******************************************************************************
 * File: ./NET.h
 * Dependencies: Ethernet.h SPI.h MQTT.h
 * Board: Arduino Nano
 * Device: Ethernet Shield W5500
 ******************************************************************************/
#include <SPI.h>
#include <Ethernet.h>
#include <MQTT.h>

#define DHCP

namespace NET 
{
    constexpr unsigned char MAC_6 = 0x73;
    struct Host {
        unsigned char mac[6] = {0x44,0x76,0x56,0x10,0x00,MAC_6};
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
    } local, remote, loopback;

    EthernetClient interface;

    inline int Connect(IPAddress ip, int port){return interface.connect(ip,port);}
    inline int Connect(char* url, int port){return interface.connect(url,port);}

    inline char demask(char c,int i)
    { 
        uint8_t mask = 0b1111; mask = ( i ? ~mask : mask );
        char val = ( c & mask ) >> i;
        return val > 9 ? 87 + val : 48 + val;
    }

    inline char* mac2string(unsigned char* mac)
    {
        static char str[13] = {};
        for(char j=0,i=0;i<6;i++)
            for(char k=0;k<=4;k+=4)
                str[j++] = demask(mac[i],k);
        return str;
    }

    namespace Status 
    {
        char* Hardware(void){
            EthernetHardwareStatus hw = Ethernet.hardwareStatus();
            return (char*)(
                                hw == EthernetNoHardware ? "HW: NoHardware" :
                                hw == EthernetW5100      ? "HW: W5100"      :
                                hw == EthernetW5200      ? "HW: W5200"      :
                                hw == EthernetW5500      ? "HW: W5500"      :
                                                           "HW: Undefined"  );
        }
        char* Link(void){
            EthernetLinkStatus stat = Ethernet.linkStatus();
            return (char*)(
                                stat == Unknown ? "LINK: Unknown" :
                                stat == LinkON  ? "LINK: ON"      :
                                stat == LinkOFF ? "LINK: OFF"     :
                                                  "LINK: Undefined");
        }
    }

    namespace Update
    {
        inline bool IP(void)
        {
            bool b = false;
            loopback.ip = Ethernet.localIP();
            loopback.gw = Ethernet.gatewayIP();
            loopback.dns = Ethernet.dnsServerIP();
            loopback.subnet = Ethernet.subnetMask();

            if(not(loopback.ip == local.ip))
                local.ip = loopback.ip, b = true;
            if(not(loopback.gw == local.gw))
                local.gw = loopback.gw, b = true;
            if(not(loopback.dns == local.dns))
                local.dns = loopback.dns, b = true;
            if(not(loopback.subnet == local.subnet))
                local.subnet = loopback.subnet, b = true;

            return b;

        }
        inline bool HW(void)
        {
            bool b = false;
            static char* hw, ln;

            struct {
                char* hw, ln;
            } tmp ; 

            tmp.hw = Status::Hardware();
            tmp.ln = Status::Link();

            if(hw != tmp.hw)
                hw = tmp.hw, b = true;
            if(ln != tmp.ln)
                ln = tmp.ln, b = true;

            Ethernet.MACAddress(loopback.mac);
            for(int i=0;i<6;i++)
                if(local.mac[i] == loopback.mac[i])
                    local.mac[i] = loopback.mac[i], b=true;

            return b;
        }

    }

    namespace Draw 
    {
        void IPstats(void)
        {
            do {
                if(Update::IP())
                {
                    LCD::Clear();
                    LCD::Print("IP: ");LCD::Print(local.ip);
                    LCD::SetCursor(0,1);
                    LCD::Print("GW: ");LCD::Print(local.gw);
                    LCD::SetCursor(0,2);
                    LCD::Print("DNS: ");LCD::Print(local.dns);
                    LCD::SetCursor(0,3);
                    LCD::Print("MASK: ");LCD::Print(local.subnet);
                }
                delay(hz2millis(1));
            } while(true);
        }
        void HWstats(void)
        {
            do {
                if(Update::HW())
                {
                    LCD::Clear();
                    LCD::Print(Status::Hardware());
                    LCD::SetCursor(0,1);
                    LCD::Print(Status::Link());
                    LCD::SetCursor(0,2);
                    LCD::Print("MAC: ");LCD::Print(mac2string(local.mac));
                    LCD::SetCursor(0,3);
                    delay(hz2millis(1));
                }
            } while(true);
        }
    }

    inline void Init(void)
    {
        #ifdef DHCP
        #ifdef ASM
            __asm__ __volatile__(
                "cli \n"
            );
        #else
            noInterrupts();
        #endif
            if(Ethernet.begin(local.mac))
                Serial.println("DHCP success");
            else
                Serial.println("DHCP failed");
        #ifdef ASM
            __asm__ __volatile__(
                "sei \n"
            );
        #else
            interrupts();
        #endif
        #else
        Ethernet.begin(
                        local.mac,
                        local.ip,
                        local.dns,
                        local.gw,
                        local.subnet
                        );
        #endif

        Serial.println("NET initialized"); 
        Serial.println(Status::Hardware());
        Serial.println(Status::Link());

        Keypad::Attach::Handler(char2key('A'),Draw::IPstats);
        Keypad::Attach::Handler(char2key('B'),Draw::HWstats);
    }
}
