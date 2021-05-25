
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Khai báo các dữ liệu cần dùng
boolean checkData = false;
int VIRTUAL_PIN;
int x = 0;

//cấu hình wifi
char ssid[] = "iPhone của Gia Khang";   // your network SSID (name)
char pass[] = "khangnguyen66";   // your network password
//-------------------------------------------//

//----------- Channel Details -------------//
unsigned long Channel_ID = 1397165; // Channel ID
const int Field_number = 1; // Don't change
const char * WriteAPIKey = "6RCBADBWQ5HD1FZW"; // Your write API Key
char auth[] = "FZyf8uFSnHMeDMLIAK4G0ToyznseQQKd";
// ----------------------------------------//

WiFiClient  client;


BLYNK_CONNECTED() {
Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
VIRTUAL_PIN = param.asInt();
checkData = true;
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
  Blynk.run();
  if (checkData == true) {
  internet();
  get_value();
  upload();
  //digitalWrite(LED, VIRTUAL_PIN);
  checkData == false;
}
  
}

void upload()
{
  internet();
  x = ThingSpeak.writeField(Channel_ID, Field_number, VIRTUAL_PIN, WriteAPIKey);
  if (x == 200)Serial.println("Data Updated.");
  if (x != 200)
  {
    Serial.println("Data upload failed, retrying....");
    delay(15000);
    upload();
  }
}

void internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void get_value()
{

}
// ----------(c) Electronics-Project-Hub -----------//
