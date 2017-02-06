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
  String BTLine = "<FW|C|10|3.123>";

}

void loop() {
  parseString d;

  if (com.available()){
    String dataBT = com.readString();
    
    d=ArduDroid.parser(dataBT);
    
    Serial.println(dataBT);
    if(ArduDroid.entry){
      for(int n=0; n < numdata; n++){
        Serial.print("ArduDroid data: ");
        Serial.println(ArduDroid.data.dataString[n]);
        Serial.print("  Type:  ");
        Serial.println(ArduDroid.data.typeString[n]);
        
      }
      //Cuando recoge una linea completa con caracteres raros hay problemas de lectura.
      if(ArduDroid.getInt(1)==10){
        Serial.println("Success");
      }
    }    

    if(MobBob.entry){
      for(int n=0; n < numdata; n++){
        Serial.print("MobBob data: ");
        Serial.print(MobBob.data.dataString[n]);
        Serial.print("  Type:  ");
        Serial.println(MobBob.data.typeString[n]);
      }
      //Cuando recoge una linea completa con caracteres raros hay problemas de lectura.
      if(MobBob.getInt(1)==10){
        Serial.println("Success");
      }
    }  
  }
}
