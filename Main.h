#ifndef MAIN
#define MAIN

#include<iostream>
#include"Mesh.h"
#include"Texture.h"
#include"ShaderClass.h"
#include"Camera.h"

#include "libraries/include/GLFW/glfw3.h"
#include "libraries/include/glad/glad.h"

static const glm::vec3 X = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 Y = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 Z = glm::vec3(0.0f, 0.0f, 1.0f);

static const glm::vec3 Vec30 = glm::vec3(0, 0, 0);
static const glm::vec3 Vec35 = glm::vec3(0.5f, 0.5f, 0.5f);

int Get(int x, int y, int z);
void Set(int w, int x, int y, int z);
void Remesh();

int main();

#endif // !MAIN