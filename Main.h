#ifndef MAIN
#define MAIN

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Mesh.h"
#include"Renderer.h"
#include"World.h"
#include"Texture.h"
#include"ShaderClass.h"
#include"Camera.h"

const glm::vec3 X = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Y = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Z = glm::vec3(0.0f, 0.0f, 1.0f);

static const glm::vec3 Vec30 = glm::vec3(0, 0, 0);
static const glm::vec3 VecY = glm::vec3(0.5f, 0, 0.5f);
static const glm::vec3 VecX = glm::vec3(0, 0.5f, 0.5f);

int GetBlock(int x, int y, int z);

#endif // !MAIN