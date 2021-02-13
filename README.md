# worldclock_LCD
This implementation allow you to display the time of any place in the world using an ESP8266 (WeMos D1-Mini)

### Libraries required 
-  __LiquidCyrstal_I2C__
-  __NTPClient__
-  __ESP 8266/ESP32__ Lib installed on the IDE

### Updates in the file to-do
- Change your SSID Info and Password data
- set your own __setTimeOffset__, in the project is set as 3 timezones, IST, EST and ARG(GMT-3) 


***Connection:***

 WeMos D1 Mini Case
```
SCL Screen -> Pin D1 (Wemos D1 Mini)
SDA Screen -> Pin D2 (Wemos D1 Mini)
5v Screen -> 5v (Wemos D1 Mini)
GND Screen -> GND (Wemos D1 Mini)
```
