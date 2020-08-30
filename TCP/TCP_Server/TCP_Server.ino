/****************************************************************************/
/*MADE FOR  : TCP (client)
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

/********* Set Pin Button *************/
#define button D0 
/**************************************/

/*********** Set Variable *************/
int st_button; 
bool data = false;
/**************************************/

/*********** Set ip server ************/
IPAddress server_ip = {192,168,43,159}; 
/**************************************/

/************* Set Wifi ***************/
const char* ssid = "vivo1723";
const char* password = "00000000";
/**************************************/

/** Declare WiFiServer and WiFiclient */
WiFiServer server(SERVER_PORT);
WiFiClient client;
/**************************************/

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print(".");
    }
    pinMode(button,INPUT_PULLUP);
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: "); 
    Serial.println(WiFi.localIP());
 
    Serial.println("Connect TCP Server");

    /*********** Connect to server *************/
    while (!client.connect(server_ip,SERVER_PORT)){
       Serial.print(".");
       delay(100);
    } 
    /*******************************************/
    Serial.println("Success"); 

}
 
void loop(){
  st_button = digitalRead(button);

  if(st_button == 0 && data == false){
    client.println("ON"); // Send information to server
    Serial.println("ON_OK");
    data = true;
    while(st_button == 0){
      st_button = digitalRead(button);
      delay(80);
    }
  }else if(st_button == 0 && data == true){
    client.println("OFF"); // Send information to server
    Serial.println("OFF_OK");
    data = false;
    while(st_button == 0){
      st_button = digitalRead(button);
      delay(80);
    }
  }
  
}
