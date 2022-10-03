#include"Camera.h"
#include "libraries/include/glm/ext/matrix_float4x4.hpp"
#include "libraries/include/glm/ext/matrix_transform.hpp"
#include "libraries/include/glm/gtc/type_ptr.hpp"

Camera::Camera(float x, float y, float z) {

	Position = glm::vec3(x, y, z);
	view = glm::mat4(1.0f); proj = glm::mat4(1.0f); trans = glm::mat4(1.0f);
}

void Camera::ProjMatrix() {
	proj = glm::perspective(glm::radians(Graphics.FOV), MAIN::aspect, 0.01f, 100.0f);
}

void Camera::CMatrix(glm::vec3 p, glm::vec3 co){
	Position = p + Vec35;
	CamOri = co;
}

void Camera::Matrix(glm::vec3 xyz, float rx, float ry, Shader& shader)
{
	view = glm::mat4(1.0f);
	trans = view;
	
	view = glm::lookAt(Position, Position + CamOri, Y);
	
	trans = glm::translate(trans, xyz);
	trans = glm::rotate(trans, 3.1416f * ry, Y);
	trans = glm::rotate(trans, 3.1416f * rx, X);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj*view * trans));
}

void Camera::Matrix(Shader& shader)
{
	view = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + CamOri, Y);

	
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj * view));
}