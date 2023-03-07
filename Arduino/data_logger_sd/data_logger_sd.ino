#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include <Adafruit_BMP085.h>

#define LED_PIN 33
#define LDR_PIN 35
File readings;
Adafruit_BMP085 bmp;
char payload[80]; //definimos un char que estaremos llenando y vaciando.


void setup() {
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(115200);
  bmp.begin();
  if (!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

}

void loop() {
  sprintf(payload,"%d,%3.2f,%d",
          bmp.readPressure(),
          bmp.readTemperature(),
          analogRead(LDR_PIN));
  digitalWrite(LED_PIN,HIGH);
    readings = SD.open("/lecturas_sensor.csv",FILE_APPEND);
    readings.println(payload);
    readings.close();
    Serial.println(payload);
  digitalWrite(LED_PIN,LOW);
    delay(500);
}
