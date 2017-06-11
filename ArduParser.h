/*
  Design and created by Blascarr

  ArduParser
  Name    : Blascarr
  Description: ArduParser.h
  version : 2.0

  ArduParser is a library to perform different protocols based on reading characters.
  Some applications works with different protocols defined by different authors, 
  and in most cases exist a pattern as following:

  	- Start_Command
  	- Data[0]
  	- Delimiter_Command
  	- Data[1]
  	- Delimiter_Command
  	- Data[2]
  	- Delimiter_Command
  	......

  	- End_Command
  

  **
  
  Blascarr invests time and resources providing this open source code like some other libraries, please
  respect the job and support open-source software.

  Written by Adrian for Blascarr
*/


#ifndef _arduparser_
#define _arduparser_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
 
#define debug 0
#define nStack 7
  
class arduParser {
  public:
    String START_CMD;
    String DELIMITER_CMD;
    String END_CMD;
    bool entry = false;
    int ndata;
    String dataString[nStack];
    
    arduParser(String START_CMD, String DELIMITER_CMD, String END_CMD){
      arduParser::START_CMD  =  START_CMD;
      arduParser::DELIMITER_CMD  =  DELIMITER_CMD;
      arduParser::END_CMD  = END_CMD;
    };
    
    void define(String START_CMD, String DELIMITER_CMD, String END_CMD){
      arduParser::START_CMD  =  START_CMD;
      arduParser::DELIMITER_CMD  =  DELIMITER_CMD;
      arduParser::END_CMD  = END_CMD;
    };

    // Clean the input String and obtain the same info without start and end delimiters
    String cleanParser(String &line){
      String subLine;
      int STARTindex = 0;
      int ENDindex = line.length();
    
      if (arduParser::START_CMD.length()!=0){
        
        STARTindex = line.indexOf(arduParser::START_CMD) + arduParser::START_CMD.length();
    
        if (!line.startsWith(arduParser::START_CMD)) {
    
          arduParser::entry = false;
          return "";
        };
      }
    
      if (arduParser::END_CMD.length()!=0){
        ENDindex = line.indexOf(arduParser::END_CMD);
        if (!line.endsWith(arduParser::END_CMD)) {
    
          arduParser::entry = false;
          return "";
        };
      } 
    
      subLine = line.substring(STARTindex, ENDindex);
      line.remove(0,subLine.length() + arduParser::START_CMD.length() + arduParser::END_CMD.length());
      return subLine;
    };

    
    void parser(String &line){
      int dataCount = 0;
      arduParser::entry = false;
    
      String subLine = arduParser::cleanParser(line);
    
      do{
        int indexTo = subLine.indexOf(arduParser::DELIMITER_CMD);
        
        arduParser::dataString[dataCount] = subLine.substring(0,indexTo);
        arduParser::dataString[dataCount].trim();
        dataCount++;
    
        if (indexTo == -1){
          break;
        }
    
        subLine = subLine.substring(indexTo+arduParser::DELIMITER_CMD.length());
      }while(subLine.length() >0);
    
      //Data struct return
      arduParser::entry = true;
      arduParser::ndata = dataCount;
      //return parser::dataString;
    };

    bool isValue(int pos){
      return arduParser::dataString[pos].toInt();
    };
    
    int getInt(int pos){
      String dataIn = arduParser::dataString[pos];
      int num;
      //Serial.print("Dato Int--> ");Serial.println(dataIn);
      if((isDigit(dataIn[0])) || dataIn[0]== '-' ){
        if(dataIn[0]== '-'){
          int index_minus = arduParser::dataString[pos].indexOf('-');
          num = dataIn.substring(index_minus).toInt()*(-1);
        }else{
          num = dataIn.toInt();
        }
        return num;
      }
    };

    float getFloat(int pos){
      String dataIn = arduParser::dataString[pos];
      float num;
      if((isDigit(dataIn[0])) || dataIn[0]== '-' ){
        if(dataIn[0]== '-'){
          int index_minus = arduParser::dataString[pos].indexOf('-');
          num = dataIn.substring(index_minus).toFloat()*(-1);
        }else{
          num = dataIn.toFloat();
        }
      }
      return num;
    };
};


#endif