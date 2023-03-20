#define PIN_LED 33

void setup() {
  pinMode(PIN_LED, OUTPUT);
}


void loop() {
  digitalWrite(PIN_LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(700);                      
  digitalWrite(PIN_LED, LOW);   // turn the LED off by making the voltage LOW
  delay(700);                      
}
