#include "arduino_secrets.h"



#include "thingProperties.h"

const int s1 = D0; 
const int s2 = D3; 

bool s1State = false;  

void setup() {
  Serial.begin(9600);
  delay(1500); 

  pinMode(s1, OUTPUT);
  pinMode(s2, INPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  checkIRSensor();  
}


void onLedChange()  {
  if (led) {
    digitalWrite(s1, HIGH);
    s1State = true;
    Serial.println("Cloud: LED ON");
  } else {
    digitalWrite(s1, LOW);
    s1State = false;
    Serial.println("Cloud: LED OFF");
  }
}


void checkIRSensor() {
  static bool objectPreviouslyDetected = false;

  bool objectDetected = digitalRead(s2) == LOW;  

  if (objectDetected && !objectPreviouslyDetected) {
    Serial.println("IR Sensor: Object detected");

    
    s1State = !s1State;
    digitalWrite(s1, s1State ? HIGH : LOW);
    Serial.println(s1State ? "IR: LED turned ON" : "IR: LED turned OFF");

    
    led = s1State;
  }

  objectPreviouslyDetected = objectDetected;

  delay(200);  
}
