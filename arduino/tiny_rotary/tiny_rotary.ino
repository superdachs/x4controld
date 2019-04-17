#include <Encoder.h>
#include <TinyWire.h>

const int CLK = 3;
const int DT = 4;
const int SW = 1;
long oldPos = -999;

Encoder rotEnc(DT,CLK);

void setup() {
  pinMode(SW, INPUT);
  TinyWire.begin(51);
  TinyWire.onRequest(requestEvent);
}

long p;
int s;
char* status = "00000000000";

void loop(){
  p = oldPos;
  s = digitalRead(SW);
  
  long newPos = rotEnc.read(); 
    if (newPos != oldPos)  {
      oldPos = newPos;       
    }
}

void requestEvent() {
  sprintf(status, "%01d%08d", s, p);
  sendText(status);
}

void sendText(char *buffer) {
  for(int pos = 0; pos < 10; pos++) {
    TinyWire.send(buffer[pos]);
  }
}
