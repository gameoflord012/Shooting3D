#pragma once
# define M_PI           3.14159265358979323846

/*Unit mili_sec*/
double CLOCKS_PER_UPDATE = 10. * (CLOCKS_PER_SEC / 100.);

const wchar_t WALL = L'#';
const wchar_t SPACE = L' ';
const wchar_t PLAYER = L'X';
const wchar_t CORNER = L' ';

//const int screenWidth = 152;
const int screenWidth = 120;
const int screenHeight = 32;
wchar_t* screen = new wchar_t[screenWidth * screenHeight];

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

HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

wstring map = []() -> wstring {
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

vector<short> wallShadow = { 0x2591, 0x2592, 0x2593, 0x2588 };
vector<short> floorShadow = { ' ', '.', '-', '=', 'm', '#' };