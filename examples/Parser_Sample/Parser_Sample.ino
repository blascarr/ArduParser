#include <ArduParser.h>

//Definition bauds per second for Serial Communication (ESP8266, BlueTooth, Serial)
long bps=9600;

arduParser parserApp ("<","|",">"); 

void setup() {
  Serial.begin(bps);
  Serial.println("ArduParser Init!");
  
  String BTLine = "<FW|C|10|3.123>";
  Serial.println(parserApp.entry);
  Serial.println(parserApp.ndata);
  parseString v = parserApp.parser(BTLine);
  Serial.println(parserApp.ndata);

  for(int n=0; n<numdata; n++){
    Serial.println(v.typeString[n]);
    Serial.println(v.dataString[n]);
  }
}

void loop() {

}
