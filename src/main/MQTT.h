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

    char* clientId = "a731fsd4";

    struct {
        char* in = "ICT4_in_2020";
        char* out = "ICT4_out_2020";
    } topic ;

    void Callback(char*,uint8_t*,uint8_t);

    PubSubClient* client = 00;

    bool Error(void)
    {
        Serial.println("MQTT failed to connect");
        return false;
    }

    void Connect(void)
    {
        Serial.println("MQTT connecting...");
        if( client->connect( clientId ) )
        {
            Serial.println("MQTT connection established");
        } else {
            Error();
        }
    }

    void Send(void)
    {
        if( not client -> connected() )
        {
            Connect();
        }
        if( client -> connected() ) {
            Serial.println("Sending MQTT package");
            client -> publish( topic.out , buf );
        } else {
            Error();
        }
    }

    void Callback(char* topic, uint8_t* payload, uint8_t size)
    {
        char* msg = (char*) malloc(size + 1);
        memcpy(msg,payload,size);
        msg[size] = NULL;
        Serial.println( msg );
        free(msg);
    }

    void POST(void)
    {
        sprintf(buf,"{\"device_id\":\"%s\",\"data\":",clientId);
        Send();
        sprintf(buf,"{\"wind_speed\":%i,\"wind_direction\":%i}}",WindSpeed::Value(),WindDirection::Value());
        Send();
    }

    void Init(void)
    {
        Serial.println("MQTT initialization");
        if(not client)
        {
            static PubSubClient host( ip, port, NET::interface );
            client = &host;
            Serial.println("MQTT initialized");
        }
    }
}
