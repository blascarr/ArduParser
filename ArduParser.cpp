/*
  Design and created by Blascarr

  ArduParser
  Name    : Blascarr
  Description: ArduParser.cpp
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

#include <ArduParser.h> 

#include <stdarg.h>

//We use "..." to indicate that we use variadic arguments
#define debug 1
#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
#define DEFINESTRUCT(...)  (dynamicstruct(NUMARGS(__VA_ARGS__), __VA_ARGS__))

arduParser::arduParser(String START_CMD, String DELIMITER_CMD, String END_CMD){
	arduParser::START_CMD  =  START_CMD;
	arduParser::DELIMITER_CMD  =  DELIMITER_CMD;
	arduParser::END_CMD  = END_CMD;
}

void arduParser::define(String START_CMD, String DELIMITER_CMD, String END_CMD){
	arduParser::START_CMD  =  START_CMD;
	arduParser::DELIMITER_CMD  =  DELIMITER_CMD;
	arduParser::END_CMD  = END_CMD;
}

String arduParser::cleanParser(String &line){

	String subLine;
	int STARTindex = 0;
	int ENDindex = line.length();

	if (arduParser::START_CMD.length()!=0){
		
		STARTindex = line.indexOf(arduParser::START_CMD) + arduParser::START_CMD.length();

		if (!line.startsWith(arduParser::START_CMD)) {

			if(debug)	Serial.println("Start command is not valid ");
			arduParser::entry = false;
			return "";
		};
	}

	if (arduParser::END_CMD.length()!=0){
		ENDindex = line.indexOf(arduParser::END_CMD);
		if (!line.endsWith(arduParser::END_CMD)) {

			if(debug)	Serial.println("End command is not valid ");
			arduParser::entry = false;
			return "";
		};
	}	

	subLine = line.substring(STARTindex, ENDindex);
	line.remove(0,subLine.length() + arduParser::START_CMD.length() + arduParser::END_CMD.length());

	if(debug)	Serial.println(line);

	return subLine;

}

parseString arduParser::parser(String &line){

	int dataCount = 0;

	arduParser::entry = false;
	arduParser::timestamp = millis();

	String subLine = arduParser::cleanParser(line);

	do{
		if (debug) Serial.println (subLine);
		int indexTo = subLine.indexOf(arduParser::DELIMITER_CMD);
		
		arduParser::data.dataString[dataCount] = subLine.substring(0,indexTo);
		arduParser::data.dataString[dataCount].trim();
		arduParser::data.typeString[dataCount]=types(arduParser::data.dataString[dataCount]);
		dataCount++;

		if (indexTo == -1){
			//arduParser::data.dataString[dataCount] = line;
			//arduParser::data.typeString[dataCount-1]=types(arduParser::data.dataString[dataCount-1]);
			break;
		}

		subLine = subLine.substring(indexTo+arduParser::DELIMITER_CMD.length());
	}while(subLine.length() >0);

	//Data struct return
	arduParser::entry = true;
	arduParser::ndata = dataCount;
	return arduParser::data;
}

String arduParser::types(String dataIn){

	if (isDigit(dataIn[0])) {

		int indexInt = dataIn.indexOf(".");

		if (indexInt < 0){
			int dataInt = dataIn.toInt();
			//if(debug)	Serial.println("it's a integer number");
			return "int";
		}else{
			float dataFloat = dataIn.toFloat();
			//if(debug)	Serial.println("it's a float number");
			return "float";
		}
	}else if (isGraph(dataIn[0])) {
		String dataString = dataIn;
		//if(debug)	Serial.println("it's a valid hexadecimaldigit a-z A-Z");
		return "string";
	}else{
		//if(debug)	Serial.println("it's not a valid hexadecimaldigit");
		return "unknown";
	}
}

bool arduParser::isValue(int pos){
	if (pos > numdata){
		if(debug)	Serial.println("Position is greater than data structure");
		return false;
	}else{
		return true;
	}
}

int arduParser::getInt(int pos){
	if (arduParser::getInt(pos)){
		if(arduParser::data.typeString[pos-1]=="int"){
			if(debug)	Serial.println("Data Value is an Integer value");
			long val = arduParser::data.dataString[pos-1].toInt();
				if(val > 65535){
					if(debug)	Serial.println("Integer value greater than 65535. Use getLong instead");
					return -1;
				}
			return arduParser::data.dataString[pos-1].toInt();
		}else{
			if(debug)	Serial.println("Data Value is not an Integer value");
			return -1;
		}
	}else{
		return -1;
	}
};

long arduParser::getLong(int pos){
	if (arduParser::getInt(pos)){
		if(arduParser::data.typeString[pos-1]=="int"){
			if(debug)	Serial.println("Data Value is an Integer value");
			return arduParser::data.dataString[pos-1].toInt();
		}else{
			if(debug)	Serial.println("Data Value is not an Integer value");
			return -1;
		}
	}else{
		return -1;
	}
};

float arduParser::getFloat(int pos){
	if (arduParser::getInt(pos)){
		if(arduParser::data.typeString[pos-1]=="float"){
			if(debug)	Serial.println("Data Value is a Float value");
			return arduParser::data.dataString[pos-1].toFloat();
		}else{
			if(debug)	Serial.println("Data Value is not a Float value");
			return -1;
		}
	}else{
		return -1;
	}
};

String arduParser::getString(int pos){
	if (arduParser::getInt(pos)){
		if(arduParser::data.typeString[pos-1]=="string"){
			if(debug)	Serial.println("Data Value is a String value");
			return arduParser::data.dataString[pos-1];
		}else{
			if(debug)	Serial.println("Data Value is not a String value");
			return "";
		}
	}else{
		return "";
	}
};

void dynamicstruct(int numargs, ...){
	int total = 0;
	//Creating list of arguments
	va_list ap;
	//numargs access directly to the number of arguments in function
	if(debug)Serial.print("sum() called with params:");
	if(debug)Serial.println( numargs);

	//Initialize vector of arguments
	va_start(ap, numargs);
	while (numargs--){
		char thisChar = va_arg(ap, int);
		if (isAlphaNumeric(thisChar)) {
			if(debug) Serial.println("it's alphanumeric");
		}
		if (isAlpha(thisChar)) {
			if(debug) Serial.println("it's alphabetic");
		}
		if (isAscii(thisChar)) {
			if(debug) Serial.println("it's ASCII");
		}
		if (isWhitespace(thisChar)) {
			if(debug)Serial.println("it's whitespace");
		}
		if (isControl(thisChar)) {
			if(debug) Serial.println("it's a control character");
		}
		if (isDigit(thisChar)) {
			if(debug) Serial.println("it's a numeric digit");
		}
		if (isGraph(thisChar)) {
			if(debug) Serial.println("it's a printable character that's not whitespace");
		}
		if (isLowerCase(thisChar)) {
			if(debug) Serial.println("it's lower case");
		}
		if (isPrintable(thisChar)) {
			if(debug) Serial.println("it's printable");
		}
		if (isPunct(thisChar)) {
			if(debug) Serial.println("it's punctuation");
		}
		if (isSpace(thisChar)) {
			if(debug) Serial.println("it's a space character");
		}
		if (isUpperCase(thisChar)) {
			if(debug) Serial.println("it's upper case");
		}
		if (isHexadecimalDigit(thisChar)) {
			if(debug) Serial.println("it's a valid hexadecimaldigit (i.e. 0 - 9, a - F, or A - F)");
		}

	}
	
	va_end(ap);

}