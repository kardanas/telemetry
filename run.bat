@ECHO Converting to hex...
cd "C:\Program Files (x86)\Arduino"
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avr-objcopy" -O ihex -R .eeprom  "%1" "%1.hex"

"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude" -C"C:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf" -v -patmega2560 -cwiring -PCOM3 -b115200 -D -Uflash:w:%1.hex:i 