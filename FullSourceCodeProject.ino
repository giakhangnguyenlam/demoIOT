
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Khai báo các dữ liệu cần dùng
boolean checkData = false;
boolean checkData2 = false;
int VIRTUAL_PIN1, VIRTUAL_PIN2,VIRTUAL_PIN3;
int x = 0;
int led=5;
//int led2=12;
int M1_Left = 12; //Direccion
int M1_Right = 13;
//cấu hình wifi
char ssid[] = "Hong Loan";   // your network SSID (name)
char pass[] = "0784858182";   // your network password
//-------------------------------------------//

//----------- Channel Details -------------//
unsigned long Channel_ID = 1397165; // Channel ID
int Field_number = 0; 
const char * WriteAPIKey = "6RCBADBWQ5HD1FZW"; // Your write API Key
char auth[] = "FZyf8uFSnHMeDMLIAK4G0ToyznseQQKd";
const int FieldNumber1 = 1;
const int FieldNumber2 = 2;
const int FieldNumber3 = 3;
const char * myCounterReadAPIKey = "WIBXU16YZKD6ZCUT"; // Read API Key
int statusCode = 0;
int temp=0;
int temp2=0;
int numberSpeed=0;
// ----------------------------------------//
void readData();
WiFiClient  client;


BLYNK_CONNECTED() {
Blynk.syncAll();
}

BLYNK_WRITE(V0)
{
VIRTUAL_PIN1 = param.asInt();
Field_number = 1;
checkData = true;
}

BLYNK_WRITE(V1)
{
VIRTUAL_PIN2 = param.asInt();
Field_number = 2;
checkData = true;
}
BLYNK_WRITE(V2)
{
VIRTUAL_PIN3 = param.asInt();
checkData = true;
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
  //Motor
  pinMode(M1_Left, OUTPUT);
  pinMode(M1_Right , OUTPUT);
  
}

void loop()
{
  Blynk.run();
  if (checkData == true) {
  internet();
  //get_value();
  upload();
  //digitalWrite(LED, VIRTUAL_PIN);
  checkData == false;

  
  //digitalWrite(led, HIGH);
}

  readData();
  //analogWrite(motor,250);
}

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



void readData(){
  //---------------- Channel 1 ----------------//
  temp = ThingSpeak.readIntField(Channel_ID, FieldNumber1, myCounterReadAPIKey);
  temp2 = ThingSpeak.readIntField(Channel_ID, FieldNumber2, myCounterReadAPIKey);
  numberSpeed=ThingSpeak.readIntField(Channel_ID, FieldNumber3, myCounterReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    //digitalWrite(led2, temp2);
    digitalWrite(led, temp);
    
    if(temp2==0)//Ấn nút tắt motor
    {
      analogWrite(M1_Left,temp2);
      analogWrite(M1_Right,temp2);
      }
     else
     {
      int speedRight=255-numberSpeed;
      analogWrite(M1_Left,numberSpeed);
      analogWrite(M1_Right,0);
      }
    Serial.println("Digital is :" + String(temp));
    Serial.println("Digital led 2 is :" + String(temp2));
    Serial.println("Digital speed motor :" + String(numberSpeed));
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
  //-------------- End of Channel 1 -------------//
}
//void readDataMotor()
//{
//  
//  }
//void get_value()
//{
//
//}
// ----------(c) Electronics-Project-Hub -----------//
