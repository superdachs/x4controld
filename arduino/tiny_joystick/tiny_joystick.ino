#include <TinyWire.h>

void setup() {
 TinyWire.begin(50);
 TinyWire.onRequest(requestEvent);
 pinMode(1, INPUT);
 pinMode(A3, INPUT);
 pinMode(A2, INPUT);
 digitalWrite(1, HIGH);
}

int x;
int y;
int s;
char* status = "00000000000";

void loop() {
 s = digitalRead(1);
 x = analogRead(A3);
 y = analogRead(A2);
} 

void requestEvent() {
  sprintf(status, "%01d%04d%04d", s, x, y);
  sendText(status);
}

void sendText(char *buffer) {
  for(int pos = 0; pos < 10; pos++) {
    TinyWire.send(buffer[pos]);
  }
}
