/*****************************/
/*                           */
/*       Juan  Blanc         */
/*                           */
/*        Jan 2021           */
/*                           */
/*****************************/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#include <LiquidCrystal_I2C.h>
#define lcdDir 0x27
LiquidCrystal_I2C lcd(lcdDir,20,4);

void setup() {

  Serial.begin(115200);
    lcd.init();
      lcd.backlight();
     
  WiFi.mode(WIFI_STA);
    WiFi.begin("SSID", "passwd");  /* PELASE SET IT!  */ 
  
  timeClient.begin();
    lcd.setCursor(0,0);
      lcd.print(F("Connecting to Wifi "));
  
  while (WiFi.status() != WL_CONNECTED) { delay(500);  lcd.print("."); } /* This loop will print a line each time than is trying to connect to the AP */

  lcd.clear();
    lcd.setCursor(0,0);
      lcd.print(" Time in the world!");
}

void loop() {
  
//IST  
timeClient.update();
timeClient.setTimeOffset(19800); //GMT -5:30 : The math is -5 * 60 * 60
lcd.setCursor(0,1);
lcd.print(timeClient.getFormattedTime());
lcd.setCursor(9,1);
lcd.print("India") ;

//EST
timeClient.update();
timeClient.setTimeOffset(-18000); //GMT -5 : The math is -5 * 60 * 60
lcd.setCursor(0,2);
lcd.print(timeClient.getFormattedTime());
lcd.setCursor(9,2);
lcd.print("Eastern") ;

//ARS 
timeClient.update();
timeClient.setTimeOffset(-10800); // GMT -3 : The math is -3 * 60 * 60
lcd.setCursor(0,3);
lcd.print(timeClient.getFormattedTime());
lcd.setCursor(9,3);
lcd.print("Argentina") ; 
  delay(1000);
}
