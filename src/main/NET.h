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
                                hw == EthernetNoHardware ? "hw: NoHardware" :
                                hw == EthernetW5100      ? "hw: W5100"      :
                                hw == EthernetW5200      ? "hw: W5200"      :
                                hw == EthernetW5500      ? "hw: W5500"      :
                                                           "hw: Undefined"  );
        }
        char* Link(void){
            auto stat = Ethernet.linkStatus();
            return (char*)(
                                stat == Unknown ? "link: Unknown" :
                                stat == LinkON  ? "link: ON"      :
                                stat == LinkOFF ? "link: OFF"     :
                                                  "link: Undefined");
        }
    }

    int Connect(IPAddress ip, int port){return localhost.connect(ip,port);}
    int Connect(char* url, int port){return localhost.connect(url,port);}

    void Init(void)
    {
        Ethernet.begin(
                        local.mac,
                        local.ip,
                        local.dns,
                        local.gw,
                        local.subnet
                        );
        Serial.println("NET initialized"); 
        Serial.println(Status::Hardware());
        Serial.println(Status::Link());
    }
}
