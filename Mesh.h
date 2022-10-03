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