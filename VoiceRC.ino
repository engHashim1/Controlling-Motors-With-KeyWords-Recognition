#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "HW1-E5172-1546";
const char* password = "QH0J51DHE30";

String serverUrl = "http://192.168.1.7/motor/get_command.php";

const int IN1 = 26; 
const int IN2 = 27;
const int IN3 = 14;
const int IN4 = 12;

String lastCommand = "";
unsigned long lastCommandTime = 0;
const unsigned long autoStopDelay = 5000; 

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    int httpCode = http.GET();

    if (httpCode == 200) {
      String payload = http.getString();
      payload.trim();
      Serial.println("Command: " + payload);

      if (payload != lastCommand) {
        lastCommand = payload;
        lastCommandTime = millis();

        if (payload.equalsIgnoreCase("forward")) {
          forward();
        } else if (payload.equalsIgnoreCase("backward")) {
          backward();
        } else if (payload.equalsIgnoreCase("stop")) {
          stopMotors();
        }
      }
    }
    http.end();
  }

  if (millis() - lastCommandTime > autoStopDelay && lastCommand != "stop") {
    stopMotors();
    lastCommand = "stop";
    Serial.println("Auto-stopped after timeout.");
  }

  delay(100);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Moving Forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Moving Backward");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Motors Stopped");
}
