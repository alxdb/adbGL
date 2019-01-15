#include <stdexcept>

#include <Core.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
	// Config
	std::string title = "BasicTriangle";
	int width = 800, height = 600;
	// Res
	const std::vector<GLfloat> triangle_vertices = {
		-1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f
	};

	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float) width / (float) height,
		0.1f,
		100.0f
	);

	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

	glm::mat4 model = glm::mat4(1.0f);

	// Setup
	Window window(width, height, title.c_str());
	window.makeCurrent();
	Shader shader("shaders/base.vs.glsl", "shaders/base.fs.glsl");

	shader.set_uniform(shader.uniforms.at("mvp.model"), model);
	shader.set_uniform(shader.uniforms.at("mvp.view"), view);
	shader.set_uniform(shader.uniforms.at("mvp.projection"), projection);

	VertexArray vao;
	VertexBuffer vbo;

	vao.set_attribute_pointer(vbo, shader.attributes.at("pos").index);
	vbo.buffer_data(triangle_vertices, GL_STATIC_DRAW);

	// Render
	while (!window.shouldClose()) {
		vao.bind();
		shader.use();

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.update();
	}
}
