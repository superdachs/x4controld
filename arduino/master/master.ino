#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x26, 20, 4);
LiquidCrystal_I2C lcd2(0x27, 20, 4);

bool cc = false;

int ledpins[6] = { 12,11,10,9,8,7 };

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Controller booting");
  Serial.println("init lcd0");
  lcd1.init();
  lcd1.backlight();
  Serial.println("init lcd1");
  lcd2.init();
  lcd2.backlight();
  Serial.println("Controller is up");
  for (int thisPin = 0; thisPin < sizeof(ledpins); thisPin++) {
    pinMode(ledpins[thisPin], OUTPUT);
  }

}

void loop() {
  Serial.println("sending request");
  Wire.requestFrom(10, 15);
  delay(500);
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
  Serial.println(text);
  String dev = text.substring(0,3);
  Serial.println(dev);
  if(dev == "LCD") {
    int dspl = text.substring(3,5).toInt();
    int line = text.substring(5,7).toInt();
    int chr = text.substring(7,9).toInt();
    String txt = text.substring(9,29);
    setDisplay(dspl, line, chr, txt);
  }
  if(dev == "LED") {
    int dev = text.substring(3,5).toInt();
    int led = text.substring(5,7).toInt();
    int val = text.substring(7,9).toInt();
    setLed(dev, led, val);
  }
}  

void setLed(int dev, int led, int value) {
  if(dev == 0) {
    Serial.println("Setting LED " + (String)ledpins[led] + " to value " + (String)value);
    digitalWrite(ledpins[led], value);
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
