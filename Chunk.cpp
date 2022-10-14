#include"chunk.h"
#include"Main.h"

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
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

}
void Chunk::SetBlock(int c,int x,int y , int z) {
	Chunk::c[x % 16][y % 64][z % 16] = (char)(c + 1);
}
char Chunk::GetChar(int x, int y, int z) {
	return Chunk::c[x%16][y%64][z%16];
}
void Chunk::Generate() {

	
	
	for (int X = 0; X < 16; X++)
	{
		for (int Z = 0; Z < 16; Z++)
		{
			//int f = noise.GetNoise((float)(x * 16 + X), (float)(z * 16 + Z))*5;
			//SetBlock(BEDROCK, X, 1, Z);
			//for (int Y = 2; Y < 23; Y++)
			//{
				//SetBlock(STONE, X, Y, Z);
			//}
			//SetBlock(DIRT, X, 23, Z);
			//SetBlock(DIRT, X, 24, Z);
			//SetBlock(DIRT, X, 25, Z);
			SetBlock(GRASS, X, 26 + (int)(noise.GetNoise((float)(x * 16 + X), (float)(z * 16 + Z)) * 5), Z);
		}
	}
}
void Chunk::Allocate()
{
	std::ofstream MyFile("C:\\MCRipoff\\World\\" + std::to_string(x) + "x" + std::to_string(z) + ".chnk");
	
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
	std::ifstream MyReadFile("C:\\MCRipoff\\World\\" + std::to_string(x) + "x" + std::to_string(z) + ".chnk");
	
	if (MyReadFile.good()) {
		std::string myText;
		getline(MyReadFile, myText);
		int i = 0;
		for (size_t z = 0; z < 16; z++)
		{
			for (size_t y = 0; y < 64; y++)
			{
				for (size_t x = 0; x < 16; x++)
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
		//Allocate();
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

					if (Get(x + 1, y, z) == AIR) {
						mesh.AddFace(EAST, x  , y, z  , TEXTURES[cb]);
					}
					if (Get(x - 1, y, z) == AIR) {
						mesh.AddFace(WEST, x  , y, z  , TEXTURES[cb+1]);
					}
					if (Get(x, y + 1, z) == AIR) {
						mesh.AddFace(TOP, x  , y, z  , TEXTURES[cb+2]);
					}
					if (Get(x, y - 1, z) == AIR) {
						mesh.AddFace(BOTTOM, x  , y, z  , TEXTURES[cb+3]);
					}
					if (Get(x, y, z + 1) == AIR) {
						mesh.AddFace(FRONT, x  , y, z  , TEXTURES[cb+4]);
					}
					if (Get(x, y, z - 1) == AIR) {
						mesh.AddFace(BACK, x  , y, z  , TEXTURES[cb+5]);
					}
				}
			}
		}
	}
}