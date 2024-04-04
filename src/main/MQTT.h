/******************************************************************************
 * File: ./Protocol.h
 * Dependencies: Ethernet.h PubSubClient.h
 * Requires: NET.h
 ******************************************************************************/
#include <PubSubClient.h>

namespace MQTT
{
    IPAddress IP{10,6,0,21};
    uint16_t port = 1883;
    uint8_t ip [4] = { 10,6,0,21 };
    bool status = false;

    char buf[256] = {};

    struct {
        char* in = "ICT4_in_2020";
        char* out = "ICT4_out_2020";
    } topic ;

    char* groupId = "jrmlwwk2024";

    EthernetClient interface;
    PubSubClient client( ip, port, interface );

    char* Checkup(void)
    {
        return status ? "CONNECTED" : "DISCONNECTED" ;
    }

    void Debug(void)
    {
        static char s_dot[] = ".";
        Serial.print(F("IP "));
        Serial.print(NET::ip);
        Serial.print(F(" > "));
        Serial.print(ip[0]); Serial.print(s_dot); 
        Serial.print(ip[1]); Serial.print(s_dot); 
        Serial.print(ip[2]); Serial.print(s_dot); 
        Serial.print(ip[3]);
        Serial.print(F(": MQTT package, "));
        Serial.println(buf);
    }

    void POST(void)
    {
        static uint8_t i = 0;
        if( i++ < 10 );
        else 
        {
            if( not status )
            {
                Serial.println(F("MQTT connecting..."));
                if( client.connect(groupId) ) 
                    Serial.println(F("MQTT connection established"));
                else 
                    Serial.println(F("MQTT failed to connect"));
            }

            if( status = client.connected() )
            {
                Debug();
                sprintf(buf,"IOTJS={\"S_name1\": \"%s_tsuunta\", \"S_value1\": %d}",groupId,WindDirection::mean);
                client.publish(topic.out,buf);
                Debug();
                sprintf(buf,"IOTJS={\"S_name2\": \"%s_tnopeus\", \"S_value2\": %d}",groupId,WindSpeed::mean);
                client.publish(topic.out,buf);
            }

            i = 0;
        }
    }

    inline void Init(void)
    {
    #ifdef DEBUG_MQTT
        Serial.println(F("MQTT initialized"));
    #endif
    }
}
