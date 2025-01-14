//C++ code 
//Implement in the Arduino for Kombucha Stretch Sensor

    int stretchSensor  = A0;  	//analog entry
    int precision = 10;   	//number of read by value displayed

    void setup() {
      Serial.begin(115200);
      Serial.println("KombuchaWorkShop – Stretch Sensor");
      Serial.println("Lélian Nahon @IFT");
    }

    void loop() {
        Serial.println(state());
        delay(200);
    }

    long state() { 
      long read = 0;
      for(int i = 0;i<precision;i++){
        read += analogRead(stretchSensor);  
      }
      read = read/precision;  
      return read;
    }
