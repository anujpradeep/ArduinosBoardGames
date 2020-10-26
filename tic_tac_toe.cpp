#include "tic_tac_toe.h"

extern MCUFRIEND_kbv tft;

extern TouchScreen ts;

int ticarray[3][3] = {0};

void arrayReset(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			ticarray[i][j] = 0;
		}
	}
}
void ticSetup(){
	arrayReset();
	tft.fillScreen(TFT_BLACK);
	tft.drawLine(0, 20, 480, 20, TFT_YELLOW);
	tft.drawLine(160, 20, 160, 320, TFT_YELLOW);
	tft.drawLine(320, 20, 320, 320, TFT_YELLOW);
	tft.drawLine(0, 127, 480, 127, TFT_YELLOW);
	tft.drawLine(0, 234, 480, 234, TFT_YELLOW);

}

bool ticWin(){
	int inrow; //amount of same elements in a row

	for(int i = 0; i < 3; i++){ //horizontal check
		inrow = 1;
		for(int j = 0; j < 2; j++){
			if(ticarray[i][j] == ticarray[i][j+1] && ticarray[i][j] != 0){
				inrow += 1;
			}
		}
		if(inrow == 3){
			return true;
		}
	}

	for(int i = 0; i < 3; i++){ //vertical check
		inrow =1;
		for(int j = 0; j < 2; j++){
			if(ticarray[j][i] == ticarray[j+1][i] && ticarray[j][i] != 0){
				inrow += 1;
			}
		}
		if(inrow == 3){
			return true;
		}
	}


	if(ticarray[0][0] == ticarray[1][1] && ticarray[1][1] == ticarray[2][2] && ticarray[1][1] != 0){
		return true;
	}
	if(ticarray[0][2] == ticarray[1][1] && ticarray[1][1] == ticarray[2][0] && ticarray[1][1] != 0){
		return true;
	}	

	return false;
}

bool fullCheck(){
	int full = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(ticarray[i][j] != 0){
				full += 1;
			}
		}
	}
	if(full == 9){
		return true;
	}

	return false;
}

void printXO(char player){
		tft.setTextSize(5);
		tft.setTextColor(TFT_WHITE, TFT_BLACK);
		tft.print(player);
}
bool ticSection(screenCord coordinates, bool turn){
	int16_t xpoint = coordinates.x;
	int16_t ypoint = coordinates.y;
	char player; //so we know what letter to print
	int ind; //index for ticarray 1 = X, 2 = O
	if(turn){
		player = 'X';
		ind = 1;
	}
	else{
		player = 'O';
		ind = 2;
	}
	//Serial.println(xpoint);
	if(xpoint < 160){
		if(ypoint < 127){
			tft.setCursor(75, 60);
			printXO(player);
			ticarray[0][0] = ind;
		}
		else if(ypoint < 234){
			tft.setCursor(75, 167);
			printXO(player);
			ticarray[1][0] = ind;
		}
		else{
			tft.setCursor(75, 274);
			printXO(player);
			ticarray[2][0] = ind;
		}
	}
	else if(xpoint < 320){
		if(ypoint < 127){
			tft.setCursor(235, 60);
			printXO(player);
			ticarray[0][1] = ind;
		}
		else if(ypoint < 234){
			tft.setCursor(235, 167);
			printXO(player);
			ticarray[1][1] = ind;
		}
		else{
			tft.setCursor(235, 274);
			printXO(player);
			ticarray[2][1] = ind;
		}
	}
	else{
		if(ypoint < 127){
			tft.setCursor(395, 60);
			printXO(player);
			ticarray[0][2] = ind;
		}
		else if(ypoint < 234){
			tft.setCursor(395, 167);
			printXO(player);
			ticarray[1][2] = ind;
		}
		else{
			tft.setCursor(395, 274);
			printXO(player);
			ticarray[2][2] = ind;
		}
	}

	return ticWin();
}

void ticTac(){
	ticSetup();
	bool turn = true; //true for X false for O
	bool gameover = false;
	bool tablefull = false;
	while(!gameover && !tablefull){
		if(turn){
			tft.setCursor(155, 3);
			tft.setTextColor(TFT_WHITE, TFT_BLACK);
			tft.setTextSize(2);
			tft.print("Player X's Turn");
			
			screenCord touched = processTouchScreen();
			gameover = ticSection(touched, turn);
			tablefull = fullCheck();
			turn = false; //change to 0

		}else{
			tft.setCursor(155, 3);
			tft.setTextSize(2);
			tft.setTextColor(TFT_WHITE, TFT_BLACK);
			tft.print("Player O's Turn");	

			screenCord touched = processTouchScreen();
			gameover = ticSection(touched, turn);
			tablefull = fullCheck();
			turn = true; //change to X
		}
		delay(100);
	}
	if(!tablefull || gameover){
		if(turn){
			tft.fillRect(80, 53, 320, 214, TFT_YELLOW);
			tft.setCursor(100, 127);
			tft.setTextSize(7);
			tft.setTextColor(TFT_BLACK, TFT_YELLOW);
			tft.print("O Wins!");
		}
		else{
			tft.fillRect(80, 53, 320, 214, TFT_YELLOW);
			tft.setCursor(100, 127);
			tft.setTextSize(7);
			tft.setTextColor(TFT_BLACK, TFT_YELLOW);
			tft.print("X Wins!");
		}
	}
	else{
		tft.fillRect(80, 53, 320, 214, TFT_YELLOW);
		tft.setCursor(180, 127);
		tft.setTextSize(7);
		tft.setTextColor(TFT_BLACK, TFT_YELLOW);
		tft.print("Tie!");
	}
}