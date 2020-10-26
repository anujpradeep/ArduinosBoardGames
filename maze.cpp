
#include "maze.h"

extern MCUFRIEND_kbv tft;

extern TouchScreen ts;

char maze[10][10];
int cursorX, cursorY;
int prevcursorX, prevcursorY;
int playerx = 0, playery = 0;
int mazeSelect(){
	tft.fillScreen(TFT_BLACK);
	tft.fillRect(0, 0, 160, 320, TFT_BLUE);
	tft.setCursor(75, 130);
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLUE);
	tft.print("1");

	tft.fillRect(320, 0, 160, 320, TFT_BLUE);
	tft.setCursor(395, 130);
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLUE);
	tft.print("2");

	tft.setCursor(177, 140);
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.println("Select Maze");

	int selection = 0;
	screenCord touched;
	while(selection == 0){
		touched = processTouchScreen();
		if(touched.x < 160){
			return 1;
		}
		else if(touched.x > 320){
			return 2;
		}
	}
}

void mazeSelector(int c){
	if(c==1){
		char m[10][10] = {{ 'P','+','#','#','+','+','+','#','#','#'},
				   		{ '#','+','+','+','+','#','+','#','+','+'},
				   		{ '#','+','#','#','#','+','+','#','+','#'},
				   		{ '+','+','+','#','#','+','#','#','+','#'},
				   		{ '+','#','#','+','+','+','#','+','+','#'},
				   		{ '+','#','+','#','#','+','#','+','+','#'},
				   		{ '+','+','+','#','+','+','+','#','+','+'},
					   	{ '#','#','+','+','+','#','+','+','+','#'},
					   	{ '#','#','+','#','#','#','#','#','#','#'},
					   	{ '#','#','+','+','+','+','+','+','+','D'}};
		memcpy(maze,m,sizeof(m));
	}else{
		char m[10][10] = {{ 'P','+','+','+','+','+','+','+','+','+'},
				   		{ '#','+','#','+','#','+','#','+','#','+'},
				   		{ '#','+','#','+','#','+','#','+','#','+'},
				   		{ '#','+','#','+','#','+','#','+','#','+'},
				   		{ '#','+','#','#','#','+','#','+','#','+'},
				   		{ '#','+','#','#','#','+','#','+','#','+'},
				   		{ '#','+','+','+','+','+','#','+','+','+'},
					   	{ '#','#','+','#','#','#','#','#','+','#'},
					   	{ '#','+','#','#','#','#','#','#','+','#'},
					   	{ '#','+','+','+','+','#','#','#','+','D'}};
		memcpy(maze,m,sizeof(m));
	}
}

startEnd mazeSetup(){
	tft.fillScreen(TFT_BLACK);
	tft.fillRect(190, 110, 100, 100, TFT_WHITE);
	startEnd locations;
	int startx = 190;
	int starty = 110;
	char component;

	for(int y = 0; y < 10; y++){
		for(int x = 0; x < 10; x++){
			component = maze[y][x];

			if(component == '#'){
				tft.fillRect(startx + x*10, starty + y*10, 10, 10, TFT_BLUE);
			}
			else if(component == 'P'){
				tft.fillRect(startx + x*10, starty + y*10, 10, 10, TFT_GREEN);
				locations.start.xcord = startx + x*10;
				locations.start.ycord = starty + y*10;
			}
			else if(component == 'D'){
				tft.fillRect(startx + x*10, starty + y*10, 10, 10, TFT_RED);
				locations.end.xcord = startx + x*10;
				locations.end.ycord = starty + y*10;
			}

		}
	}
	return locations;
}

void redrawCursor(uint16_t colour) {
  tft.fillRect(cursorX - CURSOR_SIZE/2, cursorY - CURSOR_SIZE/2,
			   CURSOR_SIZE, CURSOR_SIZE, colour);
}
void redrawPrevCursor(uint16_t colour) {
  tft.fillRect(prevcursorX - CURSOR_SIZE/2, prevcursorY - CURSOR_SIZE/2,
			   CURSOR_SIZE, CURSOR_SIZE, colour);
}
void playerMovement(startEnd location) {

  int xPlay = analogRead(JOY_HORIZ);
  int yPlay = analogRead(JOY_VERT);

  int pmovex = 0, pmovey =0;
  //following variables are used to store cursor position before moving
  prevcursorX = cursorX; 
  prevcursorY = cursorY; 

  // now move the cursor
  if (yPlay < JOY_CENTER - JOY_DEADZONE) {
	cursorY -= 1; // decrease the y coordinate of the cursor
	pmovey = -1;
  }
  else if (yPlay > JOY_CENTER + JOY_DEADZONE) {
	cursorY += 1;
	pmovey = 1;
  }

  // remember the x-reading increases as we push left
  if (xPlay > JOY_CENTER + JOY_DEADZONE) {
	cursorX -= 1;
	pmovex = -1;
  }
  else if (xPlay < JOY_CENTER - JOY_DEADZONE) {
	cursorX += 1;
	pmovex = 1;
  }

  cursorX = constrain(cursorX, 190 + CURSOR_SIZE/2, 289 - CURSOR_SIZE/2); //prevents  cursor from going off screen in x
  cursorY = constrain(cursorY, 110 + CURSOR_SIZE/2, 209 - CURSOR_SIZE/2); //prevents cursor from going off screen in y

  // Checks if cursor actually moved before redraws
  // this prevents flickering while stationary
  if ((cursorY != prevcursorY) || (cursorX != prevcursorX)){
  	if(safe(playerx + pmovex, playery + pmovey)){
  		return;
  	}
	//redraws the image in previous cursor position making use of global yegMidddle
	maze[playerx][playery] = '+';
	playerx += pmovex;
	playery += pmovey;
	maze[playerx][playery] = 'P';

	redrawPrevCursor(TFT_WHITE);
  	// drawing a red rectangle at the new cursor position
	redrawCursor(TFT_YELLOW);
	}

  delay(20);
}

bool safe(int x, int y){
	if(x > 9 || x < 0){
		return false;
	}
	if(y > 9 || y < 0){
		return false;
	}
	if(maze[x][y] == '#'){
		return false;
	}

	return true;
}
void runMaze(){
	int selection = mazeSelect();
	bool gameover;

	mazeSelector(selection);

	startEnd loc = mazeSetup();
	cursorX = loc.start.xcord + CURSOR_SIZE/2;
  	cursorY = loc.start.ycord + CURSOR_SIZE/2;
  	redrawCursor(TFT_YELLOW);
	while(true){
		playerMovement(loc);
	}
}
