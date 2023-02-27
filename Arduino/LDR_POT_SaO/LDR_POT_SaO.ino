//Queremos plotear la resistencia detectada por el potenciometro, así que reciclamos
//el programa del LDR pero cambiando el pin al 32 que es donde se encuentra el potenciometro:
#define PIN_LED 33
#define PIN_LDR 32
#define THRLD 1500

void setup() {
  pinMode(PIN_LED,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  int ldr_signal = analogRead(PIN_LDR);

  if(ldr_signal>THRLD){
    digitalWrite(PIN_LED,LOW);
  }
  else{
    digitalWrite(PIN_LED,HIGH);
  }
  Serial.println(ldr_signal);
  delay(70);
}
