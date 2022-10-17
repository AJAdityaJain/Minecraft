#include"chunk.h"
#include"Main.h"

static bool notOpaque(int x, int y, int z) {
	int b = Get(x, y, z);
	return b == AIR || b == CROSS_GRASS || b == LEAVES || b == ROSE || b == FLOWER_LEAVES;
}
static bool isBlock(int x) {
	return x != CROSS_GRASS && x != ROSE;
}

Chunk::Chunk(int X, int Z) {
	Chunk::x = X; Chunk::z = Z;
	
	for (short x = 0; x < 16; x++)
	{
		for (short y = 0; y < 64; y++)
		{
			for (short z = 0; z < 16; z++)
			{
				SetBlock(AIR, x, y, z);
			}
		}
	}

}
void Chunk::SetBlock(int w, int X, int y, int Z) {
		Chunk::c[X%16][y][Z%16] = (char)(w + 1);
	
}
char Chunk::GetChar(int x, int y, int z) {
	if (y <= 0)
		return AIR;
	return Chunk::c[x%16][y%64][z%16];
}
void Chunk::Generate() {

	
	
	for (int X = 0; X < 16; X++)
	{
		for (int Z = 0; Z < 16; Z++)
		{
			int f = (int)(noise.GetNoise((float)(x * 16 + X), (float)(z * 16 + Z)) * 6);
			for (int Y = 2; Y < 24+f; Y++)
			{
				SetBlock(STONE, X, Y, Z);
			}
			SetBlock(DIRT, X, 24 + f, Z);
			SetBlock(DIRT, X, 25 + f, Z);
			SetBlock(DIRT, X, 26 + f, Z);

			SetBlock(GRASS, X, 27 + f, Z);
			if ((rand() % 100) < 8)
				SetBlock(CROSS_GRASS, X, 28 + f, Z);
			if ((rand() % 100) < 2)
				SetBlock(ROSE, X, 28 + f, Z);

			if (X == 7 && Z == 7) {
				SetBlock(LOG, X, 28 + f, Z);
				SetBlock(LOG, X, 29 + f, Z);

				SetBlock(LEAVES, X - 1, 30 + f, Z);
				SetBlock(LEAVES, X + 1, 30 + f, Z);
				SetBlock(LEAVES, X, 30 + f, Z - 1);
				SetBlock(LEAVES, X, 30 + f, Z + 1);
				SetBlock(LOG, X, 30 + f, Z);

				SetBlock(LEAVES, X - 1, 31 + f, Z);
				SetBlock(LEAVES, X + 1, 31 + f, Z);
				SetBlock(LEAVES, X, 31 + f, Z - 1);
				SetBlock(LEAVES, X, 31 + f, Z + 1);
				SetBlock(LEAVES, X, 31 + f, Z);
				
				SetBlock(LEAVES, X, 32 + f, Z);

			}
			SetBlock(BEDROCK, X, 1, Z);

		}
	}
}
void Chunk::Allocate()
{
	std::ofstream MyFile("C:\\Minecraft2\\World\\" + std::to_string(x) + "x" + std::to_string(z) + ".chnk");
	
	for (size_t x = 0; x < 16; x++)
	{
		for (size_t y = 0; y < 64; y++)
		{
			for (size_t z = 0; z < 16; z++)
			{
				MyFile << (char)c[x][y][z];
			}
		}
	}
	
	MyFile.close();
}
void Chunk::Retrieve()
{
	std::ifstream MyReadFile("C:\\Minecarft2\\World\\" + std::to_string(x) + "x" + std::to_string(z) + ".chnk");
	
	if (MyReadFile.good()) {
		std::string myText;
		getline(MyReadFile, myText);
		int i = 0;
		for (short x = 0; x < 16; x++)
		{
			for (short y = 0; y < 64; y++)
			{
				for (short z = 0; z < 16; z++)
				{
					Chunk::c[x][y][z] = (char)myText[i];
					i++;
				}
			}
		}	
		myText = "";
	}
	else {
		Generate();
		Allocate();
	}
	MyReadFile.close();

}
void Chunk::SetMesh(Mesh& mesh) {
	int cb = 0;
	for (short x = Chunk::x * 16; x < (Chunk::x * 16) + 16; x++)
	{
		for (short y = 0; y < 64; y++)
		{
			for (short z = Chunk::z * 16; z < (Chunk::z * 16)+16; z++)
			{
				cb = Get(x, y, z) * 6;
				if (cb != 0) {
					if (isBlock(cb/6)) {
						if (notOpaque(x + 1, y, z)) {
							mesh.AddFace(EAST, x, y, z, TEXTURES[cb]);
						}
						if (notOpaque(x - 1, y, z)) {
							mesh.AddFace(WEST, x, y, z, TEXTURES[cb + 1]);
						}
						if (notOpaque(x, y + 1, z)) {
							mesh.AddFace(TOP, x, y, z, TEXTURES[cb + 2]);
						}
						if (notOpaque(x, y - 1, z)) {
							mesh.AddFace(BOTTOM, x, y, z, TEXTURES[cb + 3]);
						}
						if (notOpaque(x, y, z + 1)) {
							mesh.AddFace(FRONT, x, y, z, TEXTURES[cb + 4]);
						}
						if (notOpaque(x, y, z - 1)) {
							mesh.AddFace(BACK, x, y, z, TEXTURES[cb + 5]);
						}
					}
					else {
						mesh.AddFace(DIAG1, x, y, z, TEXTURES[cb]);
						mesh.AddFace(DIAG2, x, y, z, TEXTURES[cb]);
					}
				}
			}
		}
	}
}