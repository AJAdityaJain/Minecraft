#include "Entity.h"
#include<iostream>
Entity::Entity(float x, float y, float z) {
	//Position = glm::vec3(0, 0, 0);
	Position = glm::vec3(x, y, z);
}

void Entity::Collision(glm::vec3 displacment, int x,int y ,int z) {
	std::cout << x << " . " << y << " . " << z << " . " << std::endl;

	Position.x += displacment.x;
	if (isPointInsideAABB(x, y, z)) {
		Position.x -= displacment.x;
	}

	Position.y += displacment.y;
	if (isPointInsideAABB(x, y, z)) {
		Position.y -= displacment.y;
	}

	Position.z += displacment.z;
	if (isPointInsideAABB(x, y, z)) {
		Position.z -= displacment.z;
	}
}

bool Entity::isPointInsideAABB(int x, int y, int z) {
	return
		(x - 1 <= Position.x && x >= Position.x - Size.x) &&
		(y - 1 <= Position.y && y >= Position.y - Size.y) &&
		(z - 1 <= Position.z && z >= Position.z - Size.z);
}