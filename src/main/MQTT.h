/******************************************************************************
 * File: ./Protocol.h
 * Dependencies: Ethernet.h PubSubClient.h
 * Requires: NET.h
 ******************************************************************************/
#include <PubSubClient.h>

namespace MQTT
{
    static char buf[256] = {};

    uint16_t port = 1883;
    uint8_t ip [4] = { 10,6,0,21 };
    struct {
        char* in = "ICT4_in_2020";
        char* out = "ICT4_out_2020";
    } topic ;

    char* groupId = "jrmlwwk2024";
    char* clientId = "a731fsd4";

    EthernetClient interface;
    PubSubClient client( ip, port, interface );

    void Error(void)
    {
        Serial.println("MQTT failed to connect");
        return false;
    }

    void Send(void)
    {
        if( not client.connected() )
        {
            Serial.println("MQTT connecting...");
            if( client.connect(clientId) )
            {
                Serial.println("MQTT connection established");
            } else {
                Error();
            }
        }
        if( client.connected() ) {
            Serial.print("Sending MQTT package: ");
            Serial.println(buf);
            client.publish(topic.out,buf);
        } else {
            Error();
        }
    }

    void POST(void)
    {
        sprintf(buf,"IOTJS={\"S_name1\": \"%s_tsuunta\", \"S_value1\": %d}",groupId,WindDirection::Value());
        Send();
        sprintf(buf,"IOTJS={\"S_name2\": \"%s_tnopeus\", \"S_value2\": %d}",groupId,WindSpeed::Value());
        Send();
    }

    void Init(void)
    {
        Serial.println("MQTT initialized");
    }
}
