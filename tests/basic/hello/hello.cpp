#include <iostream>

#include "skygl.h"

using namespace sky::gl;

const UInt WIDTH = 800, HEIGHT = 600;

bool initGLFW() {
    glfwInit();
    Window::hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    Window::hint(GLFW_CONTEXT_VERSION_MINOR, 3);
    Window::hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Window::hint(GLFW_RESIZABLE, GL_FALSE);
    return true;
}

bool initGLEW() {
    glewExperimental = GL_TRUE;
    return glewInit() == GLEW_OK;
}

int main() {
    if (!initGLFW()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    Window window(WIDTH, HEIGHT, "basic/shader");

    window.keypressed.connect([&window](Key key) {
        std::cout << "Key: " << key << " " << key.code << std::endl;
        if (key == GLFW_KEY_ESCAPE)
            window.close();
    });
    window.created.connect([&window]() {
        if (!initGLEW()) {
            std::cout << "Failed to initialize GLEW" << std::endl;
        }
        Int width = window.getWidth(), height = window.getHeight();
        glViewport(0, 0, width, height);
    });

    window.create();

    window.loop([]() {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    });

    glfwTerminate();
    return 0;
}
