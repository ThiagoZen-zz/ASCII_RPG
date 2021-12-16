#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <math.h>

using namespace std;

#include "inventory.h"

char player = 'C';
char blankSpace = '.';
char currentBeneathBlock = ' ';

vector<char> map;
int mapSizeX=55,mapSizeY=25;
int mapSize;

vector<char> store;
int storeSizeX = 35,storeSizeY = 15;
int storeSize;

int scenarioX,scenarioY;
int scenarioSize;

int screenSizeX = 35,screenSizeY=15;

int startCameraOffX = screenSizeX/2, startCameraOffY = screenSizeY/2;
int cameraOffX = startCameraOffX, cameraOffY = startCameraOffY;

int centerScreenPoint;
int playerPos;

int currentPlayerRow;
int currentPlayerColumn;
int currentScreenRow;
int currentScreenColumn;

bool currentScenario;

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

void genStore(){
	for(int i=0; i < storeSizeY; i++)
	{
		for(int x=0; x < storeSizeX; x++)
		{
			if(i == 0 || x == 0 || x == storeSizeX-1)
				store.push_back('+');
			else if(i == storeSizeY-1){
				if(x == 5|| x == 6 || x == 7)
					store.push_back('-');
				else
					store.push_back('+');
			}
			else
				store.push_back('.');
		}
	}
}

void drawScenario(vector<char> customVec){
	int centerDiagonalLeft = centerScreenPoint - (scenarioX * cameraOffY) - cameraOffX;
	int currentRow = 0;
	for(int y=0;y < screenSizeY; y++)
	{ 		
		for(int x = centerDiagonalLeft + currentRow; x < centerDiagonalLeft + screenSizeX + currentRow; x++)
		{
			cout << customVec[x];
		}
		cout << "\n";
		currentRow += scenarioX;
	}
}

void debugInfo()
{
	cout << "Player Position: " << playerPos << endl;	
	cout << "Center Screen Point: " << centerScreenPoint << endl;			
	cout << endl;
	//cout << "Map Limit Horizontal: " << mapSizeX << endl;
	//cout << "Map Limit Vertical: " << mapSizeY << endl;
	cout << "Map Limit Horizontal: " << scenarioX << endl;
	cout << "Map Limit Vertical: " << scenarioY << endl;
	cout << endl;
	//cout << "Player Current Row: " << currentPlayerRow << endl;
	//cout << "Player Current Column: " << currentPlayerColumn << endl;
	//cout << "Screen Current Row: " << currentScreenRow << endl;
	//cout << "Screen Current Column: " << currentScreenColumn << endl;
	cout << endl;
	cout << "current Scenario: " << currentScenario << endl;
}

void setupCurrentScenarioSize(){
	if(currentScenario == 0){
		scenarioX = mapSizeX;
		scenarioY = mapSizeY;
	}else{
		scenarioX = storeSizeX;
		scenarioY = storeSizeY;
	}
	scenarioSize = scenarioX * scenarioY;
}

void drawScreen()
{
	system("cls");									// Erasing the screen
	setupCurrentScenarioSize();
	if(currentScenario == 0){
		drawScenario(map);
	}
	else{
		drawScenario(store);
	}
	
	drawInventory(inventory,4,35); 	// Drawing the inventory at the bottom of the screen
	
	//debugInfo(); 										// Printing the Debug Info
}

void updatePlayerPos(int newPos)
{
	char nextBlock;
	if(currentScenario == 0)
		nextBlock = map[newPos];
	else
		nextBlock = store[newPos];
		
	if(nextBlock == blankSpace){ 		//Detecting collision with other objects
		if(currentScenario == 0){
			map[playerPos] = currentBeneathBlock;
			map[newPos] = player;
		}else{
			store[playerPos] = currentBeneathBlock;
			store[newPos] = player;
		}
			
		playerPos = newPos;
		currentPlayerRow = playerPos / scenarioX;
		currentPlayerColumn = playerPos - currentPlayerRow * scenarioX;
		
		currentBeneathBlock = nextBlock;
	}
}

void updateScreen(int newPos)
{
	centerScreenPoint = newPos;
	currentScreenRow = centerScreenPoint / scenarioX;
	currentScreenColumn = centerScreenPoint - currentScreenRow * scenarioX;
}

void removePlayerFromScenario(){
	if(currentScenario != 0){
		map[playerPos] = currentBeneathBlock;
	}else{
		store[playerPos] = currentBeneathBlock;
	}
}

void setupInitialVal(){
	setupCurrentScenarioSize();
	
	centerScreenPoint = scenarioSize/2;
	playerPos = scenarioSize/2;
	
	updatePlayerPos(playerPos);				// Giving the player an initial position
	updateScreen(centerScreenPoint);	// Giving the Screen an initial position
}

void changeScenario(){
	currentScenario = !currentScenario;
	removePlayerFromScenario();
	setupInitialVal();
}

void playerMov()
{
	char ch;

	ch = getch();
	
	if	(ch=='h'){	
		changeScenario();
		drawScreen();
	}	
	
	if	    (ch=='w'){	
		if(currentPlayerRow > 0){
			updatePlayerPos(playerPos-scenarioX);
		}	
		
		if((currentScreenRow > cameraOffY) && (currentPlayerRow < currentScreenRow))
		{
			updateScreen(centerScreenPoint-scenarioX);	
		}
		drawScreen();
	}	
	else if (ch=='s'){		
		if((currentPlayerRow+1) < scenarioY){
			updatePlayerPos(playerPos+scenarioX);
		}	
		
		if ((currentScreenRow+1+cameraOffY < scenarioY) && (currentPlayerRow > currentScreenRow)){
			updateScreen(centerScreenPoint+scenarioX);	
		}
		drawScreen();
	}
	else if (ch=='a'){		
		if(currentPlayerColumn > 0){
			updatePlayerPos(playerPos-1); 
		}
		if((centerScreenPoint-cameraOffX > currentScreenRow*scenarioX) && (currentPlayerColumn < currentScreenColumn)){
			updateScreen(centerScreenPoint-1);
		}
		drawScreen();
	}
	else if (ch=='d'){		
		if(currentPlayerColumn+1 < scenarioX){	
			updatePlayerPos(playerPos+1); 
		}		
		if((centerScreenPoint+cameraOffX < (currentScreenRow*scenarioX) + scenarioX - 1) && (currentPlayerColumn > currentScreenColumn) ){
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
	// Generating/Reading Scenario Informations
	readMap();
	genStore();
	
	// Setup the size of the scenarios
	mapSize = map.size();
	storeSize = storeSizeX * storeSizeY;
	
	// Setup the first variables
	setupInitialVal();	
		
	drawScreen();											// Drawing the initial objects to the screen
	
	gameLoop();												// Game loop (Controls all actions sent by a predetermined time)

	return 0;
}
