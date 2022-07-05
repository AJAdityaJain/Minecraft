#include"Main.h"
#include "Player.h"
#include"Global.h"

//©Copyright Aditya Jain
World world;

int GetBlock(int x, int y, int z) {
	return world.GetBlock(x,y,z);
}

int SetupWindow(GLFWwindow*& Window) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);

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
	return 0;
}


int main() {
	std::cout << "Main.cpp" << std::endl;
	
	GLFWwindow* Window;if (SetupWindow(Window) == -1) {return -1;}

	std::cout << "Init and setup window" << std::endl;

	
	Shader shaderProgram("Resources\\default.vert.shader", "Resources\\default.frag.shader");
	std::cout << "Setup Shader" << std::endl;

	Mesh BlockMesh = Mesh();
	std::cout << "Terrain Gen" << std::endl;

	world.GenerateChunk(0, 0);
	world.EditMesh(BlockMesh);

	Renderer Block = Renderer();
	
	Block.Bind(BlockMesh);
	
	Texture textures("Resources\\textures.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textures.texUnit(shaderProgram, "tex0", 0);
	textures.Bind();
	std::cout << "Init and Bind Texture" << std::endl;
	
	shaderProgram.Activate();

	Camera camera(0, 0, 0);
	Player player(0, 0, 0);
	std::cout << "Create Camera and Player" << std::endl;
//Game loop

	camera.ProjMatrix();

	glfwSetCursorPos(Window, width/2, height/2);
	while (!glfwWindowShouldClose(Window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player.Inputs(Window);

		
		camera.CMatrix(player.Position,player.CamOri);

	/*	camera.Matrix(player.Position, player.Orientation.x, player.Orientation.y, shaderProgram);
		Entity.Bind();
		Entity.Render(EntityMesh.Index.size());*/

		camera.Matrix(shaderProgram);
		Block.Bind();
		Block.Render(BlockMesh.Index.size());	 		
		
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}

	std::cout << "Delete everything" << std::endl;

	Block.Delete();
	textures.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(Window);
	glfwTerminate();

	return 0;
}