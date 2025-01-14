//C++ code 
//Implement in the Arduino for Matrix Sensor
//This code only provide a Serial output to visualize nuerically each touch
//Please use the version in git hub to visualize it on processing

#include <Muca.h> 
//librairy which you will need the one that you can find
//on muca web site is not complete please use mine that I 
//have modify on the git of this project

Muca muca;

void setup() {
  Serial.begin(115200);
  muca.init(true);
  muca.setResolution(90, 90);
  muca.setReportRate(6);
  Serial.println("KombuchaWorkShop – Matrix Sensor");
  Serial.println("Lélian Nahon @IFT");
}

void loop() {
  GetTouchSimple();
  delay(5);
}

void GetTouchSimple() {
  if (muca.updated()) {
    for (int i = 0; i < muca.getNumberOfTouches(); i++) {
      
      if (i != 0)Serial.print("|");
      Serial.print(muca.getTouch(i).id); Serial.print(":");
      Serial.print(muca.getTouch(i).flag); Serial.print(":");
      Serial.print(muca.getTouch(i).x); Serial.print(":");
      Serial.print(muca.getTouch(i).y); Serial.print(":");
      Serial.print(muca.getTouch(i).weight);
    }
    Serial.println("|");
  }
}
