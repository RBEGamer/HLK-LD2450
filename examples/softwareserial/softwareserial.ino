/*
MINIMAL EXAMPLE FOR INTERFACING THE LD2450 RADAR SENSOR USING SOFTWARE SERIAL.
SETUP REQUIRES A LD2450 AND A ARDUINO UNO / NANO.


!!! PLEASE NOTE: DUE TO THE HIGH BAUDRATE OF 256000, THE SETUP IS VERY UNSTBLE AND NOCH RECOMMENTED !!!

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
  
}

void loop()
{

  // READ FUNCTION MUST BE CALLED IN LOOP TO READ THE INCOMMING DATA STREAM
  if (ld2450.read() > 0)
  {
    Serial.print(ld2450.getLastTargetMessage());
  };
}
