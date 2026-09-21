#include <Arduino.h>
#include <Wifi.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "Network.h"
#include "Telemetry.h"
#include "model.h"
#include "edge_ai.h"
#include "optimization.h"
#include "rpc.h"
#include "attributes.h"



void setup()
{
    //initialise serial monitor
    Serial.begin(115200);
    dht.begin();  // initialise sesnor
    //config esp32 with real time
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    //configure peripheral pins
    pinMode( BTN_PLUGIN, INPUT_PULLUP);
    pinMode(BTN_PLUGOUT, INPUT_PULLUP );
    pinMode(RELAY_PIN,OUTPUT );
    pinMode(LED_GREEN,OUTPUT );
    pinMode(LED_YELLOW,OUTPUT );
    pinMode(LED_RED,OUTPUT);
    //connect board to wifi
    connectWiFi();
    mqtt.setServer(MQTT_SERVER,MQTT_PORT);//mqtt server address of thingsboard and port number
    //set call  back function upon recieving data from the cloud
    mqtt.setCallback(mqttCallback);
    mqtt.setBufferSize(512);
    connectMQTT(); // Token,Device_ID
}

unsigned long now;
unsigned long last_print;

void loop()
{
    //listen to incoming requests
    mqtt.loop();
    //push data every 5 sec
    now = millis();
    if((now - last_print) > 5000)
    {
        last_print = now;
        //read data from sensor// we are reading voltage,current,temperature and power,bay_status
        sample_sensor();
       
         //run AI to get prediction
        runEdgeAIInference();
        if(  manualOverrideActive==0)
        //decide load based on the prediction
        {
        runOptimization();}
        //push it to cloud
           //publish the data
        publishTelemetry();
        //run AI to get prediction
        

    }
    plug_status();
    updateLeds();

    
}

