/* 
 * File:   Tachometer.h
 * Author: Kardanas
 *
 * Created on Penktadienis, 2016, rugpjūtis 12, 22.58
 */

#ifndef TACHOMETER_H
#define	TACHOMETER_H

class Tachometer 
{
public:
	Tachometer(uint8_t pin);

	void begin(void);
	void end(void);
	
	unsigned long currentRPM(void);
	unsigned long currentHz(void);
private:
	uint8_t pin;
	//static unsigned long volatile freqHz;
	//static unsigned long lastMillis;
	
	static void tachoISR(void);
};

#endif	/* TACHOMETER_H */

