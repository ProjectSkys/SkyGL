#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "advanced";
const String NAME = "cubemap";
const UInt WIDTH = 800, HEIGHT = 600;

GLfloat cubeVertices[] {
    // Positions          // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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

Float skyboxVertices[] {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
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

    Program shader(NAME + ".vs", NAME + ".frag");
    Program skybox("skybox.vs", "skybox.frag");

    VertexArray cube, box;
    ArrayBuffer cVBO, sVBO;

    cube.bind();
        cube.buffer(cVBO)
            .data(cubeVertices, sizeof(cubeVertices));
        cube.attrib(0).has<Float>(3)
            .stride(SizeOf<8, Float>).offset(0);
        cube.attrib(1).has<Float>(3)
            .stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        cube.attrib(2).has<Float>(2)
            .stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    cube.unbind();

    box.bind();
        box.buffer(sVBO)
           .data(skyboxVertices, sizeof(skyboxVertices));
        box.attrib(0).has<Float>(3)
           .stride(SizeOf<3, Float>).offset(0);
    box.unbind();

    TextureCubeMap sky;
    std::vector<String> skyboxPaths {
        "res/textures/skybox/right.jpg",
        "res/textures/skybox/left.jpg",
        "res/textures/skybox/top.jpg",
        "res/textures/skybox/bottom.jpg",
        "res/textures/skybox/back.jpg",
        "res/textures/skybox/front.jpg",
    };
    sky.bind()
       .param(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
       .param(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
       .param(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE)
       .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
       .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    for (SizeT i = 0; i < skyboxPaths.size(); ++i) {
        sky.load(Image(skyboxPaths[i]), GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
    }
    sky.unbind();

    std::vector<String> paths {
        "res/textures/container.jpg",
    };
    std::vector<Texture2D> textures(paths.size());
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

    Model ourModel("res/objects/nanosuit/nanosuit.obj");

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        static double last = glfwGetTime();
        double now = glfwGetTime();
        double dt = now - last;
        last = now;

        Vec3 vel;
        vel.x += keyman[GLFW_KEY_W] - keyman[GLFW_KEY_S];
        vel.y += keyman[GLFW_KEY_A] - keyman[GLFW_KEY_D];
        vel.z += keyman[GLFW_KEY_Q] - keyman[GLFW_KEY_E];
        camera.setVelocity(vel);

        double yaw = mouseman.getDeltaX();
        double pitch = -mouseman.getDeltaY();
        camera.setRotation(0.15f * Vec3{yaw, pitch, 0});

        camera.update(dt);

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 1000.0f);

        shader.use();
        shader.uniform("projection", projection);
        shader.uniform("view", camera.getMatrix());
        shader.uniform("cameraPos", camera.getEye());
        shader.uniform("effect", keyman.count[GLFW_KEY_V]);
        shader.uniform("skybox", 0);

        sky.active(0);
        if (keyman.toggled[GLFW_KEY_SPACE]) {
            Mat4 model;
            model = glm::translate(model, {0.0f, -1.75f, 0.0f});
            model = glm::scale(model, {0.2f, 0.2f, 0.2f});
            shader.uniform("model", model);
            ourModel.draw(shader, 1);
        } else {
            shader.uniform("texture_diffuse0", 1);
            textures[0].active(1);
            cube.bind();
            for (SizeT i = 0; i < cubePositions.size(); i++) {
                Float angle = 20.0f * i;
                Mat4 model;
                model = glm::translate(Mat4(), cubePositions[i]);
                model = glm::rotate(model, angle, Vec3(1.0f, 0.3f, 0.5f));
                shader.uniform("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            cube.unbind();
        }

        glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content

        skybox.use();
        skybox.uniform("projection", projection);
        skybox.uniform("view", camera.getMatrix());
        skybox.uniform("model", glm::scale(Mat4(), Vec3(100)));
        skybox.uniform("skybox", 0);

        sky.active(0);
        box.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        box.unbind();

        glDepthFunc(GL_LESS); // Set depth function back to default

    });

    glfwTerminate();
    return 0;
}
