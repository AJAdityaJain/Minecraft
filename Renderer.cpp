#include"Renderer.h"


Renderer::Renderer() {

}

void Renderer::Bind() {
	vao.Bind();
}
void Renderer::Bind(Mesh mesh) {
	vao.Bind();

	VBO VBO1(mesh.Vertex);

	EBO EBO1(mesh.Index);

	vao.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(Vert), (void*)0);
	vao.LinkAttrib(VBO1, 1, 2, GL_FLOAT, sizeof(Vert), (void*)(3 * sizeof(float)));

	vao.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	VBO1.Delete();
	EBO1.Delete();
	vao.Bind();
}

void Renderer::Render(size_t indexSize) {
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}

void Renderer::Delete() {
	vao.Delete();
}