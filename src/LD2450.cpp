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
#ifndef LD2450_cpp
#define LD2450_cpp

#include "LD2450.h"

LD2450::LD2450() // Constructor function
{
}

LD2450::~LD2450() // Destructor function
{
}

void LD2450::begin(Stream &radarStream)
{

    radar_uart = &radarStream;

    LD2450::setNumberOfTargets(MAX_SENSOR_TARGETS);
}

void LD2450::setNumberOfTargets(uint16_t _numTargets)
{
    if (_numTargets > MAX_SENSOR_TARGETS)
    {
        _numTargets = MAX_SENSOR_TARGETS;
    }
    if (_numTargets < 0)
    {
        _numTargets = 0;
    }
    LD2450::numTargets = _numTargets;
}

String LD2450::getLastTargetMessage()
{
    return LD2450::last_target_data;
}

uint8_t LD2450::read()
{
    if (LD2450::radar_uart == nullptr)
    {
        return -2;
    }

    if (LD2450::radar_uart->available() > 0)
    {
        byte rec_buf[SERIAL_BUFFER] = "";
        int len = LD2450::radar_uart->readBytes(rec_buf, sizeof(rec_buf));

        if (len > 0)
        {
            return LD2450::ProcessSerialDataIntoRadarData(rec_buf, len);
        }
    }
    return -1;
}

uint8_t LD2450::ProcessSerialDataIntoRadarData(byte rec_buf[], int len)
{
    uint8_t redreshed_targets = 0;

    for (int i = 0; i < len; i++)
    {
        // Checking the header and footer
        if (rec_buf[i] == 0xAA && rec_buf[i + 1] == 0xFF && rec_buf[i + 2] == 0x03 && rec_buf[i + 3] == 0x00 && rec_buf[i + 28] == 0x55 && rec_buf[i + 29] == 0xCC)
        {

            int index = i + 4; // Skip header and in-frame data length fields
            LD2450::last_target_data = "";

            for (int targetCounter = 0; targetCounter < LD2450::numTargets; targetCounter++)
            {
                if (index + 7 < len)
                {
                    LD2450::RadarTarget target;
                    target.x = (int16_t)(rec_buf[index] | (rec_buf[index + 1] << 8));
                    target.y = (int16_t)(rec_buf[index + 2] | (rec_buf[index + 3] << 8));
                    target.speed = (int16_t)(rec_buf[index + 4] | (rec_buf[index + 5] << 8));
                    target.resolution = (uint16_t)(rec_buf[index + 6] | (rec_buf[index + 7] << 8));

                    // debug_serial.println(target.x);
                    // debug_serial.println(target.y);
                    // debug_serial.println(target.speed);

                    // Check the highest bit of x and y. Adjust the sign
                    if (rec_buf[index + 1] & 0x80)
                        target.x -= 0x8000;
                    else
                        target.x = -target.x;
                    if (rec_buf[index + 3] & 0x80)
                        target.y -= 0x8000;
                    else
                        target.y = -target.y;
                    if (rec_buf[index + 5] & 0x80)
                        target.speed -= 0x8000;
                    else
                        target.speed = -target.speed;

                    LD2450::radarTargets[targetCounter].id = targetCounter + 1;
                    LD2450::radarTargets[targetCounter].x = target.x;
                    LD2450::radarTargets[targetCounter].y = target.y;
                    LD2450::radarTargets[targetCounter].speed = target.speed;
                    LD2450::radarTargets[targetCounter].resolution = target.resolution;

                    // Add target information to the string
                    LD2450::last_target_data += "TARGET ID=" + String(targetCounter + 1) + " X=" + target.x + "mm, Y=" + target.y + "mm, SPEED=" + target.speed + "cm/s, RESOLUTION=" + target.resolution + "mm\n";

                    index += 8; // Move to the start of the next target data

                    redreshed_targets++;
                }
            }

            i = index; // Updating the index of an external loop
        }
    }
    return redreshed_targets;
}

#endif