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
                if( status = client.connect(groupId) ) 
                    Serial.println(F("MQTT connection established"));
                else 
                    Serial.println(F("MQTT failed to connect"));
            }

            if( status = client.connected() )
            {
                sprintf(buf,"IOTJS={\"S_name1\": \"jlw_wd\", \"S_value1\": %d, \"S_name2\": \"jlw_ws\", \"S_value2\": %d}",WindDirection::mean, WindSpeed::mean);
                Debug();
                client.publish(topic.out,buf);
            }

            i = 0;
        }
    }

    inline void Init(void)
    {
        status = client.connect(groupId);
    #ifdef DEBUG_MQTT
        Serial.println(F("MQTT initialized"));
    #endif
    }
}
