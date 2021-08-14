#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,  // Lower left
	0.5f, -0.5f, 0.0f,  // Lower right
	0.0f, 0.5f, 0.0f,  // Top
	-0.25f, 0.0f, 0.0f,  // Middle left
	0.0f, -0.5f, 0.0f,  // Middle bottom
	0.25f, 0.0f, 0.0f  // Middle right
};

GLuint indices[] =
{
	0, 4, 3,  // Lower left triangle
	4, 1, 5,  // Lower right triangle
	3, 5, 2  // Top triangle
};


int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const char* window_name = "Babushka is soup ready?";
	GLFWwindow* window = glfwCreateWindow(800, 800, window_name, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shader_program("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.Activate();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shader_program.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
