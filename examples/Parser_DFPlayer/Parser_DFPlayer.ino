#include <ArduParser.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial DFPlayer(9, 10); // RX, TX
arduParser pattern("<","|",">");
int bps =9600;

void setup() {
  
  Serial.begin(bps);
  DFPlayer.begin (9600);
  mp3_set_serial (DFPlayer);
  delay(1);      
  mp3_next();
  mp3_play();
  delay(200);
}

void loop() {
  pattern.entry= false;
  delay(50);
  
  while (Serial.available()){
      String line = Serial.readString();
      pattern.parser (line);
  }
  
  if (pattern.entry){
    Serial.println("Hi Stewie");
    Serial.println(pattern.data[0]);

    if(pattern.data[0]=="NX"){
      playnext();
    }
    
    if(pattern.data[0]=="PL"){
      int nSong = pattern.getInt(2);
      Serial.println("Play Track no: ");
      Serial.println(nSong);
      playSong(pattern.getInt(2));
    }
    
    if(pattern.data[0]=="PS"){
      mp3_pause ();
    }
    
    if(pattern.data[0]=="ST"){
      mp3_stop ();
    }
    
    if(pattern.data[0]=="PV"){
      mp3_prev ();
    }
}
}

void playnext(){
  //
  mp3_next();
  delay(200);
};

void playSong(int ntrack){

  mp3_play(ntrack);
  delay(100);
  playnext();
};

