#include"Camera.h"

Camera::Camera(float x, float y, float z) {

	Position = glm::vec3(x, y, z);
	view = glm::mat4(1.0f); proj = glm::mat4(1.0f); trans = glm::mat4(1.0f);
}

void Camera::Matrix(glm::vec3 xyz, float rx, float ry, Shader& shader)
{
	view = glm::mat4(1.0f);
	trans = view;
	proj = view;
	
	proj = glm::perspective(glm::radians(FOV), MAIN::aspect, 0.01f, 100.0f);

	view = glm::lookAt(Position, Position + Orientation, Y);
	
	trans = glm::translate(trans, xyz+VecY);
	trans = glm::rotate(trans, 3.1416f * ry, Y);
	trans = glm::translate(trans, VecX-VecY);
	trans = glm::rotate(trans, 3.1416f * rx, X);
	trans = glm::translate(trans, -VecX);

	
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj*view * trans));
}

void Camera::Matrix(Shader& shader)
{
	view = glm::mat4(1.0f);
	proj = view;

	view = glm::lookAt(Position, Position + Orientation, Y);

	proj = glm::perspective(glm::radians(FOV), MAIN::aspect, 0.01f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj * view));
}