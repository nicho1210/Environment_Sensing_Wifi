#include <SoftwareSerial.h>
#include <SimpleDHT.h>
#define RX 2
#define TX 3
String AP = "TP-LINK_724G";       // AP NAME
String PASS = "2oixolxu"; // AP PASSWORD
String API = "85GKJ1VNL3WUNB58";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
String field_Temp = "field1";
String field_Humid = "field2";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
int pinDHT11 = 4;
SimpleDHT11 dht11;
SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  pinMode(10, OUTPUT);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

int Temp_Detect() {
  byte humidity = 0;
  byte temperature = 0;
  int err = SimpleDHTErrSuccess;
  Serial.println("==========Temperature===========");
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read Temperature failed, err="); Serial.println(err);delay(1000);
       return;
  }
  Serial.print("Temperature = ");   
  Serial.print((int)temperature);   
  Serial.println("C\n");
  return (int)temperature;
}

int Humid_Detect() {
  byte humidity = 0;
  byte temperature = 0;
  int err = SimpleDHTErrSuccess;
  Serial.println("==========Humidity===========");
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read Humidity failed, err="); Serial.println(err);delay(1000);
       return;
  }
  Serial.print("Humidity = ");   
  //Serial.print((int)humidity);
  //Serial.print("%");
  return (int)humidity;
}

void loop() {
 valSensor = Temp_Detect();
 if(valSensor >= 30) {
    digitalWrite(10, HIGH);
 }
 String getData = "GET /update?api_key="+ API +"&"+ field_Temp +"="+String(valSensor);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");

 valSensor = Humid_Detect();
 getData = "GET /update?api_key="+ API +"&"+ field_Humid +"="+String(valSensor);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

int getSensorData(){
  return random(1000); // Replace with your own sensor code
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
