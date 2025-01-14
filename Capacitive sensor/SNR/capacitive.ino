//C++ code 
//Implement in the Arduino for Sensitive Sensor

#include <CapacitiveSensor.h>

int precision = 10;
CapacitiveSensor cs  = CapacitiveSensor(2, 6);

void setup() {
  Serial.begin(115200);
  Serial.println("KombuchaWorkShop – Capacitive Sensor");
  Serial.println("Lélian Nahon @IFT");
  pinMode(2,OUTPUT);
  pinMode(6,INPUT);
}

void loop() {
  digitalWrite(2,HIGH);
  Serial.println(state());
  delay(50);
}

long state(){
  long read = 0;
  for(int i = 0; i<precision;i++){
    read = read + cs.capacitiveSensor(100000);
  }
  read = read/precision;
  return read;
}
