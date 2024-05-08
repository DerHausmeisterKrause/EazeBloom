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

  String webpage = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>DHT11 Sensor Data</title>";
  webpage += "<style>body { font-family: Arial, sans-serif; text-align: center; } .logo { font-family: 'Courier New', Courier, monospace; }</style></head><body>";
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
  webpage += "<h1>DHT11 Sensor Data</h1>";
  webpage += "<p>Humidity: " + String(humidity, 2) + "%<br>Temperature: " + String(temperature, 2) + "°C</p>";
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
