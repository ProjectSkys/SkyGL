#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "lighting2";
const String NAME = "gamma";
const UInt WIDTH = 800, HEIGHT = 600;

Float cubeVertices[] {
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

Vec3 cubePositions[] {
    {  0.0f,  0.0f,   0.0f },
    {  2.0f,  5.0f, -15.0f },
    { -1.5f, -2.2f, - 2.5f },
    { -3.8f, -2.0f, -12.3f },
    {  2.4f, -0.4f, - 3.5f },
    { -1.7f,  3.0f, - 7.5f },
    {  1.3f, -2.0f, - 2.5f },
    {  1.5f,  2.0f, - 2.5f },
    {  1.5f,  0.2f, - 1.5f },
    { -1.3f,  1.0f, - 1.5f }
};

Float planeVertices[] {
    // Positions          // Normals         // Texture Coords
     8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
    -8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,

     8.0f, -0.5f,  8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 0.0f,
    -8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  0.0f, 5.0f,
     8.0f, -0.5f, -8.0f,  0.0f, 1.0f, 0.0f,  5.0f, 5.0f
};

struct Light {
    Vec3 position;
    Vec3 color;
};

std::vector<Light> lights {
    {{-3.0f, 1.0f, 0.0f}, Vec3{0.25f}},
    {{-1.0f, 1.0f, 0.0f}, Vec3{0.50f}},
    {{ 1.0f, 1.0f, 0.0f}, Vec3{0.75f}},
    {{ 3.0f, 1.0f, 0.0f}, Vec3{1.00f}},
};

bool initGLFW() {
    glfwInit();
    Window::hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    Window::hint(GLFW_CONTEXT_VERSION_MINOR, 3);
    Window::hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Window::hint(GLFW_RESIZABLE, GL_TRUE);
    Window::hint(GLFW_SAMPLES, 4);
    return true;
}

bool initGLEW() {
    glewExperimental = GL_TRUE;
    return glewInit() == GLEW_OK;
}

bool setupGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    return true;
}

int main() {
    if (!initGLFW()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    Window window(WIDTH, HEIGHT, UNIT + "/" + NAME);

    WalkCamera camera;
    camera.setEye({0, 0, 6});

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

    Program light(NAME + ".vs", NAME + ".frag");
    Program lamp("lamp.vs", "lamp.frag");

    VertexArray cube, plane;
    ArrayBuffer cVBO, pVBO;

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

    plane.bind();
        plane.buffer(pVBO)
             .data(planeVertices, sizeof(planeVertices));
        plane.attrib(0).has<Float>(3)
             .stride(SizeOf<8, Float>).offset(0);
        plane.attrib(1).has<Float>(3)
             .stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        plane.attrib(2).has<Float>(2)
             .stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    plane.unbind();

    std::vector<std::tuple<String, bool, bool>> images {
        { "res/textures/wood.png",                false, true  },
        { "res/textures/wood_specular.png",       false, false },
        { "res/textures/container2.png",          false, true  },
        { "res/textures/container2_specular.png", false, false },
    };
    std::vector<Texture2D> textures(images.size());
    for (SizeT i = 0; i < textures.size(); ++i) {
        String path;
        bool alpha, gamma;
        std::tie(path, alpha, gamma) = images[i];
        textures[i].bind()
           .param(GL_TEXTURE_WRAP_S, GL_REPEAT)
           .param(GL_TEXTURE_WRAP_T, GL_REPEAT)
           .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
           .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
           .load(Image(path, alpha, gamma))
           .genMipmap()
       .unbind();
    }

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
        double roll = mouseman.getScrollY() * 20;
        camera.setRotation(0.15f * Vec3{yaw, pitch, roll});

        camera.update(dt);

        if (keyman.toggled[GLFW_KEY_M]) {
            for (auto& l : lights) {
                l.position = glm::rotateY(l.position, 0.02f);
            }
        }

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = camera.getMatrix();

        light.use();

        light.uniform("lightNum", lights.size());
        for (SizeT i = 0; i < lights.size(); ++i) {
            auto& l = lights[i];
            Vec3 diffuseColor = l.color * Vec3(0.5f);
            Vec3 ambientColor = diffuseColor * Vec3(0.2f);
            String name = "lights[" + std::to_string(i) + "]";
            light.uniform(name + ".position", l.position);
            light.uniform(name + ".ambient", ambientColor);
            light.uniform(name + ".diffuse", diffuseColor);
            light.uniform(name + ".specular", {1, 1, 1});
        }
        light.uniform("material.ambient", 0);
        light.uniform("material.diffuse", 0);
        light.uniform("material.specular", 1);
        light.uniform("material.shininess", 16.0f);

        light.uniform("projection", projection);
        light.uniform("view", view);
        light.uniform("viewPos", camera.getEye());
        light.uniform("blinn", !keyman.toggled[GLFW_KEY_B]);
        light.uniform("gamma", !keyman.toggled[GLFW_KEY_G]);

        textures[0].active(0);
        textures[0].active(1);
        plane.bind();
            light.uniform("model", Mat4());
            glDrawArrays(GL_TRIANGLES, 0, 6);
        plane.unbind();

        if (keyman.toggled[GLFW_KEY_SPACE]) {
            textures[2].active(0);
            textures[3].active(1);
            cube.bind();
            for (int i = 0; i < 10; i++) {
                Float angle = 20.0f * i;
                Mat4 model;
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, angle, {1.0f, 0.3f, 0.5f});
                light.uniform("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            cube.unbind();
        }

        lamp.use();
        lamp.uniform("projection", projection);
        lamp.uniform("view", view);
        cube.bind();
        for (auto& l : lights) {
            Mat4 model;
            model = glm::translate(model, l.position);
            model = glm::scale(model, {0.2, 0.2, 0.2});
            lamp.uniform("model", model);
            lamp.uniform("lightColor", l.color);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        cube.unbind();

    });

    glfwTerminate();
    return 0;
}
