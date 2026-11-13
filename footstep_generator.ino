#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27 (some modules use 0x3F)

const int PIEZO_PIN = A0;
const float VREF = 5.0;
const float STEP_THRESHOLD = 0.5;    // volts; tune after testing

int stepCount = 0;
bool stepActive = false;
unsigned long lastUpdate = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Footstep Energy");
  lcd.setCursor(0, 1);
  lcd.print("Generator");
  delay(2000);
  lcd.clear();
}

void loop() {
  float volts = analogRead(PIEZO_PIN) * (VREF / 1023.0);

  if (volts > STEP_THRESHOLD && !stepActive) {
    stepCount++;
    stepActive = true;
  } else if (volts < STEP_THRESHOLD / 2) {
    stepActive = false;
  }

  if (millis() - lastUpdate > 200) {
    lastUpdate = millis();
    lcd.setCursor(0, 0);
    lcd.print("Voltage:");
    lcd.print(volts, 2);
    lcd.print("V   ");
    lcd.setCursor(0, 1);
    lcd.print("Steps:");
    lcd.print(stepCount);
    lcd.print("     ");
  }
}
