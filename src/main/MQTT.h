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

    struct { char* out = "ICT4_out_2020"; } topic ;
    
    char groupId[] = "jrmlwwk2024";

    EthernetClient interface;
    PubSubClient client( ip, port, interface );

    char* Checkup(void)
    {
        return status ? "CONNECTED" : "DISCONNECTED" ;
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

            status = client.connected();

            if( status )
            {
                dtostrf(WindDirection::mean,3,1,var1);
                dtostrf(WindSpeed::mean,3,1,var2);
                sprintf(buf,"IOTJS={\"S_name1\": \"%s_WindDirection\", \"S_value1\": %s, \"S_name2\": \"%s_WindSpeed\", \"S_value2\": %s}",groupId,var1,groupId,var2);

            #ifdef DEBUG
                Serial.println(buf);
            #endif
                client.publish(topic.out,buf);
            }

            i = 0;
        }
    }

    inline void Init(void)
    {
    }
}
