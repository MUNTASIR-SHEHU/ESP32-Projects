#include "AdafruitIO_WiFi.h"
#include <WiFi.h>
#include "DHT.h"

// Your Adafruit IO Credentials
#define IO_USERNAME  "add user name from adafruit"
#define IO_KEY       "add IO key from adafruit"

// Your Wi-Fi Credentials
#define WIFI_SSID    "wifi name"
#define WIFI_PASS    "wifi password"

const int DHTPIN = 14;     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Connect to the Adafruit IO Service
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the Feed (Make sure the name matches exactly what you typed on the website)
AdafruitIO_Feed *tempFeed = io.feed("weather-station-beta");
AdafruitIO_Feed *humidityFeed = io.feed("humidity");

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO AND WIFI");
  io.connect();

  // Wait for connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  io.run(); // Keeps the connection alive

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
  
  // This is the magic line that sends data to your cloud feed!
  Serial.println("Sending data to Adafruit IO...");
  tempFeed->save(t);
  humidityFeed->save(h);

  delay(30000); // Wait 30 seconds (don't send data too fast on a free account)
}