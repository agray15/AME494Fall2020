#include <Arduino.h>
#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

TTGOClass *ttgo;



char * HOSTNAME = "test12345";
char * WifiPASS = "";

#include <WiFi.h>
#include <WebServer.h>

//PWM ADDITION HERE:
const int ledPin1 = 25;
const int ledPin2 = 26;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2= 0;
const int resolution = 8;

WebServer server(80);


void setup() {
    Serial.begin(115200);


    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_WHITE);
    ttgo->tft->setTextColor(TFT_BLACK, TFT_WHITE);
    ttgo->tft->setTextFont(4);
    ttgo->tft->drawString("Ready",  5, 10);


//PWM ADDITION HERE:
 // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);


    

    // Start Wifi AP
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, WifiPASS);


      
    // handle index -- HTTP Server

    
    server.on("/", []() {
      digitalWrite(21, 1);
      String v = server.arg("v");
      
      //IF V > 50, BRIGHTEN
      //IF V < 50, FADE
      int val = v.toInt();
      
      Serial.println(v);

      ttgo->tft->fillScreen(TFT_WHITE);
       ttgo->tft->drawString(v,  5, 10); 
       
      server.send(200, "text/html", "<html><head><script>function foo(v){window.location.href=\"./?v=\" + v}</script></head><body><input type='range' max='100' min=\"0\" onchange='foo(this.value)' id='theText'></body><script>document.getElementById(\"theText\").value=parseInt(window.location.search.replace(\"?v=\",\"\"))</script><html>");
    });

    
    server.begin();
    
}

void loop() {
    server.handleClient();  

//PWM ADDITIONS HERE:

int v;

 v = 0:
 if ( int v >= 50 ) {
 // increase the LED brightness
 for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);
    ledcWrite(ledChannel2, dutyCycle);
//    delay(15);
  }
 }



 
  // decrease the LED brightness

  v = 255;
  if ( int v < 50 ){  
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);
    ledcWrite(ledChannel2, dutyCycle);   
//    delay(15);
  }
  }



}
