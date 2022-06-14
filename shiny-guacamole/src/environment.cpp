#include "environment.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void error_callback(int error, const char *description);
void processInput(GLFWwindow *window);

Environment::Environment(int width, int height, std::string title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ENVIRONMENT::CONSTRUCT::WINDOW::FAILED" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ENVIRONMENT::CONSTRUCT::GLAD::FAILED" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    shaders = Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
}

Environment::~Environment()
{
    glfwTerminate();
}

void Environment::addShape(std::shared_ptr<Shape> shape)
{
    shapes.push_back(shape);
}

void Environment::addShape(Shape &shape)
{
    shapes.push_back(std::shared_ptr<Shape>(&shape));
}

void Environment::removeShape(std::shared_ptr<Shape> shape)
{
    for (int i = 0; i < shapes.size(); i++)
    {
        if (shapes[i] == shape)
        {
            shapes.erase(shapes.begin() + i);
        }
    }
}

void Environment::removeShape(int index)
{
    shapes.erase(shapes.begin() + index);
}

std::vector<std::shared_ptr<Shape>> Environment::getShapes() const
{
    return shapes;
}

void Environment::render()
{

    float vertices[] = {
        // positions          // texture coords
        0.5f, 0.5f, 0.0f,    // top right
        0.5f, -0.5f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f, 0.0f,    // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaders.use();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shaders.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shaders.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        shaders.setMat4("projection", projection);

        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->render();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Environment::setShaders(const GLchar *vertexShader, const GLchar *fragmentShader)
{
    shaders = Shader(vertexShader, fragmentShader);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void error_callback(int error, const char *description)
{
    std::cout << "GLFW::ERROR::" << description << std::endl;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}