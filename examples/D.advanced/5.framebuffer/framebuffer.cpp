#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "advanced";
const String NAME = "framebuffer";

UInt WIDTH = 800, HEIGHT = 600;

// Set up vertex data (and buffer(s)) and attribute pointers
Float cubeVertices[] {
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
std::vector<Vec3> cubePositions {
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

Float planeVertices[] {
    // Positions          // Texture Coords
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
};

Float quadVertices[] {
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};

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

    WalkCamera camera;
    camera.setEye({0, 0, 3});

    KeyManipulator keyman;
    MouseManipulator mouseman;

    window.created.connect([&window]() {
        if (!initGLEW()) {
            std::cout << "Failed to initialize GLEW" << std::endl;
        }
        if (!setupGL()) {
            std::cout << "Failed to setup OpenGL" << std::endl;
        }
        WIDTH = window.getWidth(), HEIGHT = window.getHeight();
        glViewport(0, 0, WIDTH, HEIGHT);
    });
    window.resized.connect([](int width, int height) {
        glViewport(0, 0, width, height);
    });
    window.keypressed.connect([&](Key key) {
        keyman.onKeyPressed(key);
        switch (key) {
            case GLFW_KEY_ESCAPE:
                window.close();
                break;
        }
    });
    window.keyreleased.connect([&](Key key) {
        keyman.onKeyReleased(key);
    });
    window.mousemoved.connect([&](double xpos, double ypos) {
        mouseman.onMouseMoved(xpos, ypos);
    });
    window.mousescrolled.connect([&](double xoff, double yoff) {
        mouseman.onMouseScrolled(xoff, yoff);
    });

    window.create();
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    VertexArray cube, plane, quad;
    ArrayBuffer bVBO, fVBO, qVBO;

    cube.bind();
        cube.buffer(bVBO)
            .data(cubeVertices, sizeof(cubeVertices));
        cube.attrib(0).has<Float>(3)
            .stride(SizeOf<5, Float>).offset(0);
        cube.attrib(1).has<Float>(2)
            .stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    cube.unbind();

    plane.bind();
        plane.buffer(fVBO)
             .data(planeVertices, sizeof(planeVertices));
        plane.attrib(0).has<Float>(3)
             .stride(SizeOf<5, Float>).offset(0);
        plane.attrib(1).has<Float>(2)
             .stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    plane.unbind();

    quad.bind();
        quad.buffer(qVBO)
            .data(quadVertices, sizeof(quadVertices));
        quad.attrib(0).has<Float>(2)
            .stride(SizeOf<4, Float>).offset(0);
        quad.attrib(1).has<Float>(2)
            .stride(SizeOf<4, Float>).offset(SizeOf<2, Float>);
    quad.unbind();

    FrameBuffer FBO;
    Texture2D fbt;
    RenderBuffer RBO;

    fbt.bind()
       .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
       .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
       .empty(WIDTH, HEIGHT, GL_RGB)
    .unbind();

    RBO.bind()
       .storage(WIDTH, HEIGHT, GL_DEPTH24_STENCIL8)
    .unbind();

    FBO.bind();
        FBO.attach(fbt, GL_COLOR_ATTACHMENT0);
        FBO.attach(RBO, GL_DEPTH_STENCIL_ATTACHMENT);
        if (FBO.status() != GL_FRAMEBUFFER_COMPLETE) {
            throw GLException("FBO::status", "status not complete");
        }
    FBO.unbind();

    Program scene(NAME + ".vs", NAME + ".frag");
    Program screen("screen.vs", "screen.frag");

    std::vector<Texture2D> textures(2);
    std::vector<String> paths {
        "res/textures/container.jpg",
        "res/textures/metal.png"
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
        static double last = glfwGetTime();
        double now = glfwGetTime();
        double dt = now - last;
        last = now;

        glfwPollEvents();

        Vec3 vel;
        vel.x += keyman[GLFW_KEY_W] - keyman[GLFW_KEY_S];
        vel.y += keyman[GLFW_KEY_A] - keyman[GLFW_KEY_D];
        vel.z += keyman[GLFW_KEY_Q] - keyman[GLFW_KEY_E];
        camera.setVelocity(vel);

        double yaw = mouseman.getDeltaX();
        double pitch = -mouseman.getDeltaY();
        camera.setRotation(0.15f * Vec3{yaw, pitch, 0});

        camera.update(dt);

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);

        // First Pass

        if (!keyman.toggled[GLFW_KEY_SPACE])
            FBO.bind();

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        scene.use();
        scene.uniform("projection", projection);
        scene.uniform("view", camera.getMatrix());

        textures[1].bind();
        plane.bind();
            scene.uniform("model", Mat4());
            glDrawArrays(GL_TRIANGLES, 0, 6);
        plane.unbind();

        textures[0].bind();
        cube.bind();
        for (SizeT i = 0; i < cubePositions.size(); i++) {
            Mat4 model = glm::translate(Mat4(), cubePositions[i]);
            scene.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        cube.unbind();

        if (!keyman.toggled[GLFW_KEY_SPACE])
            FBO.unbind();
        else
            return;

        // Second Pass

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        screen.use();
        screen.uniform("projection", projection);
        screen.uniform("view", camera.getMatrix());

        fbt.bind();
        quad.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);
        quad.unbind();
    });

    glfwTerminate();
    return 0;
}
