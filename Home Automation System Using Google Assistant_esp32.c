#include <BlynkSimpleEsp32.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#define RelayPin1 23  // D23
#define RelayPin2 22  // D22
#define SwitchPin1 13  // D13
#define SwitchPin2 12  // D12

#define VPIN_BUTTON_1 V1
#define VPIN_BUTTON_2 V2
int toggleState_1 = 1; // Toggle state for relay 1
int toggleState_2 = 1; // Toggle state for relay 2
ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
#define AUTH "YOUR_BLYNK_AUTH_TOKEN"
#define WIFI_SSID "Rahul"
#define WIFI_PASS "Gopal@1206"
void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, toggleState_1);
}
BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, toggleState_2);
}
void setup() {
  Serial.begin(9600);
  btStart();
  SerialBT.begin("ESP32_BT");
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);

  config1.setEventHandler(handleEvent1);
  config2.setEventHandler(handleEvent2);
  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Blynk.config(AUTH);
  delay(2000);
}
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    // Handle WiFi not connected
  } else {
    Blynk.run();
  }
  button1.check();
  button2.check();
}
void handleEvent1(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_1 = 0;
      digitalWrite(RelayPin1, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      break;
    case AceButton::kEventReleased:
      toggleState_1 = 1;
      digitalWrite(RelayPin1, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
      break;
  }
}

void handleEvent2(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_2 = 0;
      digitalWrite(RelayPin2, LOW);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      break;
    case AceButton::kEventReleased:
      toggleState_2 = 1;
      digitalWrite(RelayPin2, HIGH);
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
      break;
  }
}
