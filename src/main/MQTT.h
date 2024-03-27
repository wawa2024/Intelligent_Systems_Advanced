/******************************************************************************
 * File: ./Protocol.h
 * Dependencies: Ethernet.h PubSubClient.h
 * Requires: NET.h
 ******************************************************************************/
#include <PubSubClient.h>

namespace MQTT
{
    static char buf[128] = {};

    constexpr struct {
        uint16_t port = 1883;
        uint8_t ip [4] = { 10,6,0,21 };
    } remote ;

    struct {
        char* username = "jrmlww2024";
        char* password = "tamk";
        char* id = username;
        struct {
            char* in = "ICT1B_in_2020";
            char* out = "ICT1B_out_2020";
        } topic ;
    } host ;

    void Callback(char*,uint8_t*,uint8_t);

    PubSubClient client(remote.ip,remote.port,Callback,NET::interface);

    inline bool Error(void)
    {
        Serial.print("Failed to connect: ");
        Serial.println( client.state() );
        return 0;
    }

    inline bool Connect(void)
    {
        if( not client.connected() )
        {
            Serial.println("Connecting...");
            if( client.connect( host.username , host.id , host.password ) )
            {
                Serial.println("Connection established");
                client.subscribe( host.topic.in );
            } else {
                return Error();
            }
        }
        delay(hz2millis(2));
        return true;
    }

    inline bool Handshake(void)
    {
        for(uint8_t i=0; i<3 ; i++);
            if( Connect() )
                return true;
        return false;
    }

    inline bool Send(void)
    {
        if( client.connected() )
            client.publish( host.topic.out , buf );
        else
            return false; 
        return true;
    }

    void Callback(char* topic, uint8_t* payload, uint8_t size)
    {
        char* msg = (char*) malloc(size + 1);
        memcpy(msg,payload,size);
        msg[size] = NULL;
        Serial.println( msg );
        free(msg);
    }

    inline bool Session(void)
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

    inline void Init(void)
    {
        if( Session() )
        {
            sprintf(buf,"Send MQTT msg: %i/%i/%i\n",2024,3,27);
            Send();
        }
    }
}
