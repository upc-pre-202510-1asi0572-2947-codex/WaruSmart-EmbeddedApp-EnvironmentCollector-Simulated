#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>

IrrigationDevice::IrrigationDevice(DhtSensor& dhtSensor, SoilMoistureSensor& soil)
    : dht(dhtSensor), soil(soil) {}

void IrrigationDevice::setup() {
    Serial.begin(115200);
    dht.begin();
    soil.begin();
    connectWiFi();
}

void IrrigationDevice::loop() {
    dht.update();
    soil.update();

    if (!dht.valid) {
        Serial.println("Error al leer el sensor");
        delay(2000);
        return;
    }

    Serial.printf("Temperatura: %.1f °C | Humedad: %.1f %%\n", dht.temperature, dht.humidity);

    float soilMoisture = soil.getPercentage();

    if (!soilMoisture) {
      Serial.println("Error al leer el sensor");
      delay(2000);
      return;
    }

    Serial.printf("Humedad del suelo: %.1f %%\n", soilMoisture);

    String json = "{";
    json += "\"device_id\": \"waru-smart-001\",";
    json += "\"soil_moisture\":" + String(soilMoisture,1) + ",";
    json += "\"temperature\":" + String(dht.temperature, 1) + ",";
    json += "\"humidity\":" + String(dht.humidity, 1) + ",";
    json += "\"zone\": \"C\"";
    json += "}";


    Serial.println("JSON generate:");
    Serial.println(json);

    sendData(json);

    delay(10000);
}

void IrrigationDevice::connectWiFi() {
    WiFi.begin("Wokwi-GUEST", "");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado.");
}

void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // ✅ Apunta al Gateway (IP del simulador)
        http.begin("http://192.168.100.7:5000/api/v1/monitoring/device-metrics"); 

        http.addHeader("Content-Type", "application/json");
        http.addHeader("x-api-key", "test-api-key-123");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            Serial.printf("POST enviado. Código de respuesta: %d\n", httpResponseCode);
            String response = http.getString();
            Serial.println("Respuesta del servidor:");
            Serial.println(response);
        } else {
            Serial.printf("Error en POST: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("No hay conexión WiFi para enviar los datos.");
    }
}
