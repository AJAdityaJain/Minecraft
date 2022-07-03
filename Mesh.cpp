#include"Mesh.h"

Mesh::Mesh() {
}

void Mesh::AddV(GLfloat x, GLfloat y, GLfloat z, GLfloat tx, GLfloat ty) {
	Vertex.push_back(Vert{x,y,z,tx,ty});
}
void Mesh::AddI(GLuint I) {
	Index.push_back(I);
}


void Mesh::AddFace(FACES face, GLfloat a, GLfloat b, GLfloat c, int tex){
	tex -= 48;
	GLfloat tx = (tex % 8) / 8.0f;
	GLfloat ty = floorf(tex / 8.0f) / 8.0f;
	GLfloat tx2 = ((tex % 8) / 8.0f)+0.125f;
	GLfloat ty2 =		(floorf(tex / 8.0f) / 8.0f)+0.125f;
	GLint size = Vertex.size();

	if (face == FRONT) {
		AddV(a, b, c+1, tx, ty);
		AddV(a +1, b, c+1, tx2, ty);
		AddV(a, b +1, c+1, tx, ty2);
		AddV(a +1, b +1, c+1, tx2, ty2);
	}
	if (face == BACK) {
		AddV(a, b, c+0, tx, ty);
		AddV(a +1, b, c+0, tx2, ty);
		AddV(a, b +1, c+0, tx, ty2);
		AddV(a +1, b +1, c+0, tx2, ty2);
	}
	if (face == EAST) {
		AddV(a+ 1, b  , c, tx, ty);
		AddV(a+ 1, b+1, c, tx, ty2);
		AddV(a+ 1, b,   c +1, tx2, ty);
		AddV(a+ 1, b +1,c +1, tx2, ty2);
	}
	if (face == WEST) {
		AddV(a + 0, b, c, tx, ty);
		AddV(a + 0, b + 1, c, tx, ty2);
		AddV(a + 0, b, c + 1, tx2, ty);
		AddV(a + 0, b + 1, c + 1, tx2, ty2);
	}
	if (face == TOP) {
		AddV(a, b + 1, c, tx, ty);
		AddV(a +1, b + 1, c, tx2, ty);
		AddV(a, b + 1, c +1, tx, ty2);
		AddV(a +1, b + 1, c +1, tx2, ty2);
	}
	if (face == BOTTOM) {
		AddV(a, b + 0, c, tx, ty);
		AddV(a + 1, b + 0, c, tx2, ty);
		AddV(a, b + 0, c + 1, tx, ty2);
		AddV(a + 1, b + 0, c + 1, tx2, ty2);
	}
	

	if (face == FRONT || face == EAST || face == BOTTOM) {

		AddI(size + 1); AddI(size + 0); AddI(size + 2);
		AddI(size + 1); AddI(size + 2); AddI(size + 3);
	}
	else{
		AddI(size + 0); AddI(size + 1); AddI(size + 2);
		AddI(size + 2); AddI(size + 1); AddI(size + 3);
	}

	tx = 0;
	ty = 0;
	tx2 = 0;
	ty2 = 0;
	size = 0;
}
void Mesh::Clear() {
	Mesh::Vertex.clear();
	Mesh::Index.clear();
}