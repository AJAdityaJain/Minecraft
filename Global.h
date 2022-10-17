#ifndef GLOBAL
#define GLOBAL

#include <string>

enum BLOCK {
	AIR,
	GRASS,
	DIRT,
	STONE,
	BEDROCK,
	LOG,
	LEAVES,
	FLOWER_LEAVES,
	CROSS_GRASS,
	DeleteCase1,
	ROSE
};

struct Settings_Graphics {
	float FOV = 70.0f;
	int Render_Distance = 1;
};

struct Settings_Controls {
	float Mouse_Sensitivity = 0.7f;
};

static Settings_Graphics Graphics;
static Settings_Controls Controls;

static const char* TEXTURES = "000000110411444444222222333333::;;::======<<<<<<CCCCCC------DDDDDD";

static const int width = 1920;
static const int height = 1000;
static const float aspect = 1.92f;


static int Size_Block = 8;
static int Current_Block = 1;

#endif // !UNIVERSAL_VARIABLES