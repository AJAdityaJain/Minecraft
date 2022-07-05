#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Entity.h"
#include"Main.h"
#include"shaderClass.h"
#include"Global.h"

class Camera
{
public:


	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.1f, -0.9f, 0.0f);


	
	Camera(float x, float y, float z);

	void ProjMatrix();
	void CMatrix(glm::vec3 p,  glm::vec3 co);
	void Matrix(glm::vec3 xyz, float rx, float ry, Shader& shader);
	void Matrix(Shader& shader);

private:

	glm::vec3 CamOri = glm::vec3(0, 0, 0);

	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 trans;
};
#endif