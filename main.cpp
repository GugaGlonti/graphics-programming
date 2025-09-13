#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int VERSION_MAJOR = 4;
const int VERSION_MINOR = 1;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const char* WINDOW_TITLE = "OpenGL on macOS";

const char* VERTEX_SHADER_SOURCE = R"(
#version 410 core
layout(location = 0) in vec3 position;
void main() {
    gl_Position = vec4(position, 1.0);
}
)";

const char* FRAGMENT_SHADER_SOURCE = R"(
#version 410 core
out vec4 color;
void main() {
    color = vec4(0.8, 0.3, 0.02, 1.0);
}
)";

int main(void) {
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return EXIT_FAILURE;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // This is needed on macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source code
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, nullptr);
    // Compile vertex shader
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source code
    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, nullptr);
    // Compile fragment shader
    glCompileShader(fragmentShader);


    // Create shader program and link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers
    GLfloat vertices[] = {
        -0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f,
         0.5f,      -0.5f * float(sqrt(3)) / 3,     0.0f,
         0.0f,       0.5f * float(sqrt(3)) * 2/ 3,  0.0f,
        -0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f,
         0.5f / 2,   0.5f * float(sqrt(3)) / 6,     0.0f,
         0.0f,      -0.5f * float(sqrt(3)) / 3,     0.0f,
    };

    GLuint indices[] = { 
        0, 3, 5,
        3, 4, 2,
        5, 4, 1,
    };


    GLuint VAO, VBO, EBO;
    // Generate and bind vertex array object
    glGenVertexArrays(1, &VAO);
    // Generate and bind vertex buffer object
    glGenBuffers(1, &VBO);
    // Generate and bind element buffer object
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first
    glBindVertexArray(VAO);
    
    // Bind and set vertex buffer(s)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set element buffer(s)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Define vertex attribute(s)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);
        // Set clear color to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        // Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Destroy window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
