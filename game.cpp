#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>

#define teste 11;

using namespace std;

char player = 'C';
char blankSpace = '.';
char currentBeneathBlock = ' ';

int mapSizeX=27,mapSizeY=13;

int mapSize = mapSizeX * mapSizeY;

int screenSizeX = 25,screenSizeY=11;

int startCameraOffX = screenSizeX/2, startCameraOffY = screenSizeY/2;
int cameraOffX = startCameraOffX, cameraOffY = startCameraOffY;

int centerScreenPoint = mapSize/2;
int startPlayerPos = mapSize/2;
int playerPos = startPlayerPos;

int currentPlayerRow;
int currentScreenRow;

vector<char> map;

char house[4][11] = 
{
	{' ','_','_','_','_','_','_','_','_','_',' '},
	{'/','_','|','_','|','_','|','_','|','_','\\'},
	{'|','|','_','|','_','_','_','|','_','|','|'},
	{'|','_','_','_','|',' ','|','_','_','_','|'}
};

char tree[5][8] = 
{
	{' ',',','_','_',' ','_',',',' '},
	{'/',' ',' ',',','\\',' ',',','\\'},
	{'\\',',','_','_','|',',','_','/'},
	{' ',' ','|','|','/','/',' ',' '},
	{' ','/','_','_','\\',' ',' ',' '}
};

void drawObj(int startHousePos,void *arr, int y,int x)
{
	char (*obj)[y][x] = (char (*)[y][x]) arr;
	
	int arrayRow = y;
	int arrayCol = x;
		
	int objPos = startHousePos;
	for(int i=0;i < arrayRow; i++)
	{
		for(int x=0; x < arrayCol; x++)
			map[objPos + x] = (*obj)[i][x];
		objPos += mapSizeX;
	}	
}

void createMap()
{
	for(int i=0; i<mapSize; i++)
	{
		map.push_back('.');
	}
	
	/// Drawing objs
	// Houses
	//drawObj(970,house,4,11);
	// Trees
	drawObj(150,tree,5,8);
}

void debugInfo()
{
	cout << "Player Position: " << playerPos << endl;	
	cout << "Block beneath: " << currentBeneathBlock << endl;
	cout << "Center Screen Point: " << centerScreenPoint << endl;		
	cout << endl;
	cout << "Camera offset X: " << cameraOffX << endl;
	cout << "Camera offset Y: " << cameraOffY << endl;
	cout << endl;
	cout << "Map Limit Horizontal: " << mapSizeX << endl;
	cout << "Map Limit Vertical: " << mapSizeY << endl;
	cout << endl;
	cout << "Player Current Row: " << currentPlayerRow << endl;
	cout << "Screen Current Row: " << currentScreenRow << endl;
}

void drawMap()
{
	system("cls");
	
	int centerDiagonalLeft = centerScreenPoint - (mapSizeX * cameraOffY) - cameraOffX;
	int currentRow = 0;
	for(int y=0;y < screenSizeY; y++)
	{ 		
		for(int x = centerDiagonalLeft + currentRow; x < centerDiagonalLeft + screenSizeX + currentRow; x++)
		{
			cout << map[x];
		}
		cout << "\n";
		currentRow += mapSizeX;
	}	
	
	debugInfo();
}

void updatePlayerPos(int newPos)
{
	char nextBlock = map[newPos];
	map[playerPos] = currentBeneathBlock;
	map[newPos] = player;
			
	playerPos = newPos;
	currentPlayerRow = playerPos / mapSizeX;
	
	currentBeneathBlock = nextBlock;
}

void updateScreen(int newPos)
{
	centerScreenPoint = newPos;
	currentScreenRow = centerScreenPoint / mapSizeX;
}

void playerMov()
{
	char ch;

	ch = getch();
	if	    (ch=='w'){	
		if(currentPlayerRow > 0){
			updatePlayerPos(playerPos-mapSizeX);
		}	
		if(currentScreenRow-cameraOffY > 0)
		{
			updateScreen(centerScreenPoint-mapSizeX);	
		}			
		drawMap();
	}	
	else if (ch=='s'){		
		if((currentPlayerRow+1) < mapSizeY){
			updatePlayerPos(playerPos+mapSizeX);
		}	
		if (currentScreenRow+1+cameraOffY < mapSizeY){
			updateScreen(centerScreenPoint+mapSizeX);	
		}			
		drawMap();
	}
	else if (ch=='a'){		
		if(playerPos > (currentPlayerRow*mapSizeX)){
			updatePlayerPos(playerPos-1); 
		}
		if(centerScreenPoint-cameraOffX > (currentScreenRow*mapSizeX)){
			updateScreen(centerScreenPoint-1);
		}
		drawMap();
	}
	else if (ch=='d'){		
		if(playerPos < ((currentPlayerRow*mapSizeX) + mapSizeX - 1)){	
			updatePlayerPos(playerPos+1); 
		}		
		if(centerScreenPoint+cameraOffX < ((currentScreenRow*mapSizeX) + mapSizeX - 1)){
			updateScreen(centerScreenPoint+1);				
		}
		drawMap();
	} 
		
		
	else if (ch == 't'){
		updateScreen(centerScreenPoint-mapSizeX); drawMap();}
	else if (ch == 'g'){	 			
		updateScreen(centerScreenPoint+mapSizeX); drawMap();}	
	else if (ch == 'f'){
		updateScreen(centerScreenPoint-1); 				drawMap();}	
	else if (ch == 'h'){	 																														
		updateScreen(centerScreenPoint+1); 				drawMap();}
}


void gameLoop()
{
	while(true)
	{
		playerMov();
		Sleep(10);
	}	
}

int main() 
{
	createMap();
	updatePlayerPos(playerPos);
	updateScreen(centerScreenPoint);
	drawMap();
	
	gameLoop();	

	return 0;
}
