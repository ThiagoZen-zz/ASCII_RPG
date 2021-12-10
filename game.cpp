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
int currentPlayerColumn;
int currentScreenRow;
int currentScreenColumn;

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
	cout << "Center Screen Point: " << centerScreenPoint << endl;	
	cout << "Block beneath: " << currentBeneathBlock << endl;		
	cout << endl;
	cout << "Map Limit Horizontal: " << mapSizeX << endl;
	cout << "Map Limit Vertical: " << mapSizeY << endl;
	cout << endl;
	cout << "Player Current Row: " << currentPlayerRow << endl;
	cout << "Player Current Column: " << currentPlayerColumn << endl;
	cout << "Screen Current Row: " << currentScreenRow << endl;
	cout << "Screen Current Column: " << currentScreenColumn << endl;
}

void drawScreen()
{
	system("cls");									// Erasing the screen
	
	drawMapView(); 									// Drawing the map according to the screen size
	drawInventory(inventory,4,35); 	// Drawing the inventory at the bottom of the screen
	
	//debugInfo(); 									// Printing the Debug Info
}

void updatePlayerPos(int newPos)
{
	char nextBlock = map[newPos];
	if(nextBlock == blankSpace){ 		//Detecting collision with other objects
		map[playerPos] = currentBeneathBlock;
		map[newPos] = player;
				
		playerPos = newPos;
		currentPlayerRow = playerPos / mapSizeX;
		currentPlayerColumn = playerPos - currentPlayerRow * mapSizeX;
		
		currentBeneathBlock = nextBlock;
	}
}

void updateScreen(int newPos)
{
	centerScreenPoint = newPos;
	currentScreenRow = centerScreenPoint / mapSizeX;
	currentScreenColumn = centerScreenPoint - currentScreenRow * mapSizeX;
}

void playerMov()
{
	char ch;

	ch = getch();
	if	    (ch=='w'){	
		if(currentPlayerRow > 0){
			updatePlayerPos(playerPos-mapSizeX);
		}	
		
		if((currentScreenRow > cameraOffY) && (currentPlayerRow < currentScreenRow))
		{
			updateScreen(centerScreenPoint-mapSizeX);	
		}
		drawScreen();
	}	
	else if (ch=='s'){		
		if((currentPlayerRow+1) < mapSizeY){
			updatePlayerPos(playerPos+mapSizeX);
		}	
		
		if ((currentScreenRow+1+cameraOffY < mapSizeY) && (currentPlayerRow > currentScreenRow)){
			updateScreen(centerScreenPoint+mapSizeX);	
		}
		drawScreen();
	}
	else if (ch=='a'){		
		if(currentPlayerColumn > 0){
			updatePlayerPos(playerPos-1); 
		}
		if((centerScreenPoint-cameraOffX > currentScreenRow*mapSizeX) && (currentPlayerColumn < currentScreenColumn)){
			updateScreen(centerScreenPoint-1);
		}
		drawScreen();
	}
	else if (ch=='d'){		
		if(currentPlayerColumn+1 < mapSizeX){	
			updatePlayerPos(playerPos+1); 
		}		
		if((centerScreenPoint+cameraOffX < (currentScreenRow*mapSizeX) + mapSizeX - 1) && (currentPlayerColumn > currentScreenColumn) ){
			updateScreen(centerScreenPoint+1);				
		}
		drawScreen();
	} 

}

void gameLoop()
{
	while(true)
	{
		playerMov();										// Identifies the player's movement
		Sleep(50);											// Giving some delay
	}	
}

int main() 
{
	readMap();												// Reading the map from a file
	setupInitialVar();								// Initializing variables according to the environment values
		
	updatePlayerPos(playerPos);				// Giving the player an initial position
	updateScreen(centerScreenPoint);	// Giving the Screen an initial position
		
	drawScreen();											// Drawing the initial objects to the screen
	
	gameLoop();												// Game loop (Controls all actions sent by a predetermined time)

	return 0;
}
