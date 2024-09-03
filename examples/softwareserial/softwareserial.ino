/*
MINIMAL EXAMPLE FOR INTERFACING THE LD2450 RADAR SENSOR USING SOFTWARE SERIAL.
SETUP REQUIRES A LD2450 AND A ARDUINO UNO / NANO.

!!! PLEASE NOTE !!!

THIS DEMO USES THE SOFTWARE SERIAL LIBRARY.
PLEASE MAKE SURE THAT THE LIBRARY IS AVAILABLE FOR FOR BOARD.

https://docs.arduino.cc/learn/built-in-libraries/software-serial/
AND / OR 
http://arduiniana.org/libraries/newsoftserial/


IF YOU ARE USING A RASPBERRY PI PICO OR ANY OTHER BOARD WITH MULTIBLE HARDWARE SERIAL PORTS, PLEASE SEE THE BASIC EXAMPLE.


PS: !!! PLEASE NOTE: DUE TO THE HIGH BAUDRATE OF 256000, THE SETUP IS VERY UNSTBLE AND NOCH RECOMMENTED !!!

PLEASE REFER TO https://docs.arduino.cc/tutorials/communication/SoftwareSerialExample/

CONNECTIONS:

LD2450 => ARDUINO
5V => 5V
GND => GND
RX => 3
TX => 2
*/

#include <Arduino.h>

#include <SoftwareSerial.h>


#define ENABLE_SOFTWARESERIAL_SUPPORT
#include <LD2450.h>



SoftwareSerial radarSerial(2, 3); // RX, TX

// SENSOR INSTANCE
LD2450 ld2450;

void setup()
{
  //SERIAL FOR HOST / DEBUG MESSAGES
  Serial.begin(115200);

  // SETUP SENSOR
  // HERE THE HARDWARE SERIAL INTERFACE 1 IS USED
  ld2450.begin(radarSerial, false);
  

  if(!ld2450.waitForSensorMessage()){
    Serial.println("SENSOR CONNECTION SEEMS OK");
  }else{
    Serial.println("SENSOR TEST: GOT NO VALID SENSORDATA - PLEASE CHECK CONNECTION!");
  }

  
}

void loop()
{

  // READ FUNCTION MUST BE CALLED IN LOOP TO READ THE INCOMMING DATA STREAM
  if (ld2450.read() > 0)
  {
    Serial.print(ld2450.getLastTargetMessage());
  };
}
