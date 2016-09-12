#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "model";
const String NAME = "load";
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

    std::vector<String> paths {
        "res/objects/nanosuit/nanosuit.obj",
        "res/objects/cyborg/cyborg.obj",
        "res/objects/rock/rock.obj",
        "res/objects/planet/planet.obj",
    };
    std::vector<Model> models(paths.size());
    for (SizeT i = 0; i < models.size(); ++i) {
        models[i].load(paths[i]);
    }

    std::vector<std::pair<Vec3, Vec3>> trans {
        {{0, -1.5, 0}, {0.2, 0.2, 0.2}},
        {{0, -1.2, 0}, {0.7, 0.7, 0.7}},
        {{0,    0, 0}, {0.5, 0.5, 0.5}},
        {{0, -0.5, 0}, {0.4, 0.4, 0.4}},
    };
    std::vector<Mat4> fixes(trans.size());
    for (SizeT i = 0; i < fixes.size(); ++i) {
        Mat4& fix = fixes[i];
        fix = glm::translate(fix, trans[i].first);
        fix = glm::scale(fix, trans[i].second);
    }

    window.loop([&]() {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
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

        shader.use();

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = camera.getMatrix();
        static Mat4 model;
        if (!keyman.toggled[GLFW_KEY_N]) {
            model = glm::rotate(model, 0.01f, {0, 1, 0});
        }

        int idx = keyman.count[GLFW_KEY_M] % models.size();

        shader.uniform("projection", projection);
        shader.uniform("view", view);
        shader.uniform("model", fixes[idx] * model);
        shader.uniform("select", keyman.count[GLFW_KEY_SPACE]);

        models[idx].draw(shader, 1, 2);
    });

    glfwTerminate();
    return 0;
}
