#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "Chunk.h"
#include <glm/ext/vector_float2.hpp>

class World {
public:
	std::vector<Chunk*> chunks;
	Mesh MainMesh;

	void Remove(glm::vec2 ch);
	void Add(glm::vec2 ch);
	void GenerateChunk(int x, int z);
	int  GetBlock(int x, int y, int z);
	void SetMesh();
};

#endif