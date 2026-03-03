#include <WiFi.h>
#include "DHT.h"

// Set up the DHT22 sensor
#define DHTPIN 14     
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

// Your Wi-Fi Credentials
const char* ssid     = "iPhone";
const char* password = "Zarm9795";

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(2000); // Wait 2 seconds between measurements

  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Temperature in Celsius

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  Temperature: ");
  Serial.print(t);
  Serial.println("°C");
}
