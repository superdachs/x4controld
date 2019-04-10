#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x26, 20, 4);
LiquidCrystal_I2C lcd2(0x27, 20, 4);

bool cc = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Controller booting");
  Serial.println("init lcd0");
  lcd1.init();
  lcd1.backlight();
  Serial.println("init lcd1");
  lcd2.init();
  lcd2.backlight();
  Serial.println("Controller is up");
}

void loop() {
  
}



void serialEvent() {
  String text = "";
  text.reserve(29);
  char inchr;

  while(inchr != '\n') {
    while(Serial.available()) {
      inchr = (char)Serial.read();
      if(inchr != '\n')
        text += inchr;
    }
  }
  String dev = text.substring(0,4);
  if(dev == "LCD") {
    int dspl = text.substring(4,6).toInt();
    int line = text.substring(6,8).toInt();
    int chr = text.substring(8,10).toInt();
    String txt = text.substring(10,29);
    setDisplay(dspl, line, chr, txt);
  }
  if(dev == "LED") {
    int dev = text.substring(4,6).toInt();
    int led = text.substring(6,8).toInt();
    int val = text.substring(8,10).toInt();
    setLed(led, value);
  }
}  

void setLed(int dev, int led, int value) {
  if(dev == "0") {
    digitalWrite(led, value);
  }
}

void setDisplay(int dspl, int line, int chr, String txt) {
  Serial.println("writing " + txt + " to display " + String(dspl) + " line " + String(line) + " pos " + String(chr) + "\n");
  if(dspl == 0) {
    lcd1.setCursor(chr, line);
    lcd1.print(txt);
  }
  if(dspl == 1) {
    lcd2.setCursor(chr, line);
    lcd2.print(txt);
  }
}
