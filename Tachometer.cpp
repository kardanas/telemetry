/* 
 * File:   Tachometer.cpp
 * Author: Kardanas
 * 
 * Created on Penktadienis, 2016, rugpjūtis 12, 22.58
 */

#include <Arduino.h>
#include "Tachometer.h"

#define TIMEOUT_PERIOD_MCS			(1000000UL)
#define MIN_PERIOD_MCS					(200UL)

static float volatile freqHz;
static unsigned long volatile lastMicros;

Tachometer::Tachometer(uint8_t pin)
{
	freqHz = 0;
	lastMicros = 0;
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
	return freqHz * 60.0;
}

unsigned long Tachometer::currentHz()
{
	return freqHz;
}

void Tachometer::tick(void)
{
	unsigned long currentMicros = micros();
	if ((lastMicros != 0) && (currentMicros - lastMicros > TIMEOUT_PERIOD_MCS))
	{
		lastMicros = 0;
		freqHz = 0;
	}
}

void Tachometer::tachoISR()
{
	unsigned long currentMicros = micros();
	unsigned long diff = currentMicros - lastMicros;

	if (lastMicros != 0)
	{
		if (diff >= MIN_PERIOD_MCS) 
		{
			freqHz = 1000000.0 / diff;
		}
		else
		{
			freqHz = 1000000.0 / MIN_PERIOD_MCS;
		}
	}
	lastMicros = currentMicros;
}
