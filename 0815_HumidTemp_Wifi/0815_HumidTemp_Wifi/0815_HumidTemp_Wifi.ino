#include <SimpleDHT.h>

int pinDHT11 = 4;
SimpleDHT11 dht11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  //Serial.print((int)temperature);   
  //Serial.println("C");
  return (int)temperature;
}

void loop() {
  int temp_Humid;
  int temp_Temp;
  // put your main code here, to run repeatedly:
  temp_Humid = Humid_Detect();
  Serial.print(temp_Humid);
  Serial.print("%\n");
  delay(3000);
  temp_Temp = Temp_Detect();
  Serial.print(temp_Temp);
  Serial.print("C\n");
  delay(3000);
}
