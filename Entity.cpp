#include "Entity.h"
#include<iostream>
Entity::Entity(float x, float y, float z) {
	//Position = glm::vec3(0, 0, 0);
	Position = glm::vec3(x, y, z);
}

void Entity::Collision(glm::vec3 displacment, int x, int y, int z) {
	//std::cout << x << " . " << y << " . " << z << " . " << std::endl;
	Position += displacment;
}