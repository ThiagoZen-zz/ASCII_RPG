#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <math.h>

using namespace std;

char player = 'C';
char blankSpace = '.';
char currentBeneathBlock = ' ';

vector<char> map;

int mapSizeX=55,mapSizeY=25;
int mapSize;

int screenSizeX = 35,screenSizeY=15;

int startCameraOffX = screenSizeX/2, startCameraOffY = screenSizeY/2;
int cameraOffX = startCameraOffX, cameraOffY = startCameraOffY;

int centerScreenPoint;
int playerPos;

int currentPlayerRow;
int currentScreenRow;

char inventory[4][35]{
	{'.','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','.'},
	{'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
	{'|',' ','P','L','A','C','E','H','O','L','D','E','R',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
	{'.','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','.'}
};

void readMap(){
	ifstream mapFile( "map.txt" );
  
  for(string line; getline( mapFile, line ); )
	{
		for(int i = 0; i < line.size(); i++)
		{
			map.push_back(line[i]);
		} 		
	}
	
	mapFile.close();
}

void setupInitialVar(){
	mapSize = map.size();
	centerScreenPoint = mapSize/2;
	playerPos = mapSize/2;
}

void drawInventory(void *arr, int y,int x){
	char (*obj)[y][x] = (char (*)[y][x]) arr;
	
	int arrayRow = y;
	int arrayCol = x;
		
	for(int i=0;i < arrayRow; i++)
	{
		for(int x=0; x < arrayCol; x++)
			cout << (*obj)[i][x];
		cout << "\n";
	}
}

void drawMapView(){
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

void drawScreen()
{
	system("cls");
	
	drawMapView();
	drawInventory(inventory,4,35);
	
	//debugInfo();
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
		drawScreen();
	}	
	else if (ch=='s'){		
		if((currentPlayerRow+1) < mapSizeY){
			updatePlayerPos(playerPos+mapSizeX);
		}	
		if (currentScreenRow+1+cameraOffY < mapSizeY){
			updateScreen(centerScreenPoint+mapSizeX);	
		}			
		drawScreen();
	}
	else if (ch=='a'){		
		if(playerPos > (currentPlayerRow*mapSizeX)){
			updatePlayerPos(playerPos-1); 
		}
		if(centerScreenPoint-cameraOffX > (currentScreenRow*mapSizeX)){
			updateScreen(centerScreenPoint-1);
		}
		drawScreen();
	}
	else if (ch=='d'){		
		if(playerPos < ((currentPlayerRow*mapSizeX) + mapSizeX - 1)){	
			updatePlayerPos(playerPos+1); 
		}		
		if(centerScreenPoint+cameraOffX < ((currentScreenRow*mapSizeX) + mapSizeX - 1)){
			updateScreen(centerScreenPoint+1);				
		}
		drawScreen();
	} 
		
		
	else if (ch == 't'){
		updateScreen(centerScreenPoint-mapSizeX); drawScreen();}
	else if (ch == 'g'){	 			
		updateScreen(centerScreenPoint+mapSizeX); drawScreen();}	
	else if (ch == 'f'){
		updateScreen(centerScreenPoint-1); 				drawScreen();}	
	else if (ch == 'h'){	 																														
		updateScreen(centerScreenPoint+1); 				drawScreen();}
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
	readMap();
	setupInitialVar();
		
	updatePlayerPos(playerPos);
	updateScreen(centerScreenPoint);
		
	drawScreen();
	
	gameLoop();	

	return 0;
}
