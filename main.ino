#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <RTClib.h>

#define I2C_ADDR    0x27
#define BACKLIGHT_PIN     3

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

DHT dht11(4, DHT11);

RTC_DS1307 RTC;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  
  lcd.setCursor(9, 0);
  lcd.print("Wil:");

  Wire.begin();
  RTC.begin();

  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  int temp = dht11.readTemperature(); 
  int hum = dht11.readHumidity();

  lcd.setCursor(5, 0);
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(13, 0);
  lcd.print(hum);
  lcd.print("%");

  DateTime now = RTC.now(); 

  int hours = now.hour(); 
  int minutes = now.minute();
  int dates = now.day(); 
  int months = now.month(); 
  int years = now.year(); 

  lcd.setCursor(0, 1);
  if (hours < 10) lcd.print("0"); 
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) lcd.print("0"); 
  lcd.print(minutes);

  lcd.setCursor(6, 1);
  lcd.print(dates);
  lcd.print("/");
  lcd.print(months);
  lcd.print("/");
  lcd.print(years);

  delay(1000);
}
