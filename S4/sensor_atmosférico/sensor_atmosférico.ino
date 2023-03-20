//Queremos los datos de presión y temperatura en dos columnas.
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
char payload[80]; //definimos un char que estaremos llenando y vaciando.

void setup() {
  bmp.begin();
  Serial.begin(115200);

}

void loop() {
  sprintf(payload,"%d,%3.2f", //En mi caso usé %d porque mi bmp solo me manda enteros, si lo defino float no manda nada.
          bmp.readPressure(),
          bmp.readTemperature());
  Serial.println(payload);
  /*
  Serial.print(bmp.readPressure()/1000);
  Serial.print(",");  //Intento rápido que hice en clase hue hue hue.
  Serial.println(bmp.readTemperature());
  */
  delay(200);  
}
