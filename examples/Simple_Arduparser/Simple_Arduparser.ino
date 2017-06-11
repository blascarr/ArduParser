#include <SoftwareSerial.h>
#include <ArduParser.h>

SoftwareSerial com (2,3);
long bps = 9600;

arduParser pattern("<",",",">"); 

void setup() {
  Serial.begin(bps);
  com.begin(38400);
  Serial.println("Goodnight ArduParser");
  String dataline = "<P,A,R,S,E,R,123>";
  
  Serial.print("Data on parser: ");Serial.println(pattern.entry);
  pattern.parser (dataline);
  Serial.println(dataline);
  
  for(int n=0; n < nStack; n++){
    Serial.print("ArduParser data: ");
    Serial.println(pattern.data[n]);
  }
  Serial.print("Data on parser: ");Serial.println(pattern.entry);
    
}

void loop() {
 pattern.entry = false;
 while (com.available()) {
    String dataline = com.readString();
    Serial.print("BT STR: ");
    Serial.println(dataline);
    pattern.parser (dataline);
    pattern.entry = true;
 }
 
  if(pattern.entry){
    for(int n=0; n < nStack; n++){
      Serial.print("Arduparser data: ");
      Serial.println(pattern.data[n]);

    }
  }


  delay(100);

  while (Serial.available()) {
    com.write(Serial.read());
  }
  delay(100);
}
