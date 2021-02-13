
#include <ESP8266WiFi.h>

#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
ESP8266WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#include <LiquidCrystal_I2C.h>

/* Definiendo pantalla : NO TE OLVIDES de cambiar la dirección (por si tenes múltiples pantallas) */
#define direccionLCD 0x27
LiquidCrystal_I2C lcd(direccionLCD,20,4);
int debounce = 0;
void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);
 /* Se inicializa el LCD */
  lcd.init();
    lcd.backlight();
     
  WiFi.mode(WIFI_STA);
  WiFi.begin("IoT", "28101962");
  
timeClient.begin();
  timeClient.setTimeOffset(-10800);
     lcd.setCursor(0,1);
      lcd.print(F("Conectando a Wifi "));
      int n = WiFi.scanNetworks();
       for (int i = 0; i < n; i++)
{
  Serial.println(WiFi.SSID(i));
}          
          while (WiFi.status() != WL_CONNECTED) {delay(500);  lcd.print("."); }
          lcd.clear();
           // Mostrar mensaje de exito, WiFI conectada y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() {
  // wait for WiFi connection
  timeClient.update();
  if ((WiFi.status() == WL_CONNECTED) && debounce == 30) {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://ema.unsam.edu.ar/")) {  // HTTP
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          String temp = payload.substring(1680,1684);
          String hum = payload.substring(4878,4883);
          String pres = payload.substring(11587,11597);
         // Serial.println(payload);
        
             
          Serial.print("Obteniendo temperatura.. ");
          
          lcd.setCursor(0,0);
          lcd.print("Temperatura:");
          lcd.print(temp);
          lcd.print(" C");
          
          lcd.setCursor(0,1);
          lcd.print("Humedad:");
          lcd.print(hum);

          lcd.setCursor(0,2);
          lcd.print("Presion:");
          lcd.print(pres);
          debounce = 0 ;
         
       
          }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
 lcd.setCursor(0,3);
 lcd.print(timeClient.getFormattedTime());
 lcd.setCursor(9,3);
 lcd.print(WiFi.localIP());
 debounce ++ ;
 Serial.print("debunce:");
 Serial.println(debounce);
  delay(1000);
}
