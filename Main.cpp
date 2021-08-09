#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vshader);

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fshader);

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vshader);
	glAttachShader(shader_program, fshader);
	glLinkProgram(shader_program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f,  // Lower left
		 0.5f, -0.5f,  // Lower right
		 0.5f,  0.5f,  // Upper right
		-0.5f,  0.5f,  // Upper left
	};

	GLuint VAOs[1] = { 0 };
	GLuint VBOs[1] = { 0 };

	glGenVertexArrays(1, VAOs);
	glGenBuffers(1, VBOs);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, VBOs);
	glDeleteVertexArrays(1, VAOs);
	glDeleteProgram(shader_program);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
