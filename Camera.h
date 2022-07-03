#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Main.h"
#include"shaderClass.h"

class Camera
{
public:

	glm::vec3 Position;
	glm::vec3 Position2;
	glm::vec3 Size = glm::vec3(1, 1, 1);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation2 = glm::vec3(0.0f, -1.0f, -0.01f);
	glm::vec3 displacment = glm::vec3(0, 0, 0);

	glm::mat4 view;
	glm::mat4 proj ;
	glm::mat4 trans ;

	float speed = 0.01f;
	float sensitivity = 70.0f;

	double mouseX;
	double mouseY;


	Camera(int x, int y, int z);
	void Matrix(glm::vec3 xyz, float rx, float ry, Shader& shader);
	void Matrix(Shader& shader);
	
	bool isPointInsideAABB(int x, int y, int z);
	void Inputs(GLFWwindow* window);
};
#endif