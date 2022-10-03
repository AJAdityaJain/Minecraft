#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include"Entity.h"
#include"Global.h"
#include "Main.h"

void Clamp(float& intPtr, float clamp, int halt) {
	halt = halt == 0 ? -1 : 1;
	if (intPtr > clamp) {
		intPtr = halt * clamp;
	}
	if (intPtr < -clamp) {
		intPtr = -halt * clamp;
	}
}

class Player : public Entity {
public:

	glm::vec3 CamOri = glm::vec3(0,0,0);

	double mouseX;
	double mouseY;

	Player(float x, float y, float z) : Entity::Entity(x, y, z)
	{
		mouseX = 0;
		mouseY = 0;
		Entity::speed = 0.1f;
		Entity::Size = glm::vec3(1, 2, 1);
	}

	void Inputs(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		{
			int W = (width / 2);
			int H = (height / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			glfwGetCursorPos(window, &mouseX, &mouseY);

			mouseX = (W-mouseX ) / 1000 * Controls.Mouse_Sensitivity;
			mouseY = (mouseY - H) / 1000 * Controls.Mouse_Sensitivity;

			Orientation.x += mouseY;
			Orientation.y += mouseX;
			Clamp(Orientation.x, 0.4, true);
			Clamp(Orientation.y, 1, false);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, W, H);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}



		glm::vec3 displacment = glm::vec3(0, 0, 0);
		CamOri = displacment;

		CamOri.y = cos((Orientation.x+0.5f) * 3.1416f);
		float h = sin((Orientation.x+0.5f) * 3.1416f);
		CamOri.z = cos(Orientation.y * 3.1416f)*h;
		CamOri.x = sin(Orientation.y * 3.1416f)*h;

		// Handles key inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			displacment.z += cos(Orientation.y * 3.1416f) * speed;
			displacment.x += sin(Orientation.y * 3.1416f) * speed;
		}


		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			displacment.z -= cos(Orientation.y * 3.1416f) * speed;
			displacment.x -= sin(Orientation.y * 3.1416f) * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			displacment.z += cos((Orientation.y + 0.5f) * 3.1416f) * speed;
			displacment.x += sin((Orientation.y + 0.5f) * 3.1416f) * speed;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
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

		Collision(displacment, Position.x, Position.y, Position.z);
	}
};

#endif // !PLAYER_CLASS_H