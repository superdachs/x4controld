#include <Wire.h>

#define j1x A1
#define j1y A2

int j1b = 12;

String status = "00000000000";

void setup() {
  pinMode(j1b, INPUT_PULLUP);
  
  Serial.begin(9600);
  Wire.begin(10);
  Wire.onRequest(requestEvent);
}

char* j1xv;
char* j1yv;
String j1bv;

void loop() {
  sprintf(j1xv, "%04d", analogRead(j1x));
  sprintf(j1yv, "%04d", analogRead(j1y));
  j1bv = String(digitalRead(j1b));
  status = "00" + j1bv + j1xv + j1yv + "\n";
  Serial.println(status);
  delay(100);
}

void requestEvent() {
  Serial.println("got request!");
  Wire.write(status.c_str());
  Serial.print("sent: ");
  Serial.println(status);
}
