#include <WiFi.h>
#include "DHT.h"

// Your Wi-Fi Credentials
const char* ssid     = "iPhone";
const char* password = "Zarm9795";

// Sensor Setup
const int DHTPIN = 14;     
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Create a Web Server on port 80 (standard for websites)
WiFiServer server(80);

void setup() {
  pinMode(12, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(15, OUTPUT);

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

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // THIS IS THE ADDRESS YOU WILL TYPE INTO YOUR PHONE

  server.begin();
}

void loop() {
  // Check if a phone or computer is trying to connect
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client connected.");
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            
            // Read sensor data
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            int airValue = analogRead(34);

            // Send the HTTP header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // The actual Website Content (HTML)
            client.println("<html><head><title>ESP32 Weather Station</title></head>");
            client.println("<body style='font-family: Arial; text-align: center;'>");
            client.println("<h1>ESP32 Live Weather Station</h1>");
            client.print("<p style='font-size: 24px;'>Temperature: <b>");
            client.print(t);
            client.println(" &deg;C</b></p>");
            client.print("<p style='font-size: 24px;'>Humidity: <b>");
            client.print(h);
            client.println(" %</b></p>");
            client.print("<p style='font-size: 24px;'>Air Quality: <b>");
            client.print(airValue);
            client.println("</p>");
            client.println("</b></p>");
            client.println("<button onclick='location.reload()'>Refresh Data</button>");
            client.println("</body></html>");
            
            client.println();
            break; 
            if (h > 30) {
              digitalWrite(12, HIGH);
              digitalWrite(33, LOW);
              digitalWrite(15, LOW);
            } else if (t > 28) {
              digitalWrite(12, LOW);
              digitalWrite(33, HIGH);
              digitalWrite(15, LOW);
            } else {
              digitalWrite(12, LOW);
              digitalWrite(33, LOW);
              digitalWrite(15, HIGH);
            }
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}