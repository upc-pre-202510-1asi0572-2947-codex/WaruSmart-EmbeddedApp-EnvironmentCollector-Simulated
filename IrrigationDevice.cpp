#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

/// @brief Constructor that assigns references to the DHT and soil sensors
IrrigationDevice::IrrigationDevice(DhtSensor& dhtSensor, SoilMoistureSensor& soil)
    : dht(dhtSensor), soil(soil) {}

/// @brief Initializes serial communication, sensors, and WiFi connection
void IrrigationDevice::setup() {
    Serial.begin(115200);
    dht.begin();
    soil.begin();
    connectWiFi();
}

/// @brief Main loop that reads sensor data, sends JSON, and handles logic
void IrrigationDevice::loop() {
    dht.update();
    soil.update();

    if (!dht.valid) {
        Serial.println("Failed to read DHT sensor.");
        delay(2000);
        return;
    }

    Serial.printf("Temperature: %.1f °C | Humidity: %.1f %%\n", dht.temperature, dht.humidity);

    float soilMoisture = soil.getPercentage();

    if (!soilMoisture) {
        Serial.println("Failed to read soil moisture sensor.");
        delay(2000);
        return;
    }

    Serial.printf("Soil Moisture: %.1f %%\n", soilMoisture);

    // Generate JSON payload
  String jsonPayload = "{";
          jsonPayload += "\"device_id\":\"waru-smart-001\",";
          jsonPayload += "\"soil_moisture\":" + String(soilMoisture, 1) + ",";
          jsonPayload += "\"temperature\":" + String(dht.temperature, 1) + ",";
          jsonPayload += "\"humidity\":" + String(dht.humidity, 1) + ",";
          jsonPayload += "\"zone\":\"C\"";
          jsonPayload += "}";

    Serial.println("Generated JSON:");
    Serial.println(jsonPayload);

    sendData(jsonPayload);

    delay(10000);
}

/// @brief Connects to the specified WiFi network
void IrrigationDevice::connectWiFi() {
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected.");
}

/// @brief Sends the JSON payload to the backend API
/// @param jsonPayload The formatted JSON string to send
void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // URL must point to the private gateway IP when using Wokwi
        http.begin("http://192.168.100.7:5000/api/v1/monitoring/device-metrics"); 

        http.addHeader("Content-Type", "application/json");
        http.addHeader("x-api-key", "test-api-key-123");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            Serial.printf("POST sent. HTTP response code: %d\n", httpResponseCode);
            String response = http.getString();
            Serial.println("Server response:");
            Serial.println(response);
        } else {
            Serial.printf("POST failed: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}
