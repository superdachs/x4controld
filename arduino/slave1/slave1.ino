#include <Wire.h>

int j1x = A1;
int j1y = A2;

int j1b = 12;

char* status = "00000000000";

void setup() {
  pinMode(j1b, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  Wire.begin(10);
  Wire.onRequest(requestEvent);
  
}

int j1xv;
int j1yv;
int j1bv;

void loop() {
  j1xv = analogRead(j1x);
  j1yv = analogRead(j1y);
  j1bv = digitalRead(j1b);
  sprintf(status, "00%1d%04d%04d", j1bv, j1xv, j1yv);
  Serial.println(status);
  delay(100);
}

void requestEvent() {
  Serial.println("got request!");
  Wire.write(status);
  Serial.print("sent: ");
  Serial.println(status);
}
