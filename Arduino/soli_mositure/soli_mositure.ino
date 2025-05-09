#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Wi-Fi credentials
const char* ssid = "Vajreshwar";
const char* password = "9892338055";

// Firebase (Firestore)
const char* host = "firestore.googleapis.com";
const char* projectID = "mine-health-monitoring";
const char* apiKey = "AIzaSyAwu8gfWgAtmOJg9QDZ3N0BPjbErT4NYUg";
const char* collection = "sensors"; // Firestore collection name

// Google root certificate (needed for HTTPS)
const char* rootCACert = \
"-----BEGIN CERTIFICATE-----\n" \
"... (use current Google root CA here) ...\n" \
"-----END CERTIFICATE-----\n";

WiFiClientSecure client;
int sensorPin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".\n");
  }
  Serial.println("\nConnected to WiFi!");

  client.setInsecure(); // HTTPS cert
}

void loop() {
  int moisture = analogRead(sensorPin);
  Serial.print("Moisture: ");
  Serial.println(moisture);

  sendToFirestore(moisture);
  delay(10000); // Send every 10 seconds
}

void sendToFirestore(int value) {
  Serial.println("Connecting to Firestore...");

  if (!client.connect(host, 443)) {
    Serial.println("❌ Connection to Firestore failed.");
    return;
  }

  // Construct the document path (we are updating this document)
  String documentPath = "/v1/projects/" + String(projectID) + "/databases/(default)/documents/sensors/soil-moisture?key=" + apiKey;

  // JSON payload to update the moisture field
  String json = "{ \"fields\": { \"value\": {\"integerValue\": \"" + String(value) + "\"} } }";

  Serial.println("✅ Connected!");
  Serial.println("Sending PATCH to Firestore:");
  Serial.println(json);

  client.println("PATCH " + documentPath + " HTTP/1.1");
  client.println("Host: firestore.googleapis.com");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(json.length());
  client.println();
  client.println(json);

  Serial.println("⏳ Waiting for response...");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break; // Headers end
  }

  Serial.println("📩 Firebase response:");
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
  }

  client.stop();
  Serial.println("✅ Done\n");
}
