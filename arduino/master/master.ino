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
  text.reserve(26);
  char inchr;

  while(inchr != '\n') {
    while(Serial.available()) {
      inchr = (char)Serial.read();
      if(inchr != '\n')
        text += inchr;
    }
  }
  if(text == "CCOK") {
    cc = true;
    return;
  }
  int dspl = text.substring(0,2).toInt();
  int line = text.substring(2,4).toInt();
  int chr = text.substring(4,6).toInt();
  String txt = text.substring(6,26);

  setDisplay(dspl, line, chr, txt);    
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
