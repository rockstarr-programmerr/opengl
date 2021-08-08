#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void swapColor(bool &changed, int &color, GLFWwindow* window)
{
	double seconds_passed = glfwGetTime();
	bool is_turn = (int)seconds_passed % 2 == 0;

	if (is_turn)
	{
		if (!changed)
		{
			if (color == 0)
			{
				glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
				color = 1;
			}
			else if (color == 1)
			{
				glClearColor(1.0f, 0.65f, 0.0f, 1.0f);
				color = 0;
			}
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			changed = true;
		}
	}
	else
	{
		changed = false;
	}
}

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

	//glClearColor(1.0f, 0.65f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glfwSwapBuffers(window);

	bool changed = false;
	int color = 0;
	while (!glfwWindowShouldClose(window))
	{
		swapColor(changed, color, window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
