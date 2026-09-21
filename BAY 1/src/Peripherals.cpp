#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) {
    return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

// Fixed function name: changed sample_sensors to sample_sensor
void sample_sensor(void)
{
    int raw_current = analogRead(CURRENT_PIN); // 0 to 4095 -> 0 to 32 A
    int raw_voltage = analogRead(VOLTAGE_PIN); // 0 to 4095 -> 0 to 250 V
    
    voltage = mapFloat(raw_voltage, 0, 4095, 0, 250);

    // Fixed: Removed stray semicolon after if condition
    if (bayStatus == "CHARGING") {
        current = mapFloat(raw_current, 0, 4095, 0, 32);
    } else {
        current = 0.0;
    }
//read current and 5 values array
    power = voltage * current;
    
    float t = dht.readTemperature();
    if (!isnan(t)) {
        temperature = t;
    }
} 
float recentAvgCurrent()
{
    float sum =0;
    //read recent five values
    for (int i=0;i<5;i++)
    {
        sum = sum + current;
    }
     return sum/5;

    
}
bool plugin_flag_once = 1;
bool plugout_flag_once = 1;

void plug_status(void)
{
    bool pluginReading = digitalRead(BTN_PLUGIN);
    
    if (pluginReading == LOW && plugin_flag_once)
    {
        //session time
        sessionStartMs = millis();
        plugin_flag_once = 0;
        if (bayStatus == "FREE")
        {
            bayStatus = "CHARGING";
            Serial.println("Bay 1 plugin detected, Bay is CHARGING");
            digitalWrite(RELAY_PIN, HIGH);
        }
    }
    if (pluginReading == HIGH)
    {
        plugin_flag_once = 1;
    }
            
    bool plugoutReading = digitalRead(BTN_PLUGOUT);
    
    if (plugoutReading == LOW && plugout_flag_once)
    {
        plugout_flag_once = 0;
        // Fixed: Removed extra trailing space from "CHARGING "
        if (bayStatus == "CHARGING")
        {
            bayStatus = "FREE";
            Serial.println("Bay 1 plugout detected, Bay is FREE");
            digitalWrite(RELAY_PIN, LOW); // Turn off relay on plugout
        }
    }
    if (plugoutReading == HIGH)
    {
        plugout_flag_once = 1;
    }
}
/*
void update_led_status(void)
{
    if (bayStatus == "FREE")
    {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_YELLOW, LOW);
    }
    else
    {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_YELLOW, HIGH);
    }
}*/