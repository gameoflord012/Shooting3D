#pragma once
# define M_PI           3.14159265358979323846

/*Unit mili_sec*/
double CLOCKS_PER_UPDATE = 10. * (CLOCKS_PER_SEC / 100.);

const olc::Pixel WALL = olc::BLUE;
const olc::Pixel SPACE = olc::BLACK;
const olc::Pixel CORNER = SPACE;

const olc::Pixel DEBUG_PLAYER = olc::GREEN;
const olc::Pixel DEBUG_WALL = olc::RED;
const olc::Pixel DEBUG_SPACE = olc::VERY_DARK_BLUE;
const olc::Pixel DEBUG_VISION = olc::YELLOW;

const wchar_t WALL_CHAR = L'#';
const wchar_t SPACE_CHAR = L'.';

//const int screenWidth = 152;
const int screenWidth = 320;
const int screenHeight = 240;

const int mapWidth = 16;
const int mapHeight = 16;

const double playerView = M_PI / 4.;
const double playerSpeedInSec = 2.;
const double playerSpeedInMS = playerSpeedInSec * 100.;
const double playerViewSpeedInSec = M_PI / 3.;
const double playerVisionDistance = 16;
double playerAng = M_PI / 2;
double playerX = (double) mapWidth / 2., playerY = (double) mapHeight / 2.;

double deltaTime = 0;
double deltaTimeInSec = 0;
double deltaTimeInMS = 0;

const double viewUnit = 0.05;
const int vewDistance = 320;

const double aceptedCornerDistance = 0.05;

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

/*DARKER*/
vector<olc::Pixel> createShader(olc::Pixel cor, int size, double factor, bool isDarker = true) {
	vector<olc::Pixel> res;
	while (size--) {
		res.push_back(cor);
		cor.r *= (1 - factor);
		cor.g *= (1 - factor);
		cor.b *= (1 - factor);
	}
	if (not isDarker) reverse(res.begin(), res.end());
	return res;
}

vector<olc::Pixel> wallShadow = createShader(olc::BLUE, 50, 0.05, 0);
vector<olc::Pixel> floorShadow = createShader(olc::GREEN, 50, 0.05, 0);