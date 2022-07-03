#include"Camera.h"

void Clamp(float& intPtr, float clamp,int halt) {
	halt = halt == 0 ? -1 : 1;
	if (intPtr > clamp) {
		intPtr = halt*clamp;
	}
	if (intPtr < -clamp) {
		intPtr = -halt *clamp;
	}
}

Camera::Camera(int x, int y ,int z)
{
	Camera::mouseX = 0;
	Camera::mouseY = 0;
	Position = glm::vec3(0, 0, 0);
	Position2 = glm::vec3(x, y, z);
	view = glm::mat4(1.0f); proj = glm::mat4(1.0f); trans = glm::mat4(1.0f);
}

void Camera::Matrix(glm::vec3 xyz, float rx, float ry, Shader& shader)
{
	view = glm::mat4(1.0f);
	trans = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	
	proj = glm::perspective(glm::radians(70.0f), MAIN::aspect, 0.01f, 100.0f);

	view = glm::lookAt(Position2, Position2 + Orientation2, Y);

	
	
	trans = glm::translate(trans, xyz);
	
	trans = glm::translate(trans, VecY);
	trans = glm::rotate(trans, 3.1416f * ry, Y);
	trans = glm::translate(trans, VecX-VecY);
	trans = glm::rotate(trans, 3.1416f * rx, X);
	trans = glm::translate(trans, -VecX);

	
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj*view * trans));
}

void Camera::Matrix(Shader& shader)
{
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	view = glm::lookAt(Position2, Position2 + Orientation2, Y);

	proj = glm::perspective(glm::radians(70.0f), MAIN::aspect, 0.01f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(proj * view));
}

bool Camera::isPointInsideAABB(int x, int y ,int z) {
	return
		(x - 1 >= Position.x || x <= Position.x - Size.x)||
		(y - 1 >= Position.y || y <= Position.y - Size.y)||
		(z - 1 >= Position.z || z <= Position.z - Size.z);
}

void Camera::Inputs(GLFWwindow* window)
{
	displacment.x = 0;
	displacment.y = 0;
	displacment.z = 0;
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		displacment.z += cos(Orientation.y * 3.1416f) * speed;
		displacment.x += sin(Orientation.y * 3.1416f) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		displacment.z -= cos(Orientation.y * 3.1416f) * speed;
		displacment.x -= sin(Orientation.y * 3.1416f) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		displacment.z += cos((Orientation.y+0.5f) * 3.1416f) * speed;
		displacment.x += sin((Orientation.y+0.5f) * 3.1416f) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		displacment.z -= cos((Orientation.y + 0.5f) * 3.1416f) * speed;
		displacment.x -= sin((Orientation.y + 0.5f) * 3.1416f) * speed;
	}


	displacment.y = 0;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		displacment += speed * Y;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		displacment -= speed * Y;
	}

	Position += displacment;
	
	if (!isPointInsideAABB(1,0,1) ){
		Position -= displacment;
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}
	

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		int W = (MAIN::width / 2);
		int H = (MAIN::height / 2);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glfwGetCursorPos(window, &mouseX, &mouseY);

		mouseX = (mouseX - W) / 1000;
		mouseY = (mouseY - H) / 1000;

		//Orientation.x += mouseY;
		Orientation.y += mouseX;
		Clamp(Orientation.x, 0.4, true);
		Clamp(Orientation.y, 1 , false);
		if (mouseX!= 0||mouseY!=0) {
			std::cout << Orientation .x << " . " << Orientation.y << " . " << Orientation.z << std::endl;
		}
		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, W, H);
	} 
	else 
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}


/*
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		glfwGetCursorPos(window, &mouseX, &mouseY);

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-sensitivity * (float)(mouseY - (MAIN::height / 2)) / MAIN::height), glm::normalize(glm::cross(Orientation, Y)));

		if (abs(glm::angle(newOrientation, Y) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		Orientation = glm::rotate(Orientation, glm::radians(-sensitivity * (float)(mouseX - (MAIN::width / 2)) / MAIN::width), Y);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (MAIN::width / 2), (MAIN::height / 2));
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
*/