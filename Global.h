#ifndef GLOBAL
#define GLOBAL


enum BLOCK {
	AIR,
	GRASS,
	DIRT,
	STONE,
	BEDROCK,
};

struct Settings_Graphics {
	float FOV = 70.0f;
};

struct Settings_Controls {
	float Mouse_Sensitivity = 0.7f;
};

static Settings_Graphics Graphics;
static Settings_Controls Controls;

static const char* TEXTURES = "000000110411444444222222333333";

static const int width = 1920;
static const int height = 1000;
static const float aspect = 1.92f;

#endif // !UNIVERSAL_VARIABLES