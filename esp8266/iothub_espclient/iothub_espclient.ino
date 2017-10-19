// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


// Use Arduino IDE 1.6.8 or later.

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <SPI.h>

// for ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>

#include <AzureIoTHub.h>
#include <AzureIoTUtility.h>
#include <AzureIoTProtocol_MQTT.h>

#include "simplesample_mqtt.h"

static char ssid[] = "<<SSID>>";     // your network SSID (name)
static char pass[] = "<<Password>>";    // your network password (use for WPA, or use as key for WEP)


void setup() {
    initSerial();
    initWifi();
    initTime();
    pinMode(16,OUTPUT);
}

void loop() {
    simplesample_mqtt_run();
}

void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    while(!Serial);
    Serial.setDebugOutput(true);
}

void initWifi() {

    // check for the presence of the shield :
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }

    // attempt to connect to Wifi network:
    Serial.println("");
    Serial.println("InitWiFi");
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);

    Serial.println("Waiting for Wifi connection.");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("#");
        delay(500);
    }

    Serial.println("Connected to wifi");
}

void initTime() {
    time_t epochTime;

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        epochTime = time(NULL);

        if (epochTime == 0) {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        } else {
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }

}
