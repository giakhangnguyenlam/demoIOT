//--------------Electronics-project-hub-------------//
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const char ssid[] = "xxxxxxxxx";  // your network SSID (name)
const char pass[] = "xxxxxxxx";   // your network password         
WiFiClient  client;

//---------Channel Details---------//
unsigned long counterChannelNumber = 1397165;            // Channel ID
const char * myCounterReadAPIKey = "WIBXU16YZKD6ZCUT"; // Read API Key
const int FieldNumber1 = 1;  // The field you wish to read
int statusCode = 0;
//-------------------------------//

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void internet(){
  //----------------- Network -----------------//
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }
  //--------- End of Network connection--------//
}

void loop()
{
  internet();
  readData();
}

void readData(){
  //---------------- Channel 1 ----------------//
  int temp = ThingSpeak.readIntField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    //digitalWrite(led, temp);
    Serial.println("Digital is :" + temp);
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
  //-------------- End of Channel 1 -------------//
}
//--------------Electronics-project-hub-------------//
