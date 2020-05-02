#include <ArduinoJson.h>
StaticJsonDocument<200> JSON_Packet;
const int ledCount = 10;    // the number of LEDs in the bar graph
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

int ledPins[] = {
  4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};   // an array of pin numbers to which LEDs are attached


void setup() {
  Serial.begin(115200);
  inputString.reserve(200);
   for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}
int ledLevel;
void loop() {
  if(stringComplete) {
    DeserializationError error = deserializeJson(JSON_Packet, inputString);
    inputString = "";
    stringComplete = false;
    if (!error) {
      if(JSON_Packet.containsKey("freq"))
        ledLevel=JSON_Packet["freq"];
        for (int thisLed = 0; thisLed < ledCount; thisLed++) {
          if (thisLed < ledLevel) {
            digitalWrite(ledPins[thisLed], HIGH);
          }
          // turn off all pins higher than the ledLevel:
          else {
            digitalWrite(ledPins[thisLed], LOW);
          }
      }
    }     
    JSON_Packet.clear();
    inputString = "";
    stringComplete = false;
    }
}



void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if(inChar!=0x0A) 
      inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == 0x0D) {
      stringComplete = true;
    }
  }
}
