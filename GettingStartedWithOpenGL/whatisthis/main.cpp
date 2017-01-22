#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec3 position;\n"
                                   "void main()\n"
                                   "{\n"
                                   "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                   "}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 color;\n"
                                     "void main()\n"
                                     "{\n"
                                     "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n\0";

int main (int argc, char * argv[])
{
    std::cout << "HI!" << std::endl;

    if (!glfwInit())
    {
        // Initialization failed
        std::cout << "Failed to initialize GLFW" << std::endl;
        glfwSetErrorCallback(error_callback);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // to 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // from 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core-profile only
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //tells GLFW to make the context of our window
    //the main context on the current thread
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); //registers the function with the proper callback

    //Setting glewExperimental to true ensures GLEW
    //uses more modern techniques for managing OpenGL
    //functionality. Leaving it to its default value
    //of GL_FALSE might give issues when using the
    //core profile of OpenGL.
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height); //retrieves width and height from GLFW

    glViewport(0, 0, width, height); //may be smaller, but not bigger. Transforms to -1;1 coords and back

    // VERTEX SHADER
    GLuint vertexShader; //stores the vertex shader as a GLuint ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER); //creates a vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //attachs the shader source code to the shader object
    glCompileShader(vertexShader); //compiles the shader

    //checking for compile-time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //checks if compilation was successful

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); //retrieves the error message
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // FRAGMENT SHADER (the same)
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
{
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
}

    // SHADER PROGRAM
    GLuint shaderProgram; // ID
    shaderProgram = glCreateProgram(); // creates and stores

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADERPROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //deleting shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram); //every shader and rendering call will
                                 //now use this program object (and thus the shaders)

    //checks at the start of each loop iteration
    //if GLFW has been instructed to close,
    //if so, the function returns true
    while(!glfwWindowShouldClose(window))
    {
        //checks if any events are triggered (like
        //keyboard input or mouse movement events)
        //and calls the corresponding functions
        //(which we can set via callback methods)
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //swap the color buffer (a large buffer that
        //contains color values for each pixel in
        //GLFW's window) that has been used to draw
        //in during this iteration and show it as
        //output to the screen
        glfwSwapBuffers(window);
    }

    glfwTerminate(); // properly cleans/deletes all resources that were allocated

    return 0;
}

void error_callback(int error, const char* description)
{
    std::cout << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
