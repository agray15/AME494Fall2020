#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;

#include <WiFi.h>
#include <HTTPClient.h>
#include <SimpleDHT.h>

const char* ssid = "NETGEAR29";
const char* password = "quicktree607";

//Your Domain name with URL path or IP address with path
//const char* serverName = "http://192.168.1.9:1234/sendEmail";
const char* serverName = "http://192.168.1.9:1234/sendData";

String response;

int pinDHT11 = 25;
SimpleDHT11 dht11(pinDHT11);

//from http client:
String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

//BUTTON PRESSED:
void pressed() 
{
    uint16_t color = random(0xFFFF);
    ttgo->tft->fillScreen(color);
    ttgo->tft->setTextColor(color, TFT_WHITE);
    ttgo->tft->drawString("User Button pressed",  5, 100, 4);

    if(WiFi.status()== WL_CONNECTED){
              

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

 if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }

 Serial.print("Sample OK: ");
  Serial.print(String((float)temperature) + "* C, ");
  Serial.println(String((float)humidity) + "% H");

   int t = (int)temperature;
   int h = (int)humidity;
     
     Serial.println(response);

   response = httpGETRequest(serverName)+ "?t=" + t + "&h=" + h;

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
}
void released()
{
    uint16_t color = random(0xFFFF);
    ttgo->tft->fillScreen(color);
    ttgo->tft->setTextColor(color, TFT_WHITE);
    ttgo->tft->drawString("User Button released",  5, 100, 4);

}

void setup()
{
    Serial.begin(115200);
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_BLACK);
    ttgo->tft->setTextColor(TFT_WHITE, TFT_BLACK);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("User Button released",  5, 100, 4);

    ttgo->button->setPressedHandler(pressed);
    ttgo->button->setReleasedHandler(released);

    
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

 

}

void loop()
{
    ttgo->button->loop();
}
