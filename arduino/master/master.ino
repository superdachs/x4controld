#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd1(0x26, 20, 4);
LiquidCrystal_I2C lcd2(0x27, 20, 4);

void setup() {
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
}

void loop() {
  lcd1.setCursor(0,0);
  lcd1.print("LCD 1");
  lcd2.setCursor(0,0);
  lcd2.print("LCD 2");
}
