#define PIN_LED 33 // Pin de PWM (Pulse Width Modulation)
#define PIN_POT 32 // Pin de ADC (Analog to Digital Converter) Potenciometro
#define PIN_LDR 35 // Pin de LDR fotorresistor

int pwm_in = 0;
int ldr_in = 0;



void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT); //LED config


}

void loop() {
  // pwm_in = analogRead(PIN_POT);
  ldr_in = analogRead(PIN_LDR);

  // Serial.println(pwm_in);
  Serial.println(ldr_in);

  // analogWrite(PIN_LED,pwm_in/16);
  analogWrite(PIN_LED,255 - (ldr_in/16));

  // for(int i=0;i<255; i++){  //segmento del programa para 
  //   analogWrite(PIN_LED, i);
  //   delay(10);
  // }
  // for(int i=255;i>0; i--){
  //   analogWrite(PIN_LED, i);
  //   delay(10);
  // }

  delay(100);

}
