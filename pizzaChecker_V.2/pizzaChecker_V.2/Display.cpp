/*
 * Rich shield example
 * Adapted from Rich Shield Example Code
 * Name:
 * Date: 07/06/2019
 * Author: Jaap Geurts <jaap.geurts@fontys.nl>
 * Version: 1.0
 */
#include "Display.h"
#include "math.h"

// global variable for accessing the display.
DisplayHardware Display;

// mapping of digits and letters to the leds of the display.

//
//    a
//  +----+
//  |    |
// f| g  |b
//  +----+
// e|    |c
//  | d  |
//  +----+ * h
//
// construct the byte as follows:
// each segment letter is a bit/
// a = LSB, h = MSB
// hgfe.dcba
// examples:
// 4 = 01100110 = 0x66
// 7 = 00000111 = 0x07


const uint8_t NUM_DIGITS = 4;

// constants to index into the map

const uint8_t INDEX_NEGATIVE_SIGN = 16;
const uint8_t INDEX_UNDERSCORE = 17;
const uint8_t INDEX_BLANK = 18;
const uint8_t INDEX_H = 19;
const uint8_t INDEX_U = 20;
const uint8_t INDEX_R = 21;

uint8_t digit_segment_map[] =   {0x3f, 0x06, 0x5b, 0x4f, // 0 1 2 3
                                 0x66, 0x6d, 0x7d, 0x07, // 4 5 6 7
                                 0x7f, 0x6f, 0x77, 0x7c, // 8 9 A B
                                 0x39, 0x5e, 0x79, 0x71, // C d E F
                                 0x40, 0x08, 0x00, 0x76, // - _ " " H
                                 0x3e, 0x50 // U r
                                };
// 0~9,A,b,C,d,E,F,"-","_"," " ,"H", "U","r"

// timing delay when talking to the TM1637
const uint8_t SIGNAL_DELAY = 50;

const char error[] = "err ";

const uint8_t ADDR_AUTO = 0x40;
const uint8_t ADDR_FIXED = 0x44;
const uint8_t STARTADDR = 0xc0;

DisplayHardware::DisplayHardware(uint8_t clockPin, uint8_t dataPin)
{
    _clockPin = clockPin;
    _dataPin = dataPin;

    _setData = ADDR_AUTO;
    _setAddress = STARTADDR;
    /*  BRIGHT_DARKEST 0
        BRIGHT_TYPICAL 2
        BRIGHTEST      7
    */
    _displayControl = 0x88 + 7;
}

void DisplayHardware::writeByte(uint8_t data)
{

    // send the 8 Data Bits
    for (uint8_t i = 0; i < 8; i++)
    {
        // CLK low
        pinMode(_clockPin, OUTPUT);
        bitDelay();

        // Set data bit
        if (data & 0x01)
        {
            pinMode(_dataPin, INPUT);
        }
        else
        {
            pinMode(_dataPin, OUTPUT);
        }

        bitDelay();

        // CLK high
        pinMode(_clockPin, INPUT);
        bitDelay();
        data = data >> 1;
    }

    // Wait for acknowledge
    // CLK to zero
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, INPUT);
    bitDelay();

    // CLK to high
    pinMode(_clockPin, INPUT);
    bitDelay();
    uint8_t ack = digitalRead(_dataPin);

    if (ack == 0)
    {
        pinMode(_dataPin, OUTPUT);
    }

    bitDelay();
    pinMode(_clockPin, OUTPUT);
    bitDelay();

}
void DisplayHardware::showRaw(uint8_t digitPos, uint8_t segmentcode)
{
    start();          //start signal sent to TM1637 from MCU
    writeByte(ADDR_FIXED);//
    stop();           //
    start();          //
    writeByte(digitPos | 0xc0); //
    writeByte(segmentcode);//
    stop();            //
    start();          //
    writeByte(_displayControl);//
    stop();
}

void DisplayHardware::showCharAt(uint8_t digitPos, char letter)
{
    uint8_t data = mapLetterToSegment(letter);

    showRaw(digitPos, data);
}

void DisplayHardware::showDigitAt(uint8_t digitPos, uint8_t digit, bool showDot)
{
    int8_t data = mapDigitToSegment(digit);
    if (showDot)
        data |= 0x80;
    showRaw(digitPos, data);
}

void DisplayHardware::show(float value)
{
    // if the value is over 9999 (4 digits) or under -999
    if (value < -999 || value > 9999)
    {
        show(error);
        return;
    }


    // figure max numbers to write
    int pos = NUM_DIGITS - 1;

    // figure out where to put the point
    // and convert the value to an int.
    int pointpos = 3;
    float number = value;
    bool neg = number < 0;

    int stoppos = 0;
    int end = 1000;
    // if value is negative, flip, show a - and setup for 3 digits
    if (neg) {
        // if the value is negative show the hyphen -
        number = -number;
        showCharAt(0, '-');
        stoppos = 1;
        end = 100;
    }
    // scale value up to 3 digits if negative, 4 digits if positive.
    // pointpos keeps track of where the . is
    while (number < end && pointpos > stoppos)
    {
        number *= 10;
        pointpos--;
    }

    uint16_t result = number;


    // show the digits
    while (result > 0)
    {
        showDigitAt(pos, result % 10, pointpos == pos);
        result /= 10;
        pos--;
    }

    // show leading zero
    if (pos >= stoppos && pos >= pointpos) {
        showDigitAt(pos,0,pointpos == pos);
        pos--;
    }
    // show leading spaces
    while (pos >= stoppos)
    {
        showCharAt(pos, ' ');
        pos--;
    }

}

void DisplayHardware::show(int value)
{
    int pos = NUM_DIGITS - 1;

    // if the value is over 9999 (4 digits) or under -999
    if ( value < -999 || value > 9999)
    {
        show(error);
        return;
    }

    // if the value is negative show the hyphen -
    bool neg = value < 0;
    int stoppos = 0;
    if (neg) {
        value = -value;
        showCharAt(0, '-');
        stoppos = 1;
    }

    if (value == 0) {
        showDigitAt(pos, 0);
        pos--;
    }
    else {
        // show them
        while (value > 0)
        {
            showDigitAt(pos, value % 10);
            value /= 10;
            pos--;
        }
    }

    // show leading zeros or spaces
    while (pos >= stoppos)
    {
        showCharAt(pos, ' ');
        pos--;
    }

}

void DisplayHardware::show(const char data[])
{
    for (uint8_t i = 0; i < NUM_DIGITS && data[i] != 0; i++)
    {
        showRaw(i, mapLetterToSegment(data[i]));
    }
}


void DisplayHardware::clear()
{
    showRaw(0x00, 0x7f);
    showRaw(0x01, 0x7f);
    showRaw(0x02, 0x7f);
    showRaw(0x03, 0x7f);
}

//send start signal to TM1637
void DisplayHardware::start()
{
    pinMode(_dataPin, OUTPUT);
    bitDelay();
}
//End of transmission
void DisplayHardware::stop()
{
    pinMode(_dataPin, OUTPUT);
    bitDelay();
    pinMode(_clockPin, INPUT);
    bitDelay();
    pinMode(_dataPin, INPUT);
    bitDelay();
}

void DisplayHardware::bitDelay()
{
    delayMicroseconds(SIGNAL_DELAY);
}

uint8_t DisplayHardware::mapDigitToSegment(uint8_t in)
{
    if (in >= 0 && in <= 9)
    {
        return digit_segment_map[in];
    }
    else
    {
        return digit_segment_map[INDEX_UNDERSCORE];
    }
}

uint8_t DisplayHardware::mapLetterToSegment(char letter)
{
    uint8_t data;
    if (letter >= '0' && letter <= '9')
    {
        data = digit_segment_map[letter - '0'];
    }
    else if (letter >= 'A' && letter <= 'F')
    {
        data = digit_segment_map[letter - 'A' + 10];
    }
    else if (letter >= 'a' && letter <= 'f')
    {
        data = digit_segment_map[letter - 'a' + 10];
    }
    else if (letter == ' ')
    {
        data = digit_segment_map[INDEX_BLANK];
    }
    else if (letter == '-')
    {
        data = digit_segment_map[INDEX_NEGATIVE_SIGN];
    }
    else if (letter == '_')
    {
        data = digit_segment_map[INDEX_UNDERSCORE];
    }
    else if (letter == 'H' || letter == 'h')
    {
        data = digit_segment_map[INDEX_H];
    }
    else if (letter == 'U' || letter == 'u')
    {
        data = digit_segment_map[INDEX_U];
    }
    else if (letter == 'R' || letter == 'r')
    {
        data = digit_segment_map[INDEX_R];
    }

    return data;
}
