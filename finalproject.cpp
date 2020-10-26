////////////////////////////////////
//Name: Hetul Patel & Anuj Pradeep
//ID: 1571187 & 1578030
//CMPUT 275, Winter 2020
//
//Final Project
////////////////////////////////////
#include "constants_and_types.h"
#include "proc_mechanics.h"
#include <TouchScreen.h>
#include <Arduino.h>
// core graphics library (written by Adafruit)
#include <Adafruit_GFX.h>
// Hardware-specific graphics library for MCU Friend 3.5" TFT LCD shield
#include "tic_tac_toe.h"
#include "maze.h"
#include "sudoku.h"
MCUFRIEND_kbv tft;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
void setup(){
	init();

	Serial.begin(9600);
	pinMode(JOY_SEL, INPUT_PULLUP);

	uint16_t ID = tft.readID(); 
	tft.begin(ID); 
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);

	//mainScreen();
}

/*
This function sets up our main screen
*/
void mainScreen(){
	tft.fillRect(160,110, 160, 110, TFT_WHITE);

	tft.fillRect(0, 0, 160, 220, TFT_RED);
	tft.setTextSize(4);
	tft.setTextColor(TFT_WHITE, TFT_RED);
	int ycoord = 30;
	char sud[6] = {'S', 'U', 'D', 'O', 'K', 'U'};
	for(int i = 0; i < 6; i++){
		tft.setCursor(70, ycoord);
		tft.println(sud[i]);
		ycoord += 30;
	}

	tft.fillRect(320, 110, 160, 210, TFT_GREEN);
	tft.setCursor(170, 155);
	tft.setTextSize(4);
	ycoord = 145;
	tft.setTextColor(TFT_BLACK, TFT_GREEN);
	char rul[5] = {'R', 'U', 'L', 'E', 'S'};
	for(int i = 0; i < 5; i++){
		tft.setCursor(390, ycoord);
		tft.println(rul[i]);
		ycoord += 30;
	}	
	tft.fillRect(160, 0, 320, 110, TFT_BLUE);
	tft.setCursor(265, 40);
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_BLUE);
	tft.print("MAZE");
	

	tft.fillRect(0, 220, 320, 110, TFT_YELLOW);
	tft.setCursor(65, 260);
	tft.setTextSize(3);
	tft.setTextColor(TFT_BLACK, TFT_YELLOW);
	tft.print("TIC TAC TOE");

	tft.setCursor(170, 155);
	tft.setTextSize(2);
	tft.setTextColor(TFT_BLACK, TFT_WHITE);
	tft.print("Select Game");

}

/*
This function determines what game was selected
depending on where the user touched on the screen
*/
int selection(){
	//red = 1, yel = 2, gre = 3, blu = 4
	int game = 0;
	screenCord touched = processTouchScreen();
	if(touched.x < 160 && touched.y < 220){
		game = 1;
	}
	else if(touched.x < 320 && touched.y > 220){
		game = 2;
	}
	else if(touched.x > 320 && touched.y > 110){
		game = 3;
	}
	else if(touched.x > 160 && touched.y < 110){
		game = 4;
	}
	return game;
}

/*
This function is just for a transition,
it redraws black rectangles in a specifc 
pattern
*/
void transition(){
	int redcount = 0;
	int yelcount = 160;
	int grecount = 320;
	int blucount = 480;
	int midcount = 0;
	tft.fillRect(160,110, 160, 110, TFT_WHITE);
	while(redcount != 320){
		tft.fillRect(0,redcount, 160, 5, TFT_BLACK);
		redcount = redcount + 5;
	}
	while(yelcount != 480){
		tft.fillRect(yelcount, 220, 5, 110, TFT_BLACK);
		yelcount = yelcount + 5;
	}
	while(grecount != -225){
		tft.fillRect(320, grecount, 160, 5, TFT_BLACK);
		grecount = grecount - 5;
	}
	while(blucount != 155){
		tft.fillRect(blucount, 0, 5, 110, TFT_BLACK);
		blucount = blucount - 5;
	}
	while(midcount != 115){
		tft.fillRect(160, 110, 160, midcount, TFT_BLACK);
		midcount = midcount + 5;
	}
}

/*
This function is called if the user
clicks on the rules box on the screen
and it just shows how to play the various games
*/
void rules(){
	tft.fillScreen(TFT_GREEN);
	tft.setCursor(15, 10);

	tft.setTextSize(3);
	tft.setTextColor(TFT_BLACK, TFT_GREEN);	
	tft.println("Rules for Sudoku");
	tft.setTextSize(2);
	tft.println("1. In order to input numbers into boxes");
	tft.println(" you need to select your desired number");
	tft.println(" from the panel of numbers on the right");
	tft.println(" and then tap the desired box and then");
	tft.println(" tap 'Make Move'");

	tft.setTextSize(3);
	tft.setCursor(15, 115);
	tft.println("Rules for Tic Tac Toe");
	tft.setTextSize(2);
	tft.println("2. The basic rules apply, but in order");
	tft.println(" to account for misclicks we allow");
	tft.println(" players to change already clicked boxes");

	tft.setTextSize(3);
	tft.setCursor(15, 200);
	tft.println("Rules for Maze");
	tft.setTextSize(2);
	tft.println("3. For the maze the player is the yellow");
	tft.println(" box and the destination is the red box");
	tft.println(" use the boxes on the right side to move");
	tft.println(" U for Up, D for Down, R for Right, L");	
	tft.println(" for Left");

	tft.fillRect(420, 290, 60, 30, TFT_BLACK);
	tft.setCursor(430, 300);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.print("EXIT");
	while(true){
		screenCord touched = processTouchScreen();
		if(touched.x > 420 && touched.y > 290){
			break;
		}
	}
}

int main(){
	int random;
	setup();
	mainScreen();
	int game = 0;
	
	while(game == 0){
		game = selection();
	}
	
	transition();
	if(game == 1){
		runSud();
	}
	else if(game == 2){
		ticTac();	
	}
	else if(game == 3){
		rules();
	}
	else if(game == 4){
		runMaze();
	}
	delay(200);	
	random = main();
  return 0;
}