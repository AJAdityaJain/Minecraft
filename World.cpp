#include "World.h"
int World::GetBlock(int x, int y, int z) {
	for (size_t i = 0; i < chunks.size(); i++)
	{
		if (chunks[i]->x == (int)(x / 16) && chunks[i]->z == (int)(z / 16)) {
			return -1 + (int)chunks[i]->GetChar(x, y, z);
		}
	}
	return 1;
}
void World::GenerateChunk(int x, int z)
{
	if (x >= 0 && z >= 0) {
		Chunk* c;
		c = new Chunk(x, z);
		c->Retrieve();
		World::chunks.push_back(c);
		c = nullptr;
	}
}
void World::SetMesh()
{
	MainMesh.Clear();
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->SetMesh(MainMesh);
	}
}
void World::Remove(glm::vec2 ch) {
	for (int i = 0; i < chunks.size(); i++)
	{
		if (abs(chunks[i]->x - ch.x) > Graphics.Render_Distance || abs(chunks[i]->z - ch.y) > Graphics.Render_Distance) {
			chunks.erase(chunks.begin() + i);
		}
	}
}
void World::Add(glm::vec2 ch) {
	bool b = true;
	
	for (int x = -Graphics.Render_Distance; x < Graphics.Render_Distance+ 1; x++)
	{
		for (int y = -Graphics.Render_Distance; y < Graphics.Render_Distance+ 1; y++)
		{
			b = true;
			for (size_t i = 0; i < chunks.size(); i++)
			{
				if (chunks[i]->x == ch.x + x && chunks[i]->z == ch.y + y) {
					b = false;
					i = chunks.size();
				}

			}
			if (b)
				GenerateChunk(x + ch.x, y + ch.y);
		}
	}
}