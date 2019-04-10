#include <Wire.h>

#define j1x A1
#define j1y A2

int j1b = 12;

void setup() {
  pinMode(j1b, INPUT_PULLUP);
  
  Serial.begin(9600);
  Wire.begin(25);
  Wire.onRequest(requestEvent);
}

void loop() {
  int j1xv = analogRead(j1x);
  int j1yv = analogRead(j1y);
  int j1bv = digitalRead(j1b);
  Serial.println(j1xv);
  Serial.println(j1yv);
  Serial.println(j1bv);
  delay(100);

}

void requestEvent() {
  Serial.println("got request");
  Wire.write("hello");
}
