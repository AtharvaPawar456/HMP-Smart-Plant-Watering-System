#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Pin definitions
const int relayPin = 5;
const int buzzerPin = D2;
const int soilPin = A0;  // Analog pin for ESP8266

// Threshold and API Key
const int soilThreshold = 40;
const char* apiKey = "WRITE API KEY";

// Wi-Fi credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";

void blinkBuzzer(){
  digitalWrite(buzzerPin, HIGH);delay(300);                  
  digitalWrite(buzzerPin, LOW);delay(500);

  digitalWrite(buzzerPin, HIGH);delay(300);                  
  digitalWrite(buzzerPin, LOW);delay(1000);

}

// Function to connect to Wi-Fi
void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

// Function to send data to ThingSpeak
void updateThingSpeak(int soilValue, int relayState) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;  // Create WiFiClient object
    HTTPClient http;
    
    // Using HTTP instead of HTTPS
    String url = "http://api.thingspeak.com/update?api_key=" + String(apiKey) + "&field1=" + String(soilValue) + "&field2=" + String(relayState);

    Serial.println("url: " + url);  // Print the URL for debugging

    http.begin(client, url);  // Pass the WiFiClient object and the HTTP URL
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("Data sent to ThingSpeak: " + payload);
    } else {
      Serial.println("Error sending data to ThingSpeak: " + String(httpResponseCode));
    }
    
    http.end();
  } else {
    Serial.println("WiFi disconnected. Cannot send data.");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize pins
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Initially turn off the relay
  digitalWrite(buzzerPin, LOW); // Initially turn off the buzzer

  // Connect to Wi-Fi
  connectWiFi();
  blinkBuzzer();
}

void loop() {
  // Read soil moisture value (analog input)
  int soilRaw = analogRead(soilPin); 
  // int soilValue = map(soilRaw, 0, 1023, 0, 100); // Map to 0-100 range using built-in map()
  int soilValue = map(1023 - soilRaw, 0, 1023, 0, 100); // Invert the raw value and map to 0-100

  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  // Control relay and buzzer based on threshold
  int relayState;
  if (soilValue >= soilThreshold) {
    digitalWrite(relayPin, LOW);  // Turn off relay
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    Serial.println("Pump : OFF");
    delay(1000); // 15 seconds


    relayState = 0;
  } else {
    digitalWrite(relayPin, HIGH); // Turn on relay
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
    Serial.println("Pump : ON");
    delay(1000); // 15 seconds

    relayState = 1;
  }
  digitalWrite(relayPin, LOW);  // Turn off relay
  digitalWrite(buzzerPin, LOW); // Turn off buzzer


  // Update ThingSpeak with soil moisture and relay state
  updateThingSpeak(soilValue, relayState);
  blinkBuzzer();

  // Delay before the next reading
  delay(15000); // 15 seconds
}
