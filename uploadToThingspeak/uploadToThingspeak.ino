
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Khai báo các dữ liệu cần dùng
boolean checkData = false;
int VIRTUAL_PIN1, VIRTUAL_PIN2,VIRTUAL_PIN3;
int x = 0;

//cấu hình wifi
char ssid[] = "iPhone của Gia Khang";   // your network SSID (name)
char pass[] = "khangnguyen66";   // your network password
//-------------------------------------------//

//cấu hình channel
unsigned long Channel_ID = 1397165; // Channel ID
const char * WriteAPIKey = "6RCBADBWQ5HD1FZW"; // Your write API Key
char auth[] = "FZyf8uFSnHMeDMLIAK4G0ToyznseQQKd";
// ----------------------------------------//

WiFiClient  client;


BLYNK_CONNECTED() {
Blynk.syncAll();
}

//Khai báo và gán giá trị cho 3 virtual pin: 2 đèn, 1 quạt
BLYNK_WRITE(V0)
{
VIRTUAL_PIN1 = param.asInt();
checkData = true;
}

BLYNK_WRITE(V1)
{
VIRTUAL_PIN2 = param.asInt();
checkData = true;
}

BLYNK_WRITE(V2)
{
VIRTUAL_PIN3 = param.asInt();
checkData = true;
}

// setup
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Blynk.begin(auth, ssid, pass);
  
}

// chạy chương trình
void loop()
{
  Blynk.run();
  if (checkData == true) {
  internet();
  upload();
  checkData == false;
}

  
}

// upload lên thingspeak
void upload()
{
  internet();
  ThingSpeak.setField(1, VIRTUAL_PIN1);
  ThingSpeak.setField(2, VIRTUAL_PIN2);
  ThingSpeak.setField(3, VIRTUAL_PIN3); 
  x = ThingSpeak.writeFields(Channel_ID, WriteAPIKey);
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
