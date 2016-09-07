#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "basic";
const String NAME = "geometry";
const UInt WIDTH = 800, HEIGHT = 600;

Float points[] {
    // Position   // Color
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // Bottom-left
};

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

bool setupGL() {
    glEnable(GL_DEPTH_TEST);
    return true;
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
        if (!setupGL()) {
            std::cout << "Failed to setup OpenGL" << std::endl;
        }
        UInt width = window.getWidth(), height = window.getHeight();
        glViewport(0, 0, width, height);
    });
    window.resized.connect([](int width, int height) {
        glViewport(0, 0, width, height);
    });
    window.keypressed.connect([&](Key key) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                window.close();
                break;
        }
    });
    window.create();
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    VertexArray VAO;
    ArrayBuffer VBO;
    VAO.bind();
        VAO.buffer(VBO)
           .data(points, sizeof(points));
        VAO.attrib(0).has<Float>(2)
           .stride(SizeOf<5, Float>).offset(0);
        VAO.attrib(1).has<Float>(2)
           .stride(SizeOf<5, Float>).offset(SizeOf<2, Float>);
    VAO.unbind();

    Program shader(NAME + ".vs", NAME + ".frag", NAME + ".gs");

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        VAO.bind();
            glDrawArrays(GL_POINTS, 0, 4);
        VAO.unbind();

    });

    glfwTerminate();
    return 0;
}
