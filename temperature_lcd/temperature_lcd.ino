#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ----- CONFIG -----
String candidateName = "GIHOZO RUKUNDO BENISE";

unsigned long lastScrollTime = 0;
const int scrollDelay = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int scrollCursor = 0;
String paddedName;

float currentTemp = 0.0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  if (candidateName.length() > 16)
    paddedName = candidateName + "                ";
  else
    paddedName = candidateName;
}

void loop() {

  // ----- READ SENSOR -----
  int sensorValue = analogRead(A0);
  float voltage = (sensorValue / 1023.0) * 3.3;
  currentTemp = voltage  * 10.0;

  // ----- SERIAL DEBUG -----
  Serial.print("RAW:");
  Serial.print(sensorValue);
  Serial.print("  VOLTAGE:");
  Serial.print(voltage, 3);
  Serial.print("  TEMP:");
  Serial.println(currentTemp, 1);

  // ----- ROW 1: SCROLL NAME -----
  if (candidateName.length() > 16) {
    if (millis() - lastScrollTime >= scrollDelay) {
      lastScrollTime = millis();

      lcd.setCursor(0, 0);
      lcd.print(paddedName.substring(scrollCursor, scrollCursor + 16));

      scrollCursor++;
      if (scrollCursor > (int)candidateName.length()) {
        scrollCursor = 0;
      }
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print(candidateName);
  }

  // ----- ROW 2: TEMP DISPLAY -----
  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(currentTemp, 1);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C");

  delay(1000);
}