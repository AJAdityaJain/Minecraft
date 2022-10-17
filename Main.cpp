//©Copyright Aditya Jain
#include"Main.h"
#include"Global.h"
#include"World.h"
#include"Player.h"

World* a;
glm::vec2 PlayerChunk;
glm::vec2 LPlayerChunk;

int Get(int x, int y, int z) {
	return a->GetBlock(x, y, z);
}

void Set(int w, int x, int y, int z) {
	a->SetBlock(w, x, y, z);
}

void Remesh() {

	a->SetMesh();
}

int SetupWindow(GLFWwindow*& Window) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window = glfwCreateWindow(width, height, "Minecraft-Master", NULL, NULL);

	if (Window == NULL) {
		std::cout << "Window failed to generate... I don't know how to fix this. Sorry\n";
		return -1;
		glfwTerminate();
	}
	glfwMakeContextCurrent(Window);
	glfwMaximizeWindow(Window);
	gladLoadGL();
	glViewport(0, 0, width, height);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.2f, 0.7f, 0.92f, 1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GLFWimage images[1]{};
	int d = 4;
	images[0].pixels = stbi_load("C:\\Minecraft2\\Resources\\Icon.png", &images[0].width, &images[0].height, &d, d); //rgba channels 
	glfwSetWindowIcon(Window, 1, images);
	stbi_image_free(images[0].pixels);
	return 0;
}

int main() {
	std::cout << "Main.cpp" << std::endl;

	GLFWwindow* Window;if (SetupWindow(Window) == -1) {return -1;}
	
	a = new World();
	CHUNK_CLASS_H::noise.SetNoiseType(noise.NoiseType_Perlin);
	a->GenerateChunk(16,16);
	Remesh();


	Shader shaderProgram("C:\\Minecraft2\\Resources\\default.vert.shader", "C:\\Minecraft2\\Resources\\default.frag.shader");


	Texture textures("C:\\Minecraft2\\Resources\\textures.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);textures.texUnit(shaderProgram, "tex0", 0);	textures.Bind();shaderProgram.Activate();


	Camera camera(0, 0, 0);	Player player(16*16, 30, 16*16);camera.ProjMatrix();
	

	glfwSetCursorPos(Window, width/2.0, height/2.0);
	
	while (!glfwWindowShouldClose(Window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		PlayerChunk.x = (int)(player.Position.x / 16);PlayerChunk.y = (int)(player.Position.z / 16);

		if (PlayerChunk != LPlayerChunk) {
			LPlayerChunk = PlayerChunk;
			a->Add(PlayerChunk);
			a->Remove(PlayerChunk);
			Remesh();
		}


		player.Inputs(Window);

		camera.CMatrix(player.Position,player.CamOri);

		camera.Matrix(shaderProgram);
		a->Rend.Render(a->MainMesh.Index.size());
		
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
	for (auto c : a->chunks) {
		c->Allocate();
	}

	std::cout << "Delete everything" << std::endl;

	a->Rend.Delete();
	textures.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(Window);
	glfwTerminate();

	return 0;
}