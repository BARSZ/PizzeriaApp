#ifndef _RICHSHIELD_DISPLAY_H
#define _RICHSHIELD_DISPLAY_H

/*
 * Adapted from Rich Shield Example Code
 * Name:
 * Date: 07/06/2019
 * Author: Jaap Geurts <jaap.geurts@fontys.nl>
 * Version: 1.0
 */

#include <Arduino.h>
#include <inttypes.h>

/**
 * based on code written by Fred Chu
 * License: LGPL
 */

class DisplayHardware
{
  public:

    DisplayHardware(uint8_t clockPin=10, uint8_t dataPin=11);

    void showCharAt(uint8_t digitPos,char letter);
    void showDigitAt(uint8_t digitPos,uint8_t digit, bool showDot = false);
    void show(int value); // display full number
    void show(float value); // display full number
    void show(const char data[]); 
    void setDot(uint8_t pos, bool visible = true);
    void clear();


  private:

    void writeByte(uint8_t data);

    void start();
    void stop();
    void bitDelay();
    uint8_t mapDigitToSegment(uint8_t in);
    uint8_t mapLetterToSegment(char letter);
    
    void showRaw(uint8_t digitPos, uint8_t segmentcode);
      
    uint8_t _clockPin;
    uint8_t _dataPin;
    
    uint8_t _setData;
    uint8_t _setAddress;
    uint8_t _displayControl;
    
};

extern DisplayHardware Display;


#endif
