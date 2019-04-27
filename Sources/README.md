# Source files needed

Backup folder to ensure it's compilation.

- Arduino IDE ARDUINO - 1.8.9 - https://www.arduino.cc/en/Main/Software
- Arduino core for the ESP32 - 1.0.1 - https://github.com/espressif/arduino-esp32
- MAX6675 Library from Adafruit - 1.0.0 - https://github.com/adafruit/MAX6675-library
- MPR121 Library from Adafruit - 1.0.2 - https://github.com/adafruit/Adafruit_MPR121
- ILI9341 Library from Adafruit - 1.3.6 - https://github.com/adafruit/Adafruit_ILI9341
- GFX Library (LCD graphics core) from Adafruit - 1.4.8 - https://github.com/adafruit/Adafruit-GFX-Library

## MAX6675 library modification

On max6675.cpp line 4

```c
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
```

And add a couple of things to work with the ESP32

```c
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
  #define _delay_ms(ms) delayMicroseconds((ms) * 1000)
#endif
```