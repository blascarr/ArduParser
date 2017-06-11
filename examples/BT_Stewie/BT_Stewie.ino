#include <ArduParser.h>
#include <DFPlayer_Mini_Mp3.h>
SoftwareSerial DFPlayer(9, 10); // RX, TX
arduParser parser("<","|",">");
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
  parser.entry= false;
  delay(50);
  
  while (Serial.available()){
      parser.parser (Serial.readString());
      parser.entry = true;
  }
  if (parser.entry){
    Serial.println("Hi Stewie");
    Serial.println(parser.data.dataString[0]);

    if(parser.data.dataString[0]=="NX"){
      playnext();
    }
    
    if(parser.data.dataString[0]=="PL"){
      int nSong = parser.getInt(2);
      Serial.println("Play Track no: ");
      Serial.println(nSong);
      playSong(parser.getInt(2));
    }
    
    if(parser.data.dataString[0]=="PS"){
      mp3_pause ();
    }
    
    if(parser.data.dataString[0]=="ST"){
      mp3_stop ();
    }
    
    if(parser.data.dataString[0]=="PV"){
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

