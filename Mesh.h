#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <vector>
#include "VAO.h"
#include "EBO.h"


enum FACES {
	BACK,
	FRONT,
	WEST,
	EAST,
	BOTTOM,
	TOP
};

//const char GRASS_TOP = 0;
//const char GRASS_SIDE = 1;
//const char STONE = 2;
//const char BEDROCK = 3;
//const char DIRT = 4;
//const char ANDESITE = 5;
//const char DIORITE = 6;
//const char GRANITE = 7;
//const char GRASS = 8;
//const char SAND = 9;

//enum TEXTURES {
//	GRASS_TOP = 0,
//	GRASS_SIDE = 1,
//	STONE = 2,
//	BEDROCK = 3,
//	DIRT = 4,
//	ANDESITE = 5,
//	DIORITE = 6,
//	GRANITE = 7,
//	GRASS = 8,
//	SAND = 9
//};

class Mesh
{
public:
	std::vector <Vert> Vertex;
	std::vector <GLuint> Index;
	
	Mesh();

	void AddV(GLfloat x, GLfloat y, GLfloat z, GLfloat tx, GLfloat ty);
	void AddI(GLuint I);
	void AddFace(FACES face, GLfloat a, GLfloat b, GLfloat c, int tex);
	void Clear();

	//Mesh(std::vector <GLfloat>& V, std::vector <GLuint>& I);

};
#endif