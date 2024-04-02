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

    struct {
        char* in = "ICT4_in_2020";
        char* out = "ICT4_out_2020";
    } topic ;

    char* groupId = "jrmlwwk2024";
    char* clientId = groupId;

    EthernetClient interface;
    PubSubClient client( ip, port, interface );

    void Error(void)
    {
        Serial.println("MQTT failed to connect");
        return false;
    }

    char* Checkup(void)
    {
        return client.connected() ? "CONNECTED" : "DISCONNECTED";
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
        #ifdef DEBUG_MQTT
            Serial.print("IP ");
            Serial.print(NET::ip);
            Serial.print(" > ");
            Serial.print(ip[0]); Serial.print("."); 
            Serial.print(ip[1]); Serial.print("."); 
            Serial.print(ip[2]); Serial.print("."); 
            Serial.print(ip[3]);
            Serial.print(": MQTT package, ");
            Serial.println(buf);
        #endif
            client.publish(topic.out,buf);
        } else {
            Error();
        }
    }

    void POST(void)
    {
        static uint8_t i = 0;
        if( i++ < 10 );
        else 
        {
            sprintf(buf,"IOTJS={\"S_name1\": \"%s_tsuunta\", \"S_value1\": %d}",groupId,WindDirection::Value());
            Send();
            sprintf(buf,"IOTJS={\"S_name2\": \"%s_tnopeus\", \"S_value2\": %d}",groupId,WindSpeed::Value());
            Send();
            i = 0;
        }
    }

    inline void Init(void)
    {
    #ifdef DEBUG_MQTT
        msgSerial(STRING_MQTT,STRING_initialized);
    #endif
    }
}
