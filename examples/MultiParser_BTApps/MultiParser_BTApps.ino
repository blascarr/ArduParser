#include <SoftwareSerial.h>
#include <ArduParser.h>

//Definition bauds per second for Serial Communication (ESP8266, BlueTooth, Serial)
long bps=115200;

SoftwareSerial com(10,11); //RX-10; TX-11
arduParser ArduDroid ("<",",",">"); 
arduParser MobBob ("*","|","#"); 

void setup() {
  Serial.begin(bps);
  com.begin(bps);
  Serial.println("ArduParser Init!");

}

void loop() {

  if (com.available()){
    String ArduDroid_String = com.readString();
    String MobBob_String = ArduDroid_String;
    
    ArduDroid.parser(ArduDroid_String);
    MobBob.parser(MobBob_String);
  }
  
  if(ArduDroid.entry){
    for(int n=0; n < ArduDroid.ndata; n++){
      Serial.print("ArduDroid data ");Serial.print(n);Serial.print(" : ");
      Serial.println(ArduDroid.data[n]);
      
    }
    ArduDroid.entry=false;
  }    

  if(MobBob.entry){
    for(int n=0; n < MobBob.ndata; n++){
      Serial.print("MobBob data ");Serial.print(n);Serial.print(" : ");
      Serial.print(MobBob.data[n]);
    }
    MobBob.entry = false;
  }
}
