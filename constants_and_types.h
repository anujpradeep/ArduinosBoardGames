#ifndef __CONSTANTS_AND_TYPES_H
#define __CONSTANTS_AND_TYPES_H

#define JOY_VERT  A9 // should connect A9 to pin VRx
#define JOY_HORIZ A8 // should connect A8 to pin VRy
#define JOY_SEL   53

#define JOY_CENTER   512
#define JOY_DEADZONE 64


// touch screen pins, obtained from the documentaion
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// width/height of the display when rotated horizontally
#define TFT_WIDTH  480
#define TFT_HEIGHT 320

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 100
#define TS_MINY 110
#define TS_MAXX 960
#define TS_MAXY 910

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

#include <TouchScreen.h>

#include <Arduino.h>

// core graphics library (written by Adafruit)
#include <Adafruit_GFX.h>

// Hardware-specific graphics library for MCU Friend 3.5" TFT LCD shield
#include <MCUFRIEND_kbv.h>

/*
This structure is called in the code whenever we wish to get
the touch screen reading. ts.getPoint() returns int16_t values
so the struct contains int16_t for x and y of the touchscreen.
*/
struct screenCord {
	int16_t x, y;
};



#endif