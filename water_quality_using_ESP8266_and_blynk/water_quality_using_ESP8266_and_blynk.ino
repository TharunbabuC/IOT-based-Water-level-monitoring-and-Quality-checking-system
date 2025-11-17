#define BLYNK_TEMPLATE_ID "TMPL31V38NsIs"
#define BLYNK_TEMPLATE_NAME "water level"
#define BLYNK_AUTH_TOKEN "Glce_5rvDSmChVFo6vukFSyy3FqXu20X"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_SDA 4
#define OLED_SCL 5

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
#define TRIGGER_PIN 12          // GPIO12 for ultrasonic trigger
#define ECHO_PIN 13             // GPIO13 for ultrasonic echo
#define PH_ANALOG_PIN A0        // Analog input pin for pH sensor directly
#define TURBIDITY_PIN 2         // GPIO2 - Digital pin for turbidity sensor

// WiFi credentials
const char* ssid = "bro";
const char* pass = "tharunbabu";

// Tank dimensions
const int tankHeight = 100;  // cm

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Water Quality Monitor");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  // Initialize pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TURBIDITY_PIN, INPUT);  // Digital input for turbidity
}

void loop() {
  Blynk.run();  // Runs Blynk for app connection

  // Read sensor values
  int distance = getDistance();
  int waterLevel = map(distance, 0, tankHeight, 100, 0);
  float pHValue = getPHValue();  // Read pH value directly from A0
  int turbidity = digitalRead(TURBIDITY_PIN);   // Digital read for turbidity sensor

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Water Quality Monitor");

  display.setCursor(0, 12);
  display.print("Water Level: ");
  display.print(waterLevel);
  display.println("%");

  display.setCursor(0, 24);
  display.print("pH Level: ");
  display.print(pHValue, 2);  // Display pH with two decimal precision

  display.setCursor(0, 36);
  display.print("Turbidity: ");
  display.print(turbidity == HIGH ? "Clear" : "Cloudy");

  display.display();

  // Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Water Level: ");
  Serial.print(waterLevel);
  Serial.print("%, pH Level: ");
  Serial.print(pHValue);
  Serial.print(", Turbidity: ");
  Serial.println(turbidity == HIGH ? "Clear" : "Cloudy");

  // Send data to Blynk
  Blynk.virtualWrite(V0, waterLevel);
  Blynk.virtualWrite(V1, pHValue);
  Blynk.virtualWrite(V3, turbidity == HIGH ? 1 : 0);  // 1 for Clear, 0 for Cloudy

  delay(1000);
}

// Function to calculate distance from ultrasonic sensor
int getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;  // Distance in cm
  return distance;
}

// Function to read pH value from pH sensor
float getPHValue() {
  int sensorValue = analogRead(PH_ANALOG_PIN);  // Read analog voltage from A0
  float voltage = sensorValue * (3.3 / 1023.0);  // Convert to voltage (3.3V for ESP8266)
  
  // Assuming voltage of 0-3.0V maps to pH range 0-14
  float pHValue = voltage * (14.0 / 3.0);  // Adjust to map sensor value to pH range
  return pHValue;
}

