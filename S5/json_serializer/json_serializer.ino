// Leer Json desde Serial, SD o SPIFFS 
// Serializar un Json e imprimirlo por serial

#include <Adafruit_BMP085.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
//#include <Credentials.h>

//Payload creado con snprintf
#define BUFFER_LEN  256
char payload[BUFFER_LEN]; //Payload Serializado
String json_string;

//Payload crearon con Json parser
//Doc: https://arduinojson.org/
//Ticket: Usar reservación de memoria en stack
//Usar el json assistant para calcular el LEN necesario para cada documento
#define JSON_BUFFER_INCOMING_LEN 200
#define JSON_BUFFER_OUTGOING_LEN 200
DynamicJsonDocument payload_in(JSON_BUFFER_INCOMING_LEN); //Json desde SPIFFS,SD,Serial o MQTT (Stream)
DynamicJsonDocument payload_out(JSON_BUFFER_OUTGOING_LEN);//Json hacia SPIFFS,SD,Serial o MQTT (Stream)

//Configuración de BMP y LED
#define PIN_LED 33 //Mi led está ubicado en el pin 33.
Adafruit_BMP085 bmp;

void setup() {
  
  //Inicializar perifericos
  Serial.begin(115200);
  bmp.begin(0x77); 
  pinMode(PIN_LED,OUTPUT);
  SPIFFS.begin(true);
  File file_json;

  //Leer el archivo con Json desde SPIFFS.
  file_json = SPIFFS.open("/json_file.txt", FILE_READ);

  //Guardar Json en variable
  while (file_json.available()) {
    json_string = file_json.readString();
  }   
  file_json.close(); 

  Serial.println("Contenido del archivo");
  Serial.println(json_string);
  Serial.println("Está bueno imprimirlo por Serial, pero\n"
                 "necesitamos extraer los atributos.\n"
                 "A mano sería muy complicado.");  

  //Json parser deserializer
  //Parseo desde el archivo 
  file_json = SPIFFS.open("/json_file.txt", FILE_READ);
  deserializeJson(payload_in,file_json);
  file_json.close(); 

  //Extracción de atributos
  const char* message = payload_in["message"];
  const char* origen = payload_in["origen"];

  Serial.println("Atributos:");
  Serial.println(message);Serial.println(origen);


}


void loop() {

  //Para hacer payloads con jsons, es una solución Ok.
  sprintf(payload,"{\"origen\" : \"sprintf\","
                    "\"temp_C\" : \"%.2f\"," 
                    "\"press_hPa\" : \"%d\"}",        //Como mi BMP detecta la presión en int yo uso %d.             
                    bmp.readTemperature(),
                    bmp.readPressure()/100);
   
   Serial.print("Publicando mensaje: ");
   Serial.println(payload);
               
   //Json Serializer
   // Guardar
   payload_out["origen"] = "json_serializer";
   payload_out["temp_C"] = String(bmp.readTemperature(),2);
   payload_out["press_hPa"] = String(bmp.readPressure()/100); //En mi caso mi BMP manda los datos en int por lo que si pongo ",2" en el argumento de "String" cambia el número a base 2.

   
   serializeJson(payload_out, payload);
        
   Serial.print("Publicando mensaje: ");
   Serial.println(payload);
   delay(5000);
                      
}
