#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "basic";
const String NAME = "coordinate";
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
        // Setup OpenGL options
        glEnable(GL_DEPTH_TEST);
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

    // Set up vertex data (and buffer(s)) and attribute pointers
    Float vertices[] {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // World space positions of our cubes
    Vec3 cubePositions[] {
        { 0.0f,  0.0f,   0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, - 2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, - 3.5f},
        {-1.7f,  3.0f, - 7.5f},
        { 1.3f, -2.0f, - 2.5f},
        { 1.5f,  2.0f, - 2.5f},
        { 1.5f,  0.2f, - 1.5f},
        {-1.3f,  1.0f, - 1.5f}
    };

    VertexArray VAO;
    ArrayBuffer VBO;

    SKY_BIND(VAO) {
        _.buffer(VBO).data(vertices);
        _.attrib(0).has<Float>(3).stride(SizeOf<5, Float>).offset(0);
        _.attrib(2).has<Float>(2).stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    }

    std::vector<Texture2D> textures(2);
    std::vector<String> paths {
        "res/textures/container.jpg",
        "res/textures/awesomeface.png"
    };
    for (SizeT i = 0; i < textures.size(); ++i) {
        textures[i].bind()
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (SizeT i = 0; i < textures.size(); ++i) {
            textures[i].active(i);
            shader.uniform("tex" + std::to_string(i), i);
        }

        shader.use();

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = glm::translate(Mat4(), Vec3(0.0f, 0.0f, -3.0f));

        shader.uniform("projection", projection);
        shader.uniform("view", view);

        SKY_BIND(VAO) {
            for (int i = 0; i < 10; i++) {
                Float angle = 20.0f * i;
                auto model = glm::translate(Mat4(), cubePositions[i]);
                model = glm::rotate(model, angle, Vec3(1.0f, 0.3f, 0.5f));
                shader.uniform("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    });

    glfwTerminate();
    return 0;
}
