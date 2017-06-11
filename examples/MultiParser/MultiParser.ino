#include <ArduParser.h>

//Definition bauds per second for Serial Communication (ESP8266, BlueTooth, Serial)
long bps=38400;

arduParser ArduDroid ("<",",",">"); 
arduParser MobBob ("*","|","#"); 

void setup() {
  Serial.begin(bps);

  Serial.println("ArduParser Init!");
  String DroidLine = "<FW,C,10,3.123>";
  String BoBLine = "*FW|C|10|3.123|Hello| World#";

  ArduDroid.parser(DroidLine);
  Serial.println();
  Serial.print ("ArduDroid Data: ");
  Serial.println(ArduDroid.ndata);
  Serial.println();
  for(int n=0; n < ArduDroid.ndata; n++){
    Serial.print(" Data ");Serial.print(n); Serial.print(" : ");
    Serial.println(ArduDroid.data[n]);
  }

  MobBob.parser(BoBLine);
  Serial.println();
  Serial.print ("MobBob Data: ");
  Serial.println(MobBob.ndata);
  Serial.println();
  for(int n=0; n < MobBob.ndata; n++){
    Serial.print(" Data ");Serial.print(n); Serial.print(" : ");
    Serial.println(MobBob.data[n]);
  }
}

void loop() {

}
