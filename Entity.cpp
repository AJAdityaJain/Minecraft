#include "Entity.h"

Entity::Entity(float x, float y, float z) {
	//Position = glm::vec3(0, 0, 0);
	Position = glm::vec3(x, y, z);
}


bool Entity::isPointInsideAABB(int x, int y, int z) {
	return
		(x - 1 >= Position.x || x <= Position.x - Size.x) ||
		(y - 1 >= Position.y || y <= Position.y - Size.y) ||
		(z - 1 >= Position.z || z <= Position.z - Size.z);
}