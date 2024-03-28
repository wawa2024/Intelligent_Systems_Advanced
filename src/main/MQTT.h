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

    char* clientId = "a731fsd4";
    PubSubClient client( ip, port, NET::interface );

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
            Serial.println("Sending MQTT package");
            client.publish(topic.out,buf);
        } else {
            Error();
        }
    }

    void POST(void)
    {
        sprintf(buf,"{\"device_id\":\"%s\",\"data\":",clientId);
        Send();
        sprintf(buf,"{\"wind_speed\":%i,",WindSpeed::Value());
        Send();
        sprintf(buf,"\"wind_direction\":%i}}",WindDirection::Value());
        Send();
    }

    void Init(void)
    {
        Serial.println("MQTT initialized");
    }
}
