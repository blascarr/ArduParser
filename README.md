
  ArduParser

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

On this way, with this library we can perform easily code for robots who respond with a variety of mobile applications and extend our IOT modules.

We can access to different information of the response and define it like String, integer or float numbers to pass for different devices.