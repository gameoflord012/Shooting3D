#pragma once
# define M_PI           3.14159265358979323846

/*Unit mili_sec*/
double CLOCKS_PER_UPDATE = 10. * (CLOCKS_PER_SEC / 100.);

const wchar_t WALL = L'#';
const wchar_t SPACE = L' ';
const wchar_t PLAYER = L'X';
const wchar_t CORNER = L' ';

//const int screenWidth = 152;
const int screenWidth = 320;
const int screenHeight = 240;

const int mapWidth = 16;
const int mapHeight = 16;

const double playerView = M_PI / 4.;
const double playerSpeedInSec = 2.;
const double playerSpeedInMS = playerSpeedInSec * 100.;
const double playerViewSpeedInSec = M_PI / 4.;
const double playerVisionDistance = 16;
double playerAng = M_PI / 2;
double playerX = (double) mapWidth / 2., playerY = (double) mapHeight / 2.;

double deltaTime = 0;
double deltaTimeInSec = 0;
double deltaTimeInMS = 0;

const double viewUnit = 0.1;
const int vewDistance = 160;

const double aceptedCornerDistance = 0.1;

wstring world = []() -> wstring {
	return
		wstring(L"################") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#....#.........#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#..............#") +
		wstring(L"#.....##########") +
		wstring(L"#..............#") +
		wstring(L"################");
} ();


/*Farset to closest*/
vector<olc::Pixel> wallShadow = { olc::BLACK, olc::VERY_DARK_GREY, olc::DARK_GREY,  olc::GREY };
vector<olc::Pixel> floorShadow = { olc::VERY_DARK_BLUE, olc::DARK_BLUE, olc::BLUE };