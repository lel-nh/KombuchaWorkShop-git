//C++ code to implement in arduino in order to visualize SNR while running snr.py 
//make sure  to have the right serial port in the py file

#include <CapacitiveSensor.h>

int precision = 10;
CapacitiveSensor cs = CapacitiveSensor(2, 6);
CapacitiveSensor cs2 = CapacitiveSensor(3, 7);

void setup() {
  Serial.begin(115200);
  Serial.println("Capacitive Sensor SNR Calculation - Kombucha");
  Serial.println("Lélian N. @IFT");
  pinMode(2, OUTPUT);
  pinMode(6, INPUT);
}

void loop() {
  long signal = measureSignal();  
  long noise = measureNoise();  

  float snr = 0;
  if (noise > 0) {  
    snr = 20 * log((float)signal / noise);
  }

  Serial.print("Signal: ");
  Serial.print(signal);
  Serial.print(", Noise: ");
  Serial.print(noise);
  Serial.print(", SNR: ");
  Serial.println(snr);

  delay(100);  
}

long measureSignal() {
  long total = 0;
  for (int i = 0; i < precision; i++) {
    total += cs.capacitiveSensor(100000);  
  }
  return total / precision;  
}

long measureNoise() {
  long total = 0;
  for (int i = 0; i < precision; i++) {
    total += cs2.capacitiveSensor(100000);  
  }
  return total / precision; 
}
