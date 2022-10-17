#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "Chunk.h"
#include"Renderer.h"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>

class World {
public:
	std::vector<Chunk*> chunks;
	Mesh MainMesh;
	Renderer Rend;

	void Remove(glm::vec2 ch);
	void Add(glm::vec2 ch);
	void GenerateChunk(int x, int z);
	int  GetBlock(int x, int y, int z);
	void SetBlock(int w, int x, int y, int z);
	void SetMesh();
};

#endif