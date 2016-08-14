/* 
 * File:   main.cpp
 * Author: Kardanas
 *
 * Created on August 9, 2016, 8:40 PM
 */
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <HardwareSerial.h>
#include "Tachometer.h"

#define PIN_POTENTIOMETER		(0)
#define PIN_TACHO						(19)
#define PIN_LED							(13)

#define PIN_LCD_RS	(53)
#define PIN_LCD_EN	(51)
#define PIN_LCD_DB0	(49)
#define PIN_LCD_DB1	(47)
#define PIN_LCD_DB2	(45)
#define PIN_LCD_DB3	(43)

#define SAFETY_DELAY_MS			(1000)

static LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_DB0, PIN_LCD_DB1, PIN_LCD_DB2, PIN_LCD_DB3);
static Tachometer tacho(PIN_TACHO);

static uint16_t potentiometerRaw;
static uint8_t ledPWM = 0;

static void printData(void)
{
	lcd.clear();

	lcd.setCursor(0, 0);
	lcd.print("Pot: ");
	lcd.print((int)(potentiometerRaw * 5000.0 / 1023.0));
	lcd.setCursor(10, 0);
	lcd.print("mV");
	
	lcd.setCursor(0, 1);
	lcd.print("PWM: ");
	lcd.print((int16_t)(ledPWM * 100.0 / 255.0));
	lcd.setCursor(10, 1);
	lcd.print("%");
	
	lcd.setCursor(0, 2);
	lcd.print("RPM: ");
	lcd.print(tacho.currentHz());
	lcd.setCursor(10, 1);
}

void setup()
{
	bool flash = true;
	unsigned long lastMillis = millis();

	Serial.begin(115200);
	while (!Serial);

	Serial.println("Application started.");
	
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_TACHO, INPUT_PULLUP);
	pinMode(PIN_POTENTIOMETER, OUTPUT);
	lcd.begin(20, 4);
	
	tacho.begin();
	
	while ((millis() - lastMillis) < SAFETY_DELAY_MS)
	{
		lcd.clear();
		if (flash)
		{
			lcd.setCursor(6, 1);
			lcd.print("ACHTUNG!");
		}
		lcd.setCursor(2, 2);
		lcd.print("Set RPM to zero!");
		flash = !flash;

		potentiometerRaw = analogRead(PIN_POTENTIOMETER);
		if (potentiometerRaw !=0 )
		{
			lastMillis = millis();
		}
		
		delay(200);
	}
	
}

void loop()
{
	potentiometerRaw = analogRead(PIN_POTENTIOMETER);
	
	ledPWM = (uint8_t)(255.0 * potentiometerRaw / 1023.0);
	analogWrite(PIN_LED, ledPWM);
	
	printData();
	delay(200);
}