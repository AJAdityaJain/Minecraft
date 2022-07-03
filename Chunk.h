#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "UnivVar.h"
#include "Mesh.h"
#include "libraries/include/inc/Perlin.h"

class Chunk {
public:
	char c[16][48][16];
	int x = 0;
	int z = 0;
	
	Chunk(int X=16, int Z=16);
	void SetBlock(int c, int x, int y, int z);
	int  GetBlock(int x, int y, int z);
	void Generate();
	void GetMesh(Mesh& mesh);
};

#endif