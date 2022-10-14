#ifndef RAYCAST
#define RAYCAST

#include<glm/glm.hpp>
#include"Main.h"

class Raycast
{
public:
	glm::vec3 Position = Vec30;
	glm::vec3 Orientation = Vec30;
	float SpeedInv = 4;
	void Orient(glm::vec3 o);
	void MoveCheck(bool b);

};

#endif