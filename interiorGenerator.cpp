#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <fstream>
#include <math.h>

using namespace std;

vector<char> store;

int screenSizeX = 35,screenSizeY=15;

int storeSizeX = 35,storeSizeY = 15;
int storeSize = storeSizeX * storeSizeY;

int startCameraOffX = screenSizeX/2, startCameraOffY = screenSizeY/2;
int cameraOffX = startCameraOffX, cameraOffY = startCameraOffY;

int centerScreenPoint;

vector<char> map;

int mapSizeX=55,mapSizeY=25;
int mapSize;

bool changeMap = 0;

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

void updatePositions(int sizeX,int sizeY){
	centerScreenPoint = (sizeX*sizeY)/2;
}

void drawMapView(vector<char> customVec,int sizeX,int sizeY){
	system("cls");
	
	centerScreenPoint = (sizeX*sizeY)/2;
	
	int centerDiagonalLeft = centerScreenPoint - (sizeX * cameraOffY) - cameraOffX;
	int currentRow = 0;
	for(int y=0;y < screenSizeY; y++)
	{ 		
		for(int x = centerDiagonalLeft + currentRow; x < centerDiagonalLeft + screenSizeX + currentRow; x++)
		{
			cout << customVec[x];
		}
		cout << "\n";
		currentRow += sizeX;
	}
}

void verify(){
	char ch;

	ch = getch();
	
	if	(ch=='h'){	
		if(!changeMap){
			drawMapView(store, storeSizeX, storeSizeY);
		}
		else{
			drawMapView(map, mapSizeX, mapSizeY);
		}
		changeMap = !changeMap;
	}	
}

void gameLoop()
{
	while(true)
	{
		verify();
		cout << "Map Id: " << changeMap << endl;
		cout << "Center Screen Position: " << centerScreenPoint << endl;
		Sleep(50);
	}	
}

int main()
{	
	readMap();
  genStore();
    
  drawMapView(map, mapSizeX, mapSizeY);
  updatePositions(mapSizeX,mapSizeY);
	 
  gameLoop();
}
