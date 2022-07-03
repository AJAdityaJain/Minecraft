#include"Main.h"
#include"UnivVar.h"

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
	Mesh EntityMesh = Mesh();
	std::cout << "Terrain Gen" << std::endl;

	world.GenerateChunk(0, 0);
	world.EditMesh(BlockMesh);

	EntityMesh.AddFace(FRONT , 0, 0, 0, 49);
	EntityMesh.AddFace(BACK  , 0, 0, 0, 53);
	EntityMesh.AddFace(TOP   , 0, 0, 0, 50);
	EntityMesh.AddFace(BOTTOM, 0, 0, 0, 50);
	EntityMesh.AddFace(EAST	 , 0, 0, 0, 50);
	EntityMesh.AddFace(WEST  , 0, 0, 0, 50);

	Renderer Block = Renderer();
	Renderer Entity = Renderer();
	Block.Bind(BlockMesh);
	Entity.Bind(EntityMesh);

	Texture textures("Resources\\textures.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textures.texUnit(shaderProgram, "tex0", 0);
	textures.Bind();
	std::cout << "Init and Bind Texture" << std::endl;
	
	shaderProgram.Activate();

	Camera camera(1, 6, 1);
	std::cout << "Create Camera" << std::endl;
//Game loop

	glfwSetCursorPos(Window, width/2, height/2);
	while (!glfwWindowShouldClose(Window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(Window);

		camera.Matrix(camera.Position, camera.Orientation.x, camera.Orientation.y, shaderProgram);
		Entity.Bind();
		Entity.Render(EntityMesh.Index.size());

		camera.Matrix(shaderProgram);
		Block.Bind();
		Block.Render(BlockMesh.Index.size());	 

		//std::cout << camera.Orientation2.x << " . " << camera.Orientation2.y << " . " << camera.Orientation2.z << " . " << std::endl;
		//Entity.Bind();
		//Entity.Render(EntityMesh.Index.size());
		
		
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

//©Copyright Aditya Jain