#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "advanced";
const String NAME = "culling";
const UInt WIDTH = 800, HEIGHT = 600;

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

Float planeVertices[] {
    // Positions          // Texture Coords
    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

    5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
    -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
    5.0f,  -0.5f, -5.0f,  2.0f, 2.0f
};

Float transparentVertices[] {
    // Positions         // Texture Coords
    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

    0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
    1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
    1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

std::vector<Vec3> grassPositions {
    {-1.5f,  0.0f, -0.48f},
    { 1.5f,  0.0f,  0.51f},
    { 0.0f,  0.0f,  0.7f},
    {-0.3f,  0.0f, -2.3f},
    { 0.5f,  0.0f, -0.6f}
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
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

int main() {
    if (!initGLFW()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    Window window(WIDTH, HEIGHT, UNIT + "/" + NAME);

    FreeCamera camera;
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
        UInt width = window.getWidth(), height = window.getHeight();
        glViewport(0, 0, width, height);
    });
    window.resized.connect([](int width, int height) {
        glViewport(0, 0, width, height);
    });
    window.keypressed.connect([&](Key key) {
        std::cout << "Key: " << key << " " << key.code << std::endl;
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

    Program program(NAME + ".vs", NAME + ".frag");
    Program single(NAME + ".vs", "single.frag");

    VertexArray box, floor, board;
    ArrayBuffer bVBO, fVBO, oVBO;

    box.bind();
        box.buffer(bVBO)
           .data(cubeVertices, sizeof(cubeVertices));
        box.attrib(0).has<Float>(3)
           .stride(SizeOf<5, Float>).offset(0);
        box.attrib(1).has<Float>(2)
           .stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    box.unbind();
    floor.bind();
        floor.buffer(fVBO)
             .data(planeVertices, sizeof(planeVertices));
        floor.attrib(0).has<Float>(3)
             .stride(SizeOf<5, Float>).offset(0);
        floor.attrib(1).has<Float>(2)
             .stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    floor.unbind();
    board.bind();
        board.buffer(oVBO)
             .data(transparentVertices, sizeof(transparentVertices));
        board.attrib(0).has<Float>(3)
             .stride(SizeOf<5, Float>).offset(0);
        board.attrib(1).has<Float>(2)
             .stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    board.unbind();

    std::vector<std::pair<String, Bool>> images {
        {"res/textures/marble.jpg", false},
        {"res/textures/metal.png", false},
        {"res/textures/grass.png", true},
        {"res/textures/window.png", true}
    };
    std::vector<Texture2D> textures(images.size());
    for (SizeT i = 0; i < images.size(); ++i) {
        String path = images[i].first;
        Bool alpha = images[i].second;
        Enum wrap = alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT;
        textures[i]
            .bind()
               .param(GL_TEXTURE_WRAP_S, wrap)
               .param(GL_TEXTURE_WRAP_T, wrap)
               .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
               .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
               .load(Image(path, alpha))
               .genMipmap()
           .unbind();
    }

    window.loop([&]() {
        static double last = glfwGetTime();
        double now = glfwGetTime();
        double dt = now - last;
        last = now;

        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Vec3 vel;
        vel.x += keyman[GLFW_KEY_W] - keyman[GLFW_KEY_S];
        vel.y += keyman[GLFW_KEY_A] - keyman[GLFW_KEY_D];
        vel.z += keyman[GLFW_KEY_Q] - keyman[GLFW_KEY_E];
        camera.setVelocity(vel);

        double yaw = mouseman.getDeltaX();
        double pitch = -mouseman.getDeltaY();
        double roll = mouseman.getScrollY() * 20;
        camera.setRotation(0.15f * Vec3{yaw, pitch, roll});

        camera.update(dt);

        if (keyman.toggled[GLFW_KEY_C]) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);

        program.use();
        program.uniform("tex", 0);
        program.uniform("projection", projection);
        program.uniform("view", camera.getMatrix());

        textures[0].active(0);
        floor.bind();
        {
            program.uniform("model", Mat4());
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        floor.unbind();

        textures[1].active(0);
        box.bind();
        for (int i = 0; i < 10; i++) {
            Mat4 model = glm::translate(Mat4(), cubePositions[i]);
            program.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        box.unbind();

        auto eye = camera.getEye();
        std::sort(grassPositions.begin(), grassPositions.end(), [&eye](KVec3Ref a, KVec3Ref b) {
            auto da = glm::length(eye - a);
            auto db = glm::length(eye - b);
            return da > db;
        });

        textures[2 + keyman.toggled[GLFW_KEY_SPACE]].active(0);
        board.bind();
        for (SizeT i = 0; i < grassPositions.size(); i++) {
            Mat4 model = glm::translate(Mat4(), grassPositions[i]);
            program.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        board.unbind();

    });

    glfwTerminate();
    return 0;
}
