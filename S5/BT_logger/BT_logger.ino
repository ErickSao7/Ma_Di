//Lecturas por BT Serial
//Cada 100ms
#include <Adafruit_BMP085.h>

#define LED_PIN 33
#define LDR_PIN 35
Adafruit_BMP085 bmp;
char payload[80]; //definimos un char que estaremos llenando y vaciando.

//Bluetooth

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  pinMode(LED_PIN,OUTPUT);
  Serial.begin(115200);
  bmp.begin();
  SerialBT.begin("Axolote Erick"); //Bluetooth device name
  Serial.println("Bluetooth configurado");

}

void loop() {
  if (SerialBT.available()) { //este ciclo if es para que se realice una pausa en las medidas cada que se mande un texto.
    Serial.write(SerialBT.read());
        delay(20);

  }
  else{
    sprintf(payload,"%d,%3.2f,%d",//mi BMP mide enteros, así que uso %d.
          bmp.readPressure(),
          bmp.readTemperature(),
          analogRead(LDR_PIN));
  digitalWrite(LED_PIN,HIGH);
    SerialBT.println(payload); //comando para imprimir en la terminal Bluetooth.
    Serial.println(payload);
  digitalWrite(LED_PIN,LOW);
      delay(100);

  }

}
