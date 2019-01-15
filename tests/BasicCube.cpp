//
// Created by alxdb on 10/01/19.
//

#include <Core.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>

int main() {
	// Config
	std::string title = "BasicCube";
	int width = 800, height = 600;
	// Res
	const std::vector<GLfloat> cube_vertices = {
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 1.0f
	};


	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		(float) width / (float) height,
		0.1f,
		100.0f
	);

	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, -3),
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

	VertexBuffer pos_vbo;
	VertexBuffer col_vbo;

	pos_vbo.buffer_data(cube_vertices, GL_STATIC_DRAW);
	col_vbo.buffer_data(cube_vertices, GL_STATIC_DRAW);

	VertexArray vao;
	vao.set_attribute_pointer(pos_vbo, shader.attributes.at("pos").index);
	vao.set_attribute_pointer(col_vbo, shader.attributes.at("col").index);


	// Render
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	while (!window.shouldClose()) {
		vao.bind();
		shader.use();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		window.update();
	}
}
