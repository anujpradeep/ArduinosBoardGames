#include "sudoku.h"

extern MCUFRIEND_kbv tft;

extern TouchScreen ts;

int board[N][N];

int prevboard[N][N];

int solution[N][N];

void sudDisplay(){
	int startx = 95;
	int starty = 17;
	tft.setTextSize(2);

	for(int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			tft.setCursor(startx, starty);
			if(prevboard[x][y] != 0 && prevboard[x][y] == board[x][y]){
				tft.setTextColor(TFT_WHITE, TFT_BLACK);
				tft.print(prevboard[x][y]);
			}
			else if(prevboard[x][y] != 0 && prevboard[x][y] != board[x][y]){
				tft.setTextColor(TFT_RED, TFT_BLACK);
				tft.print(prevboard[x][y]);
			}
			startx += 35;
		}
		startx = 95;
		starty += 35;
	}
}
int sudSelect(){
	tft.fillScreen(TFT_BLACK);
	tft.fillRect(0, 0, 480, 107, TFT_RED);
	tft.setCursor(220, 53);
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_RED);
	tft.print("1");

	tft.fillRect(0, 214, 480, 106, TFT_RED);
	tft.setCursor(220, 267);
	tft.setTextSize(5);
	tft.setTextColor(TFT_WHITE, TFT_RED);
	tft.print("2");

	tft.setCursor(140, 158);
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.println("Select Sudoku Game");

	int selection = 0;
	screenCord touched;
	while(selection == 0){
		touched = processTouchScreen();
		if(touched.y < 107){
			return 1;
		}
		else if(touched.y > 214){
			return 2;
		}
	}
}
void sudLoad(int game){
	if(game == 1){
		int b[N][N] = { {3,0,6,5,0,8,4,0,0},
				   	{5,2,0,0,0,0,0,0,0},
				   	{0,8,7,0,0,0,0,3,1},
				    {0,0,3,0,1,0,0,8,0},
				   	{9,0,0,8,6,3,0,0,5},
				  	{0,5,0,0,9,0,6,0,0},
				   	{1,3,0,0,0,0,2,5,0},
					{0,0,0,0,0,0,0,7,4},
					{0,0,5,2,0,6,3,0,0} };

		memcpy(board, b, sizeof(b));
		memcpy(prevboard, b, sizeof(b));
	}
	if(game == 2){
		int b[N][N] = { {5,3,0,0,7,0,0,0,0},
				   		{6,0,0,1,9,5,0,0,0},
				   		{0,9,8,0,0,0,0,6,0},
					    {8,0,0,0,6,0,0,0,3},
					   	{4,0,0,8,0,3,0,0,1},
					  	{7,0,0,0,2,0,0,0,6},
					   	{0,6,0,0,0,0,2,8,0},
						{0,0,0,4,1,9,0,0,5},
						{0,0,0,0,8,0,0,7,9} };

		memcpy(board, b, sizeof(b));
		memcpy(prevboard, b, sizeof(b));				
	}
}

void sudSetup(){
	tft.fillRect(0, 0, 480, 320, TFT_BLACK);
	
	int startx = 84;
	int starty = 4;

	for(int i= 1; i < 3; i++){
		tft.drawFastHLine(startx, starty + i*35, 396, TFT_WHITE);
		tft.drawFastVLine(startx + i*35, starty, 312, TFT_WHITE);
	}

	starty = 108;
	for(int i = 1; i < 3; i++){
		tft.drawFastHLine(startx, starty + i*35, 396, TFT_WHITE);
	}

	starty = 212;
	for(int i = 1; i < 3; i++){
		tft.drawFastHLine(startx, starty + i*35, 396, TFT_WHITE);
	}

	starty = 4;
	startx = 188;
	for(int i = 1; i < 3; i++){
		tft.drawFastVLine(startx + i*35, starty, 312, TFT_WHITE);
	}

	for(int i = 1; i < 3; i++){
		tft.drawFastVLine(startx + i*35, starty, 312, TFT_WHITE);
	}
	startx = 292;
	for(int i = 1; i < 3; i++){
		tft.drawFastVLine(startx + i*35, starty, 312, TFT_WHITE);
	}

	tft.drawRect(84, 4, 312, 312, TFT_RED);

	tft.drawRect(84, 4, 104, 312, TFT_RED);
	tft.drawRect(84, 4, 208, 312, TFT_RED);	

	tft.drawRect(84, 4, 312, 104, TFT_RED);
	tft.drawRect(84, 4, 312, 208, TFT_RED);	

	tft.fillRect(397, 4, 48, 312, TFT_BLACK);
	tft.drawRect(445, 4, 35, 312, TFT_RED);
	tft.drawFastHLine(445, 109, 35, TFT_WHITE);
	tft.drawFastHLine(445, 214, 35, TFT_WHITE);

	int cursy = 17;
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	for(int i = 1; i < 10; i++){
		tft.setCursor(458, cursy);
		tft.print(i);
		cursy += 35;
	}

	tft.fillRect(0, 140, 75, 40, TFT_RED);
	tft.setCursor(10, 155);
	tft.setTextSize(1);
	tft.setTextColor(TFT_WHITE, TFT_RED);
	tft.print("Make Move");

	tft.fillRect(0, 280, 75, 40, TFT_RED);
	tft.setCursor(10, 295);
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_RED);
	tft.print("EXIT");

	int temp[N][N];
	memcpy(temp,board,sizeof(board));
	//solves the board and saves the right solution in temp
	solveBoard(temp);
	//copies it into soln so we can use it in check win
	memcpy(solution,temp,sizeof(temp));


}

int selectedNum(screenCord touched){

	if(touched.x > 445 && touched.y < 39){
		return 1;
	}
	else if(touched.x > 445 && touched.y < 74){
		return 2;
	}
	else if(touched.x > 445 && touched.y < 109){
		return 3;
	}
	else if(touched.x > 445 && touched.y < 144){
		return 4;
	}
	else if(touched.x > 445 && touched.y < 179){
		return 5;
	}
	else if(touched.x > 445 && touched.y < 214){
		return 6;
	}
	else if(touched.x > 445 && touched.y < 249){
		return 7;
	}
	else if(touched.x > 445 && touched.y < 284){
		return 8;
	}
	else if(touched.x > 445 && touched.y < 319){
		return 9;
	}
	return 0;
}
int getColumn(screenCord touched){

	if(touched.x < 119){
		return 0;
	}
	else if(touched.x < 154){
		return 1;
	}
	else if(touched.x < 189){
		return 2;
	}
	else if(touched.x < 224){
		return 3;
	}
	else if(touched.x < 259){
		return 4;
	}
	else if(touched.x < 294){
		return 5;
	}
	else if(touched.x < 329){
		return 6;
	}
	else if(touched.x < 364){
		return 7;
	}
	else if(touched.x < 399){
		return 8;
	}
	return 0;
}
int getRow(screenCord touched){
	if(touched.y < 39){
		return 0;
	}
	else if(touched.y < 74){
		return 1;
	}
	else if(touched.y < 109){
		return 2;
	}
	else if(touched.y < 144){
		return 3;
	}
	else if(touched.y < 179){
		return 4;
	}
	else if(touched.y < 214){
		return 5;
	}
	else if(touched.y < 249){
		return 6;
	}
	else if(touched.y < 284){
		return 7;
	}
	else if(touched.y < 319){
		return 8;
	}
	return 0;
}

void makeMove(int row, int col, int num){
	if(board[row][col] == 0 && num != 0){
		prevboard[row][col] = num;
		sudDisplay();
	}
}
rowcol empty(int b[N][N]){
	rowcol temp;
	temp.row = -1;
	for(int r = 0;r<N;r++){
		for(int c = 0;c<N;c++){
			if(b[r][c] == 0){
				temp.row = r;
				temp.col = c;
				return temp;
			}
		}
	}
	return temp;
}
bool ifsafe(int b[N][N],int row,int col,int num){
	if(b[row][col] != 0){
		return false;
	}
	//checks col for number
	for(int c = 0;c<N;c++){
		if(b[row][c] == num){
			return false;
		}
	}
	//checks row for number
	for(int r = 0; r<N;r++){
		if(b[r][col]==num){
			return false;
		}
	}
	//checks box for number
	int rowboxstart = row - row%3;
	int colboxstart = col -col%3;
	for(int r = rowboxstart;r<rowboxstart+3;r++){
		for(int c = colboxstart;c<colboxstart+3;c++){
			if(b[r][c] == num){
				return false;
			}
		}
	}
	return true;
}

bool solveBoard(int b[N][N]){
	rowcol first = empty(b);
	if(first.row == -1){
		return true; //No unassigned numbers
	}
	for(int i = 1;i <= 9;i++){
		if(ifsafe(b,first.row,first.col,i)){
			b[first.row][first.col] = i;

			if(solveBoard(b)){
				return true;
			}
			//backtrack back as i is wrong
			b[first.row][first.col] = 0;
		}
	}
	return false;
}

bool winCheck(){
	int counter = 0;
	for(int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			if(prevboard[x][y] == solution[x][y]){
				counter += 1;
			}
		}
	}
	if(counter == 81){
		return true;
	}

	return false;
}
void runSud(){
	int choice = sudSelect();
	int num = 0;
	int row = 0;
	int col = 0;
	bool gameover = false;
	bool quit = false;
	sudLoad(choice);
	sudSetup();
	sudDisplay();
	while(!gameover && !quit){
		screenCord touched = processTouchScreen();
		if(touched.x > 445){
			num = selectedNum(touched);
		}
		tft.setCursor(0, 0);
		tft.setTextSize(1);
		tft.print("Num = ");
		tft.print(num);
		if(touched.x > 84 && touched.x < 396){
			col = getColumn(touched);
			row = getRow(touched);
		}
		tft.setCursor(0, 10);
		tft.setTextSize(1);
		tft.print("Row = ");
		tft.println(row);
		tft.print("Col = ");
		tft.println(col);
		if(touched.x < 75 && touched.y < 180 && touched.y > 140){
			makeMove(row, col, num);
		}
		if(touched.x < 75 && touched.y < 320 && touched.y > 280){
			quit = true;
		}
		gameover = winCheck();
	}
	if(!quit){
		tft.fillRect(200, 120, 120, 80, TFT_RED);
		tft.setCursor(220, 140);
		tft.setTextSize(3);
		tft.setTextColor(TFT_WHITE, TFT_RED);
		tft.print("You Win!");		
	}


}