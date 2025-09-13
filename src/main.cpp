#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const int VERSION_MAJOR = 4;
const int VERSION_MINOR = 1;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "OpenGL on macOS";


GLfloat vertices[] =
{
	-0.5f,     -0.5f * float(sqrt(3)) / 3,      0.0f,
	 0.5f,     -0.5f * float(sqrt(3)) / 3,      0.0f,
	 0.0f,      0.5f * float(sqrt(3)) * 2 / 3,  0.0f,
	-0.5f / 2,  0.5f * float(sqrt(3)) / 6,      0.0f,
	 0.5f / 2,  0.5f * float(sqrt(3)) / 6,      0.0f,
	 0.0f,     -0.5f * float(sqrt(3)) / 3,      0.0f,
};

GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};


int main()
{
	if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

	int fbWidth, fbHeight;
	glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);


	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		shaderProgram.Activate();
		VAO1.Bind();
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}