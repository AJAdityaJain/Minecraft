#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "VAO.h"
#include "Mesh.h"

class Renderer {
public:
	VAO vao;
	
	Renderer();
	void Delete();
	void Bind();
	void Bind(Mesh mesh);
	void Render(GLsizei mesh);
};

#endif