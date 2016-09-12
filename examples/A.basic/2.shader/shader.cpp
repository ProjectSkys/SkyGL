#include <iostream>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "basic";
const String NAME = "shader";
const UInt WIDTH = 800, HEIGHT = 600;

bool initGLFW() {
    glfwInit();
    Window::hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    Window::hint(GLFW_CONTEXT_VERSION_MINOR, 3);
    Window::hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Window::hint(GLFW_RESIZABLE, GL_TRUE);
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
    Window window(WIDTH, HEIGHT, UNIT + "/" + NAME);

    window.created.connect([&window]() {
        if (!initGLEW()) {
            std::cout << "Failed to initialize GLEW" << std::endl;
        }
        UInt width = window.getWidth(), height = window.getHeight();
        glViewport(0, 0, width, height);
    });
    window.resized.connect([](int width, int height) {
        glViewport(0, 0, width, height);
    });
    window.keypressed.connect([&window](Key key) {
        if (key == GLFW_KEY_ESCAPE)
            window.close();
    });

    window.create();

    Program shader(NAME + ".vs", NAME + ".frag");

    Float vertices[] {
        // Positions       // Colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Left
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Top
    };

    VertexArray VAO;
    ArrayBuffer VBO;

    SKY_BIND(VAO) {
        _.buffer(VBO).data(vertices);
        _.attrib(0).has<Float>(3).stride(SizeOf<6, Float>).offset(0);
        _.attrib(1).has<Float>(3).stride(SizeOf<6, Float>).offset(SizeOf<3, Float>);
    }

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        SKY_BIND(VAO) {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    });

    glfwTerminate();
}
