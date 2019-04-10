#include <HardWire.h>

#define j1x A1
#define j1y A2

int j1b = 12;

char* status;

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
  String st = "00" + j1bv + j1xv + j1yv + "\n";
  st.toCharArray(status, 15);
  Wire.beginTransmission(1);
  Wire.write("Hallo");
  int stat = Wire.endTransmission();
  Serial.write(stat);
  delay(1000);
}

void requestEvent() {
  status = "Hallo";
  Serial.println("got request!");
  Wire.write(status);
  Serial.print("sent: ");
  Serial.println(status);
}
