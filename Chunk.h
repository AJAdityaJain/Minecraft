#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Global.h"
#include "Mesh.h"
#include "libraries/include/inc/Perlin.h"


static FastNoiseLite noise;

class Chunk {
public:
	int x = 0;
	int z = 0;
	
	Chunk(int X=16, int Z=16);
	void SetBlock(int w, int X, int y, int Z);
	char GetChar(int x, int y, int z);
	
	void Allocate();
	void Retrieve();

	void SetMesh(Mesh& mesh);

private:
	char c[16][64][16];
	void Generate();
};

#endif