#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include<glm/glm.hpp>

class Entity
{
public:
	glm::vec3 Position;
	glm::vec3 Size = glm::vec3(1, 1, 1);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);

	float speed = 0.1f;


	bool isPointInsideAABB(int x, int y, int z);
	Entity(float x, float y, float z);


};
#endif // !ENTITY_CLASS_H
