#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid = "FRITZ!Box-Asboeck";
const char* password = "Robby2222!";

const int DHTPin = D4; // Pin, an dem der DHT11-Sensor angeschlossen ist
const int DHTType = DHT11; // Typ des DHT-Sensors

DHT dht(DHTPin, DHTType);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  dht.begin();

  // Verbindung zum WiFi-Netzwerk herstellen
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start des Web Servers
  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<head>");
  client.println("<meta http-equiv='refresh' content='5'>"); // Aktualisiere die Seite alle 5 Sekunden
  client.println("<title>ESP8266 DHT11 Web Server</title>");
  client.println("</head>");

  client.println("<body>");

  client.println("<h1>ESP8266 DHT11 Web Server</h1>");

  client.println("<h2>Current Temperature and Humidity</h2>");
  
  // Sensorwerte abrufen
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  client.print("<p>Temperature: ");
  client.print(temperature);
  client.println(" °C</p>");
  client.print("<p>Humidity: ");
  client.print(humidity);
  client.println(" %</p>");

  client.println("</body>");
  client.println("</html>");

  delay(1000); // Eine Sekunde warten
}
