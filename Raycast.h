#ifndef RAYCAST
#define RAYCAST

#include<glm/glm.hpp>
#include"Game.h"

class Raycast
{
public:
	glm::vec3 Position = GAME_CLASS_H::Vec30;
	glm::vec3 Orientation = GAME_CLASS_H::Vec30;
	float SpeedInv = 1;
	void Orient(glm::vec3 o);
	void MoveCheck(bool b);

};

#endif