#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "Redmi";
const char* password = "12345678";

// Firebase details
const char* projectID = "mine-health-monitoring";
const char* apiKey = "AIzaSyAwu8gfWgAtmOJg9QDZ3N0BPjbErT4NYUg";
const char* documentPath = "sensors/noise-sensor";  // Collection/document path

int noiseSensorPin = 34;  // Use GPIO34 for analog input

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(noiseSensorPin, INPUT);

  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n WiFi Connected!");
}

void loop() {
  int noiseValue = analogRead(noiseSensorPin);
  Serial.print("Noise Sensor Value: ");
  Serial.println(noiseValue);

  sendToFirestore(noiseValue);
  delay(10000);  // Wait 10 seconds before sending again
}

void sendToFirestore(int value) {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;

    String url = "https://firestore.googleapis.com/v1/projects/" + String(projectID)
               + "/databases/(default)/documents/" + String(documentPath) + "?key=" + apiKey;

    String payload = "{ \"fields\": { \"value\": {\"integerValue\": \"" + String(value) + "\"} } }";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.sendRequest("PATCH", payload);

    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("📨 Firestore Response:");
      Serial.println(response);
    } else {
      Serial.println("❌ Error sending data to Firestore");
    }

    http.end();
  } else {
    Serial.println("❌ WiFi not connected");
  }
}
