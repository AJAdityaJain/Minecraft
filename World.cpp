#include "World.h"

void World::GenerateChunk(int x, int z)
{
	Chunk* c;
	c = new Chunk(x, z);
	c->Retrieve();
	World::chunks.push_back(c);
	c = nullptr;
}
void World::SetMesh()
{
	MainMesh.Clear();
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i]->SetMesh(MainMesh);
	}
}