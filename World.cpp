#include"World.h"

void World::GenerateChunk(int x, int z)
{
	Chunk c (x, z);
	c.Generate();
	World::chunks.push_back(c);
	c = NULL;
}

void World::EditMesh(Mesh& mesh)
{
	for (int i = 0; i < World::chunks.size(); i++)
	{
		World::chunks[i].GetMesh(mesh);
	}
}

int World::GetBlock(int x, int y, int z) {
	{
		int X = x / 16.0f;
		int Z = z / 16.0f;

		
		for (int i = 0; i < chunks.size(); i ++) {
			if (chunks[i].x == X && chunks[i].z == Z) {
				return chunks[0].GetBlock(x%16, y, z%16);
			}
		}
		return 0;
	}
}
