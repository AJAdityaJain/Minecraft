#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string getfilecontents(const char* filename);

class Shader {
	public:
		GLuint ID;

		Shader(const char* vertexSrc, const char* fragmentSrc);

		void Activate();
		void Delete();

	private:
		void compileErrors(unsigned int shader, const char* type);
	
};

#endif