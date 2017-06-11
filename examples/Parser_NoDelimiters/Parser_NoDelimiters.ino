#include <ArduParser.h>

//Definition bauds per second for Serial Communication (ESP8266, BlueTooth, Serial)
long bps=9600;

arduParser pattern ("","|",""); 

void setup() {
  Serial.begin(bps);
  Serial.println("ArduParser Init!");
  
  String BTLine = "FW|C|10|3.123";
  pattern.parser(BTLine);
  Serial.print ("N Data: ");
  Serial.println(pattern.ndata);
  Serial.println();

  for(int n=0; n < pattern.ndata; n++){
    Serial.println(pattern.data[n]);
  }
}

void loop() {

}
