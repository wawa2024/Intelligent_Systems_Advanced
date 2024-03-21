/******************************************************************************
 * File: ./Protocol.h
 * Dependencies: Ethernet.h SPI.h MQTT.h
 * Requires: NET.h
 ******************************************************************************/
#include <MQTT.h>

namespace MQTT
{
    MQTTClient client;

    struct Host {
        IPAddress ip;
        char* id, username, password;
    } remote ;

    inline void Connect(void)
    {
        
    }

    inline void POST(char*,int size)
    {

    }

    inline void Init(void)
    {
        client.begin(remote.ip,NET::interface);
    }
}
