// Shooting3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <time.h> 
#include <Windows.h>
using namespace std;

#include "Vars.h"

template <typename T> 
bool InBound(T a, T b, T c) { return (a) <= (b) and (b) <= (c); }

void inputHandler() {
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
		playerX -= playerSpeedInSec * deltaTimeInSec;
	}
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
		playerX += playerSpeedInSec * deltaTimeInSec;
	}
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
		playerY -= playerSpeedInSec * deltaTimeInSec;
	}
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
		playerY += playerSpeedInSec * deltaTimeInSec;
	}
}

void update() {
	for (int x = 0; x < screenWidth; x++) {
		double curAng = playerAng - playerView / 2. + 
						(double)x * (playerView / (double)screenWidth);

		double moveX = cos(curAng);
		double moveY = sin(curAng);

		double curX = playerX, curY = playerY;
		int dis = 0;
		while (InBound(0., curX, (double) (mapWidth - 1)) and 
			   InBound(0., curY, (double) (mapHeight - 1))) {

			if (map[(int)curX + (int)curY * mapWidth] == WALL) break;
			curX += moveX * viewUnit;
			curY += moveY * viewUnit;
			dis++;
		}		
		
		int wallHeight = screenHeight * 2. - (screenHeight / (double) dis);
		cout << wallHeight << ' ';
		/*for (int y = -wallHeight / 2; y <= wallHeight / 2; y++) {
			screen[x + (screenHeight / 2 + y) * screenWidth] = WALL;
		}*/
	}		
	cout << endl;
}

void render() {
	DWORD dwBytesWritten = 0;
	WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
}

int main()
{
	for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = SPACE;	
	//SetConsoleActiveScreenBuffer(hConsole);	

	double previous = clock();
	double lag = 0.0;	
	while (true) 
	{		
		inputHandler();

		double current = clock();
		deltaTime = current - previous;
		deltaTimeInSec = deltaTime / CLOCKS_PER_SEC;
		deltaTimeInMS = deltaTimeInSec * 100;
		previous = current;
		lag += deltaTime;

		while (lag >= CLOCKS_PER_UPDATE)
		{
			update();
			lag -= CLOCKS_PER_UPDATE;
		}

		//render();
	}   
	system("pause");
}

