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
        char* username = "a731fsd4";
        char* password = "tamk";
        char* id = username;
        struct {
            char* in = "ICT4_in_2020";
            char* out = "ICT4_out_2020";
        } topic ;
    } host ;

    void Callback(char*,uint8_t*,uint8_t);

    PubSubClient* client = 00;

    bool Error(void)
    {
        Serial.println("MQTT failed to connect");
        return false;
    }

    bool Connect(void)
    {
        if( not client->connected() )
        {
            Serial.println("Connecting...");
            if( client->connect( host.username ) )
            {
                Serial.println("Connection established");
            } else {
                return Error();
            }
        }
        delay(hz2millis(2));
        return true;
    }

    bool Handshake(void)
    {
        for(uint8_t i=0; i<3 ; i++);
            if( Connect() )
                return true;
        return false;
    }

    bool Send(void)
    {
        if( client -> connected() ) {
            client -> publish( host.topic.out , buf );
            return true;
        } else {
            return false; 
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

    bool Session(void)
    {
        Serial.println("Beginning MQTT session...");
        if( Handshake() ) {
            Serial.println("MQTT session active");
            return true;
        } else {
            Serial.println("MQTT failed");
            return false;
        }
    }

    void POST(void)
    {
        sprintf(buf,"{\"device_id\":\"%s\",\"data\":{\"wind_speed\":%i,\"wind_direction\":%i}}",host.username,WindSpeed::Value(),WindDirection::Value());
        if( not Send() )
        {
            Error();
            Session();
        }
    }

    void Init(void)
    {
        if(not client)
        {
            static PubSubClient host( ip, port, NET::interface );
            client = &host;
        }
    }
}
