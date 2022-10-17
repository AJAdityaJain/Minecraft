#include "Raycast.h"

void Raycast::Orient(glm::vec3 o) {
	Orientation = glm::normalize(o);

	//Orientation += Vec35;
}

void Raycast::MoveCheck(bool b, int bl) {
	if (b) {
		glm::vec3 lp = Vec30;
		for (size_t i = 0; i < 5*SpeedInv; i++)
		{
			Position += Orientation / SpeedInv;

			if (Get((int)Position.x, (int)Position.y, (int)Position.z) == AIR) {
				lp = Position;
			}
			else {
				Set(bl, (int)lp.x, (int)lp.y, (int)lp.z);
				return;
			}
		}
	}
	else {
		for (size_t i = 0; i < 5 * SpeedInv; i++)
		{
			Position += Orientation / SpeedInv;

			if (Get((int)Position.x, (int)Position.y, (int)Position.z) != AIR) {
				Set(AIR, (int)Position.x, (int)Position.y, (int)Position.z);
				return;
			}
		}
	}
}