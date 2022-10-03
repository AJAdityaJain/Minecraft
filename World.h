#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "Chunk.h"

class World {
public:
	std::vector<Chunk*> chunks;
	Mesh MainMesh;

	void GenerateChunk(int x, int z);

	void SetMesh();
};

#endif