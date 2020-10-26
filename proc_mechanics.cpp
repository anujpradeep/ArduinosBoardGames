#include "proc_mechanics.h"

extern TouchScreen ts;
extern MCUFRIEND_kbv tft;



int processJoystick() {
  int xVal = analogRead(JOY_HORIZ);
  int yVal = analogRead(JOY_VERT);
  //int buttonVal = digitalRead(JOY_SEL);

  // now move the cursor
  if (yVal < JOY_CENTER - JOY_DEADZONE) {
    return -1; // decrease the y coordinate of the cursor
  }
  else if (yVal > JOY_CENTER + JOY_DEADZONE) {
    return 1;
  }

  // remember the x-reading increases as we push left
  if (xVal > JOY_CENTER + JOY_DEADZONE) {
    return -1;
  }
  else if (xVal < JOY_CENTER - JOY_DEADZONE) {
    return 1;
  }
  else{
  	return 0;
  }
}

screenCord processTouchScreen() {
	screenCord coordinates;
	pinMode(YP, INPUT); 
	pinMode(XM, INPUT);
	TSPoint touch = ts.getPoint();

	// restore pinMode to output after reading the touch
    // this is necessary to talk to tft display

	while(touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {
		touch = ts.getPoint();
	}

	coordinates.x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH-1, 0);
	coordinates.y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT-1, 0);

	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 
	return coordinates;
	delay(200);
}