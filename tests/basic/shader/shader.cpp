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
        UInt width = window.getWidth(), height = window.getHeight();
        glViewport(0, 0, width, height);
    });

    window.create();

    Shader shader("basic.vs", "basic.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] {
        // Positions       // Colors
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom Right
       -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Left
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Top
    };

    VertexArray VAO;
    ArrayBuffer VBO;

    VAO.bind();
        VAO.buffer(VBO)
           .data(vertices, sizeof(vertices));
        VAO.attrib(0).has<Float>(3)
           .offset(0).stride(SizeOf<6, Float>);
        VAO.attrib(1).has<Float>(3)
           .offset(SizeOf<3, Float>).stride(SizeOf<6, Float>);
    VAO.unbind();

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        VAO.bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
        VAO.unbind();
    });

    glfwTerminate();
    return 0;
}
