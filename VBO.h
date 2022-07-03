#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<vector>
#include<glad/glad.h>

struct Vert {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat u;
	GLfloat v;
};

class VBO {
	public:
		GLuint ID;

		VBO(std::vector<Vert>& vertices);

		void Bind();
		void Unbind();
		void Delete();
};

#endif // !VBO_CLASS_H