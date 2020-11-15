//adjustments so 2 pins light up
const int ledPin1 = 25;
const int ledPin2 = 26;

// setting PWM properties
const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2= 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin1, ledChannel1);
  ledcAttachPin(ledPin2, ledChannel2);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);
    ledcWrite(ledChannel2, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel1, dutyCycle);
    ledcWrite(ledChannel2, dutyCycle);   
    delay(15);
  }
}
