#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

const char* ssid = "FRITZ!Box-Asboeck";
const char* password = "Robby2222!";

#define DHTPIN 2     // DHT11 Sensor Pin - GPIO2 (D4)
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

ESP8266WebServer server(80);

void handleRoot() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Testwerte für pH-Wert, Pumpen und Lampe
  float pHValue = 7.2; // Beispielwert für den pH-Wert
  bool pump1Status = true; // Beispielwert für Pumpe 1
  bool pump2Status = false; // Beispielwert für Pumpe 2
  bool lampStatus = true; // Beispielwert für die Lampe

  String webpage = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>DHT11 Sensor Data</title>";
  webpage += "<style>body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; } .container { max-width: 600px; margin: 0 auto; background-color: #e0e0e0; padding: 20px; border-radius: 10px; box-shadow: 0px 0px 10px 0px rgba(0,0,0,0.1); } .logo { font-family: 'Courier New', Courier, monospace; } h2 { margin-top: 20px; font-family: 'Verdana', sans-serif; text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2); } .status { font-weight: bold; padding: 5px 10px; border-radius: 5px; } .status-on { background-color: #4CAF50; color: white; } .status-off { background-color: #f44336; color: white; } .sensor-container { margin-top: 30px; text-align: left; background-color: #d0d0d0; padding: 15px; border-radius: 5px; flex: 1; margin: 10px; }</style></head><body>";
  webpage += "<div class=\"container\">";
  
  // Logo
  webpage += "<div class=\"logo\">";
  webpage += "<pre>";
  webpage += " _____             ______ _                       \n";
  webpage += "|  ___|            | ___ \\ |                      \n";
  webpage += "| |__  __ _ _______| |_/ / | ___   ___  _ __ ___  \n";
  webpage += "|  __|/ _` |_  / _ \\ ___ \\ |/ _ \\ / _ \\| '_ ` _ \\ \n";
  webpage += "| |__| (_| |/ /  __/ |_/ / | (_) | (_) | | | | | |\n";
  webpage += "\\____/\\__,_/___\\___\\____/|_|\\___/ \\___/|_| |_| |_|\n";
  webpage += "</pre>";
  webpage += "</div>";

  // Großer Container für die Unterpunkte
  webpage += "<div class=\"container\" style=\"display: flex; flex-wrap: wrap; justify-content: space-between;\">";

  // Sensor Data
  webpage += "<div class=\"sensor-container\">";
  webpage += "<h2>Sensor Data</h2>";
  webpage += "<p>Humidity: " + String(humidity, 2) + "%<br>Temperature: " + String(temperature, 2) + "°C</p>";
  webpage += "</div>";

  // pH-Wert
  webpage += "<div class=\"sensor-container\">";
  webpage += "<h2>pH Value</h2>";
  webpage += "<p>pH Value: " + String(pHValue) + "</p>";
  webpage += "</div>";

  // Pumpen
  webpage += "<div class=\"sensor-container\">";
  webpage += "<h2>Pumps</h2>";
  webpage += "<p>Pump 1 Status: <span class=\"status status-" + String(pump1Status ? "on\">ON" : "off\">OFF") + "</span></p>";
  webpage += "<p>Pump 2 Status: <span class=\"status status-" + String(pump2Status ? "on\">ON" : "off\">OFF") + "</span></p>";
  webpage += "</div>";

  // Lampe
  webpage += "<div class=\"sensor-container\">";
  webpage += "<h2>Lamp</h2>";
  webpage += "<p>Lamp Status: <span class=\"status status-" + String(lampStatus ? "on\">ON" : "off\">OFF") + "</span></p>";
  webpage += "</div>";

  // Ende des großen Containers für die Unterpunkte
  webpage += "</div>";

  webpage += "</div>"; // Ende des container-Divs
  
  webpage += "</body></html>";

  server.send(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(DHTPIN, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(1000); // Jede Sekunde aktualisieren
}
