/*
 *	An Arduino library for the Hi-Link LD2450 24Ghz FMCW radar sensor.
 *
 *  This sensor is a Frequency Modulated Continuous Wave radar, which makes it good for presence detection and its sensitivity at different ranges to both static and moving targets can be configured.
 *
 *	The code in this library is based off the https://github.com/0ingchun/arduino-lib_HLK-LD2450_Radar.
 *
 *	https://github.com/ncmreynolds/ld2410
 *
 *
 */
#ifndef LD2450_h
#define LD2450_h

#include <Arduino.h>

#define LD2450_MAX_SENSOR_TARGETS 3
#define LD2450_SERIAL_BUFFER 256
#define LD2450_SERIAL_SPEED 256000


#if defined(ESP32)
  #ifdef ESP_IDF_VERSION_MAJOR // IDF 4+
    #if CONFIG_IDF_TARGET_ESP32 // ESP32/PICO-D4
      #define LD2450_RADAR_SERIAL Serial
      #define LD2450_RADAR_RX_PIN 32
      #define LD2450_RADAR_TX_PIN 33
    #elif CONFIG_IDF_TARGET_ESP32S2
      #define LD2450_RADAR_SERIAL Serial
      #define LD2450_RADAR_RX_PIN 9
      #define LD2450_RADAR_TX_PIN 8
    #elif CONFIG_IDF_TARGET_ESP32C3
      #define LD2450_RADAR_SERIAL Serial
      #define LD2450_RADAR_RX_PIN 4
      #define LD2450_RADAR_TX_PIN 5
    #else 
      #error Target CONFIG_IDF_TARGET is not supported
    #endif
  #else // ESP32 Before IDF 4.0
    #define LD2450_RADAR_SERIAL Serial0
    #define LD2450_RADAR_RX_PIN 32
    #define LD2450_RADAR_TX_PIN 33
  #endif
#elif defined(ESP8266)
  #define LD2450_RADAR_SERIAL Serial
  #define LD2450_RADAR_RX_PIN 0
  #define LD2450_RADAR_TX_PIN 1
#elif defined(AVR)
  #define LD2450_RADAR_SERIAL Serial
  #define LD2450_RADAR_RX_PIN 0
  #define LD2450_RADAR_TX_PIN 1
#endif


class LD2450
{

public:
    typedef struct RadarTarget
    {
        uint16_t id;         // ID
        int16_t x;           // X mm
        int16_t y;           // Y mm
        int16_t speed;       // cm/s
        uint16_t resolution; // mm
    } RadarTarget_t;

    LD2450();
    // Constructor function
    ~LD2450();

    void begin();
    void begin(HardwareSerial &radarStream, bool already_initialized = false);
    void setNumberOfTargets(uint16_t _numTargets);
    uint8_t ProcessSerialDataIntoRadarData(byte rec_buf[], int len);
    String getLastTargetMessage();
    uint8_t read();

protected:
private:
    Stream *radar_uart = nullptr;
    RadarTarget_t radarTargets[LD2450_MAX_SENSOR_TARGETS]; // Stores the target of the current frame
    uint16_t numTargets = LD2450_MAX_SENSOR_TARGETS;
    String last_target_data = "";
};
#endif