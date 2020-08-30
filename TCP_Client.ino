/****************************************************************************/
/*MADE FOR  : TCP (server)
/*DESIGN BY : Pattharapol Choonarong <BiGCaT> 
/*DESIGN AT : Suratthani Technical College, Electronics Department , ET313   
/*VESRSION  : 1.0 BETA 
/****************************************************************************/

/**************************************/
/* include Library ESP8266 OR
 * include Library ESP32
 */
#include <ESP8266WiFi.h>
/**************************************/

/*********** Set Server port **********/
#define SERVER_PORT 8000 
/**************************************/

/*********** Set Pin LED **************/
#define led D7
/**************************************/

/************* Set Wifi ***************/
const char* ssid = "vivo1723";
const char* password = "00000000";
/**************************************/

/******** Declare WiFiServer **********/
WiFiServer server(SERVER_PORT);
/**************************************/

/*********** Set Variable *************/
String data;
/**************************************/

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  pinMode(led,OUTPUT);
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  /*********** Start  server *********/
  server.begin();
  /***********************************/
}

void loop() {
  /****** Get information from client *******/
   WiFiClient client = server.available();
  /******************************************/
   if (client){
      Serial.println("new client");
      while(1){
        while(client.available()){ 
          char d = client.read();
          data = data + d;

          if(data == "ON"){
            digitalWrite(led,HIGH);
          }
          if(data == "OFF"){
            digitalWrite(led,LOW);
          }
        }
        data = "";
        
        if(server.hasClient()){
           return;
        }    
     }      
  } 
}
