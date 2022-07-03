#include"chunk.h"
#include"Main.h"

Chunk::Chunk(int X, int Z) {
	Chunk::x = X; Chunk::z = Z;
	
	for (short x = 0; x < 16; x++)
	{
		for (short y = 0; y < 48; y++)
		{
			for (short z = 0; z < 16; z++)
			{
				SetBlock(0, x, y, z);
			}
		}
	}
}

void Chunk::SetBlock(int c,int x,int y , int z) {
	Chunk::c[x][y][z] = (char)(c+1);
}

int Chunk::GetBlock(int x, int y, int z) {
	if (x >= 0 && y >= 0 && z >= 0) {
		return (int)(Chunk::c[x][y][z]-1);
	}
	return 0;
}

void Chunk::Generate() {
	//FastNoiseLite noise;
	//noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	//noise.SetSeed(76541);
	
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			//int n = (int)noise.GetNoise((float)x, (float)y)*10 + 11;
			SetBlock(1, x, 10, y);
			SetBlock(2, x, 9, y);
			//SetBlock(2, x, 8, y);
			//SetBlock(2, x, 7, y);
			//SetBlock(3, x, 6, y);
			//SetBlock(3, x, 5, y);
			//SetBlock(4, x, 4, y);
		}
	}

	SetBlock(1, 1, 0, 1);

}

void Chunk::GetMesh(Mesh& mesh) {
	int cb = 0;
	for (short x = Chunk::x * 16; x < (Chunk::x * 16) + 16; x++)
	{
		for (short y = 0; y < 48; y++)
		{
			for (short z = Chunk::z * 16; z < (Chunk::z * 16)+16; z++)
			{
				cb = MAIN::GetBlock(x, y, z) * 6;
				if (cb != 0) {

					if (MAIN::GetBlock(x + 1, y, z) == 0) {
						mesh.AddFace(EAST, x  , y, z  , TEXTURES[cb]);
					}
					if (MAIN::GetBlock(x - 1, y, z) == 0) {
						mesh.AddFace(WEST, x  , y, z  , TEXTURES[cb+1]);
					}
					if (MAIN::GetBlock(x, y + 1, z) == 0) {
						mesh.AddFace(TOP, x  , y, z  , TEXTURES[cb+2]);
					}
					if (MAIN::GetBlock(x, y - 1, z) == 0) {
						mesh.AddFace(BOTTOM, x  , y, z  , TEXTURES[cb+3]);
					}
					if (MAIN::GetBlock(x, y, z + 1) == 0) {
						mesh.AddFace(FRONT, x  , y, z  , TEXTURES[cb+4]);
					}
					if (MAIN::GetBlock(x, y, z - 1) == 0) {
						mesh.AddFace(BACK, x  , y, z  , TEXTURES[cb+5]);
					}
				}
			}
		}
	}
	std::cout << TEXTURES[cb + 2] << "ENDVAL" << cb << "blok";
}
