#include "window.hpp"
#include <stdexcept>


SG::Window::Window(vec2i size,vec2i pos, char const *name ): size(size), pos(pos), windowId(windowCount++){
    window = glfwCreateWindow(size.x, size.y, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

}

SG::Window::Window(int x_size, int y_size, int x_pos , int y_pos, char const *name): size(x_size, y_size), pos(x_pos, y_pos), windowId(windowCount++)
{
    window = glfwCreateWindow(x_size, y_size, name, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

}

void SG::Window::render()
{
    glfwMakeContextCurrent(window);
    for(auto shape : shapes){
        shape->render();
    }
    glfwSwapBuffers(window);
}

GLFWwindow * const SG::Window::getWindow(){
    return window;
}

void SG::Window::addShape(Shape *shape)
{
    shapes.push_back(shape);
}


unsigned int SG::Window::windowCount = 0;