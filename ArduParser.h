/*
  Design and created by Blascarr

  ArduParser
  Name    : Blascarr
  Description: ArduParser.h
  version : 1.0

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
  Written by Adrian for Blascarr
*/


#ifndef _arduparser_
#define _arduparser_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
 
#include <structconfig.h> 

  class arduParser {

    public:
      
      String START_CMD;
      String DELIMITER_CMD;
      String END_CMD;

      bool entry = false;
      int ndata;
      unsigned long timestamp;
      
      parseString data;
      
      arduParser(String START_CMD, String DELIMITER_CMD, String END_CMD);
      void define(String START_CMD, String DELIMITER_CMD, String END_CMD);

      parseString parser(String &line);
      String types(String dataIn);
      String cleanParser(String &line);

      bool isValue(int pos);
      int getInt(int pos);
      long getLong(int pos);
      float getFloat(int pos);
      String getString(int pos);
  };

#endif