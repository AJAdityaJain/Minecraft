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
	return 0;
}

int main() {
	std::cout << "Main.cpp" << std::endl;
	
	GLFWwindow* Window;if (SetupWindow(Window) == -1) {return -1;}
	GLFWimage images[1]{};
	int d = 4;
	images[0].pixels = stbi_load("C:\\MCRipoff\\Resources\\Icon.png", &images[0].width, &images[0].height, &d, d); //rgba channels 
	glfwSetWindowIcon(Window, 1, images);
	stbi_image_free(images[0].pixels);

	std::cout << "Init and setup window" << std::endl;

	

	a = new World();
	a->GenerateChunk(16,16);
	a->SetMesh();
	Renderer Block = Renderer();	
	Block.Bind(a->MainMesh);
	
	std::cout << "Terrain Gen" << std::endl;




	Shader shaderProgram("C:\\MCRipoff\\Resources\\default.vert.shader", "C:\\MCRipoff\\Resources\\default.frag.shader");
	
	std::cout << "Setup Shader" << std::endl;




	Texture textures("C:\\MCRipoff\\Resources\\textures.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	textures.texUnit(shaderProgram, "tex0", 0);
	textures.Bind();
	shaderProgram.Activate();

	std::cout << "Init and Bind Texture" << std::endl;
	

	Camera camera(0, 0, 0);
	Player player(16*16, 30, 16*16);
	
	std::cout << "Create Camera and Player" << std::endl;

	camera.ProjMatrix();

	glfwSetCursorPos(Window, width/2.0, height/2.0);
	
	while (!glfwWindowShouldClose(Window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		PlayerChunk.x = (int)(player.Position.x / 16);PlayerChunk.y = (int)(player.Position.z / 16);

		if (PlayerChunk != LPlayerChunk) {
			LPlayerChunk = PlayerChunk;
			a->Add(PlayerChunk);
			a->Remove(PlayerChunk);
			a->SetMesh();
			Block.Bind(a->MainMesh);
		}


		player.Inputs(Window);

		camera.CMatrix(player.Position,player.CamOri);

		camera.Matrix(shaderProgram);
		Block.Render(a->MainMesh.Index.size());
		
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