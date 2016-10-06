/* 
 * File:   main.cpp
 * Author: Kardanas
 *
 * Created on August 9, 2016, 8:40 PM
 */
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <HardwareSerial.h>

#include <Servo.h>
#include "Tachometer.h"

#define PIN_POTENTIOMETER		(0)
#define PIN_TACHO						(19)
#define PIN_LED							(13)
#define PIN_SERVO           (12)

#define PIN_LCD_RS	(42)
#define PIN_LCD_EN	(52)
#define PIN_LCD_DB4	(50)
#define PIN_LCD_DB5	(48)
#define PIN_LCD_DB6	(46)
#define PIN_LCD_DB7	(44)

#define SAFETY_DELAY_MS			(1000)

static LiquidCrystal lcd(PIN_LCD_RS, PIN_LCD_EN, PIN_LCD_DB4, PIN_LCD_DB5, PIN_LCD_DB6, PIN_LCD_DB7);
static Tachometer tacho(PIN_TACHO);

static Servo servo;

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
	lcd.print(tacho.currentRPM());
	
	lcd.setCursor(0, 3);
	lcd.print("FRQ: ");
	lcd.print(tacho.currentHz());
	lcd.setCursor(10, 3);
	lcd.print(" Hz");
}

void setup()
{
	bool flash = true;
	unsigned long lastMillis = millis();

	Serial.begin(115200);
	while (!Serial);

	Serial.println("Application started.");
	
	pinMode(PIN_LED, OUTPUT);
	pinMode(PIN_POTENTIOMETER, OUTPUT);

	servo.attach(PIN_SERVO);
	//servo.write(0);
	delay(200);

	lcd.begin(20, 4);
	
	tacho.begin();
	lastMillis = millis();
	
	while ((millis() - lastMillis) < SAFETY_DELAY_MS)
	{
		potentiometerRaw = analogRead(PIN_POTENTIOMETER);

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Pot: ");
		lcd.print((int)(potentiometerRaw * 5000.0 / 1023.0));
		lcd.setCursor(10, 0);
		lcd.print("mV");
		if (flash)
		{
			lcd.setCursor(6, 1);
			lcd.print("ACHTUNG!");
		}
		lcd.setCursor(2, 2);
		lcd.print("Set RPM to zero!");
		flash = !flash;

		if (potentiometerRaw !=0 )
		{
			lastMillis = millis();
		}
		
		delay(200);
	}

}

void loop()
{
	tacho.tick();
	potentiometerRaw = analogRead(PIN_POTENTIOMETER);
	
	ledPWM = (uint8_t)(255.0 * potentiometerRaw / 1023.0);
	analogWrite(PIN_LED, ledPWM);
  
	servo.write(map(potentiometerRaw, 0, 1023, 0, 180));

	printData();
	delay(100);
}