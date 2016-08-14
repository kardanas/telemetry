/* 
 * File:   Tachometer.cpp
 * Author: Kardanas
 * 
 * Created on Penktadienis, 2016, rugpjūtis 12, 22.58
 */

#include <Arduino.h>
#include "Tachometer.h"

#include <HardwareSerial.h>

#define TIMEOUT_PERIOD_MS			(1000)

static unsigned long volatile freqHz;
static unsigned long lastMillis;
//static Timer timer;

Tachometer::Tachometer(uint8_t pin)
{
	freqHz = 0;
	lastMillis = 0;
	this->pin = pin;
}

void Tachometer::begin(void)
{
	attachInterrupt(digitalPinToInterrupt(pin), tachoISR, FALLING);
}

void Tachometer::end()
{
	detachInterrupt(digitalPinToInterrupt(pin));
}

unsigned long Tachometer::currentRPM()
{
	return freqHz * 60;
}

unsigned long Tachometer::currentHz()
{
	return freqHz;
}

void Tachometer::tachoISR()
{
	unsigned long currentMillis = millis();
	unsigned long diff = currentMillis - lastMillis;

	Serial.print("c:");
	Serial.print(currentMillis);
	Serial.print(" l:");
	Serial.print(lastMillis);
	Serial.print(" d:");
	Serial.println(currentMillis - lastMillis);

	if ((diff != 0) && (lastMillis != 0))
	{
		freqHz = 1000UL / (currentMillis - lastMillis);
	}
	lastMillis = currentMillis;
}