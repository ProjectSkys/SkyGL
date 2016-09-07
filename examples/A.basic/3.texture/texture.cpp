#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "basic";
const String NAME = "texture";
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

    Program program(NAME + ".vs", NAME + ".frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    Float vertices[] {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };
    UInt indices[] {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    VertexArray VAO;
    ArrayBuffer VBO;
    ElementBuffer EBO;

    VAO.bind();
        VAO.buffer(VBO)
           .data(vertices, sizeof(vertices));
        VAO.buffer(EBO)
           .data(indices, sizeof(indices));
        VAO.attrib(0).has<Float>(3)
           .stride(SizeOf<8, Float>).offset(0);
        VAO.attrib(1).has<Float>(3)
           .stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        VAO.attrib(2).has<Float>(2)
           .stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    VAO.unbind();

    std::vector<Texture2D> textures(2);
    std::vector<String> paths {
        "res/textures/container.jpg",
        "res/textures/awesomeface.png"
    };
    for (SizeT i = 0; i < textures.size(); ++i) {
        textures[i]
            .bind()
               .param(GL_TEXTURE_WRAP_S, GL_REPEAT)
               .param(GL_TEXTURE_WRAP_T, GL_REPEAT)
               .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
               .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
               .load(Image(paths[i]))
               .genMipmap()
           .unbind();
    }

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (SizeT i = 0; i < textures.size(); ++i) {
            textures[i].active(i);
            program.uniform("tex" + std::to_string(i), i);
        }
        program.use();
        VAO.bind();
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        VAO.unbind();
    });

    glfwTerminate();
    return 0;
}
