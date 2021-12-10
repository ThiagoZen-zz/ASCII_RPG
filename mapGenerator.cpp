#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

vector<char> map;

int mapSizeX,mapSizeY;
int mapSize;

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

void setupVar()
{
	mapSizeX = 55;
	mapSizeY = 25;
	mapSize = mapSizeX * mapSizeY;
}

void genCustomMap()
{	
  for(int i=0; i < mapSize; i++)
	{
		map.push_back('.');
	}
}

void drawObj(int startPos,void *arr, int y,int x)
{
	char (*obj)[y][x] = (char (*)[y][x]) arr;
	
	int arrayRow = y;
	int arrayCol = x;
		
	int objPos = startPos;
	for(int i=0;i < arrayRow; i++)
	{
		for(int x=0; x < arrayCol; x++)
			map[objPos + x] = (*obj)[i][x];
		objPos += mapSizeX;
	}	
}

void writeOnFile()
{
	ofstream myfile;
  myfile.open ("map.txt");
  for(int i=0; i < mapSize; i++)
	{
		myfile << map[i];
	}
  myfile.close();
}

int main() {
	setupVar();
  genCustomMap();  
  //Tree
  drawObj(1124,tree,5,8);
  drawObj(76,tree,5,8);
  drawObj(558,tree,5,8);
  //House
  drawObj(695,house,4,11);
  drawObj(94,house,4,11);
  
  writeOnFile();
  
	cout << "Done!" << endl;
  return 0;
}
