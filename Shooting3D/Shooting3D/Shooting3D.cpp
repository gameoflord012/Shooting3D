// Shooting3D.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <time.h> 
#include <assert.h>
#include <vector>

using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Vars.h"



template <typename T> 
bool InBound(T a, T b, T c) { return (a) <= (b) and (b) <= (c); }

bool movableSpace(double x, double y) {
	return InBound<double>(0, x, mapWidth - 1) and InBound<double>(0, y, mapHeight - 1) and
		world[(int)(x)+(int)(y)* mapWidth] != WALL_CHAR;
}

class Shooting3D : public olc::PixelGameEngine {
public:
	void debug()
	{
		//swprintf_s(screen, screenWidth - 1, L"%3.2lf %3.2lf %3.2lf", playerX, playerY, playerAng);
		for (int x = 0; x < mapWidth; x++)
			for (int y = 0; y < mapHeight; y++) {
				//screen[x + (y + 1) * screenWidth] = world[x + y * mapWidth];
				Draw(x, y + 1, world[x + y * mapWidth] == SPACE_CHAR ? DEBUG_SPACE : DEBUG_WALL);
			}

		//screen[(int)(playerX) + ((int)(playerY) + 1) * screenWidth] = PLAYER;
		Draw((int)(playerX), (int)(playerY)+1, DEBUG_PLAYER);

		int moveX = (int)round(cos(playerAng));
		int moveY = (int)round(-sin(playerAng));
		//screen[(int)((int)(playerX + (double)moveX) + ((int)(playerY + (double)moveY) + 1) * screenWidth)] = L'*';
		Draw((int)(playerX + (double)moveX), (int)(playerY + (double)moveY) + 1, DEBUG_VISION);
	}

	void inputHandler() {
		auto fixAng = [&]() {
			if (playerAng >= 2 * M_PI) playerAng -= (int)(playerAng / (2. * M_PI)) * 2. * M_PI;
			if (playerAng <= -2 * M_PI) playerAng += (int)(-playerAng / (2. * M_PI)) * 2. * M_PI;
		};


		double moveX = cos(playerAng) * playerSpeedInSec * deltaTimeInSec;
		double moveY = -sin(playerAng) * playerSpeedInSec * deltaTimeInSec;
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
			if (movableSpace(playerX + moveY, playerY - moveX)) {
				playerX += moveY;
				playerY -= moveX;
			}
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
			if (movableSpace(playerX - moveY, playerY + moveX)) {
				playerX -= moveY;
				playerY += moveX;
			}
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			if (movableSpace(playerX + moveX, playerY + moveY)) {
				playerX += moveX;
				playerY += moveY;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			if (movableSpace(playerX - moveX, playerY - moveY)) {
				playerX -= moveX;
				playerY -= moveY;
			}
		}
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) {
			playerAng += playerViewSpeedInSec * deltaTimeInSec;
			fixAng();
		}
		if (GetAsyncKeyState((unsigned short)'E') & 0x8000) {
			playerAng -= playerViewSpeedInSec * deltaTimeInSec;
			fixAng();
		}
	}

	void update() {
		for (int x = 0; x < screenWidth; x++) {
			double curAng = playerAng + playerView / 2. -
				(double)x * (playerView / (double)screenWidth);

			double moveX = cos(curAng);
			double moveY = -sin(curAng);

			int dis = 0;
			double curX, curY;
			for (dis = 1; dis <= vewDistance; dis++) {
				curX = (double)playerX + (double)dis * viewUnit * moveX,
					curY = (double)playerY + (double)dis * viewUnit * moveY;

				assert(InBound<int>(0, curX, mapWidth - 1));
				assert(InBound<int>(0, curY, mapHeight - 1));
				if (not movableSpace(curX, curY)) break;
			}

			int nearestCornerX = round(curX);
			int nearestCornerY = round(curY);

			double deltaX = curX - (double)nearestCornerX;
			double deltaY = curY - (double)nearestCornerY;
			double disToCorner = sqrt(deltaX * deltaX + deltaY * deltaY);

			bool isCorner = disToCorner <= aceptedCornerDistance;

			double perCent = 1. - (double)dis / vewDistance;
			int wallHeight = (double)screenHeight * perCent;
			/*Wall shading*/
			for (int y = 0; y < wallHeight; y++) {
				int idx = (int)((double)(wallShadow.size() - 1) * perCent);
				assert(InBound<int>(0, idx, wallShadow.size() - 1));
				/*screen[x + ((screenHeight - wallHeight) / 2 + y) * screenWidth] =
					isCorner ? CORNER : wallShadow[idx];*/
				Draw(x, (screenHeight - wallHeight) / 2 + y, isCorner ? CORNER : wallShadow[idx]);
			}
			/*Up floor*/
			//for (int y = 0; y < (screenHeight - wallHeight) / 2; y++) {}

			/*Bottom floor*/
			int beginY = (screenHeight - wallHeight) / 2 + wallHeight;
			for (int y = beginY; y < screenHeight; y++) {
				//screen[x + y * screenWidth] = L'#';
				//game.draw(x, y, L'#');

				int dis = screenHeight - y - 1;
				double floorPercent = 1 - dis / (double)(screenHeight / 2);

				int idx = (int)((double)(floorShadow.size() - 1) * floorPercent);
				assert(InBound<int>(0, idx, floorShadow.size() - 1));
				//screen[x + y * screenWidth] = floorShadow[idx];
				Draw(x, y, floorShadow[idx]);
			}
		}
	}

	bool OnUserCreate() override {
		sAppName = "Upgraded 3D Shooting";
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		inputHandler();
		deltaTime = fElapsedTime;
		deltaTimeInSec = deltaTime;
		deltaTimeInMS = deltaTimeInSec * 100;

		for (int i = 0; i < screenWidth * screenHeight; i++) 
			Draw(i % screenWidth, i / screenWidth, SPACE);
		update();
		debug();
		//Draw( screenWidth / 2, screenHeight / 2, olc::WHITE);

		return true;
	}
};


int main()
{	
	Shooting3D game;	
	if(game.Construct(screenWidth, screenHeight, 4, 4))
		game.Start();
}

