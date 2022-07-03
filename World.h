#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H


#include"Chunk.h"
#include<vector>
#include "Camera.h"

class World {
private:
	std::vector<Chunk> chunks;

public:
	void GenerateChunk(int x, int z);

	void EditMesh(Mesh& mesh);
	int GetBlock(int x, int y, int z);

};

#endif