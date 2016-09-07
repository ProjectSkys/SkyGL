#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "advanced";
const String NAME = "instance";
const UInt WIDTH = 800, HEIGHT = 600;

const int TOTAL_AMOUNT = 100000;
const int STEP_AMOUNT = 5000;
const int INIT_AMOUNT = 10000;
int amount = INIT_AMOUNT;

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
    glEnable(GL_CULL_FACE);
    return true;
}

int main() {
    if (!initGLFW()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    Window window(WIDTH, HEIGHT, UNIT + "/" + NAME);

    FreeCamera camera;
    camera.setEye({0, 100, 155});
    camera.setLook({0, -1, -1});

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
            case GLFW_KEY_MINUS:
                amount -= STEP_AMOUNT;
                amount = std::max(amount, 0);
                break;
            case GLFW_KEY_EQUAL:
                amount += STEP_AMOUNT;
                amount = std::min(amount, TOTAL_AMOUNT);
                break;
        }
        std::cout << "amount: " << amount << std::endl;
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

    Program instanceShader(NAME + ".vs", NAME + ".frag");
    Program planetShader("planet.vs", "planet.frag");

    Model rock("res/objects/rock/rock.obj");
    Model planet("res/objects/planet/planet.obj");

    std::vector<Mat4> modelMatrices(TOTAL_AMOUNT);
    srand(glfwGetTime()); // initialize random seed
    Float radius = 80.0f;
    Float offset = 25.0f;
    for (SizeT i = 0; i < TOTAL_AMOUNT; i++) {
        Mat4& model = modelMatrices[i];
        // 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
        Float angle = (Float)i / (Float)TOTAL_AMOUNT * 360.0f;
        Float displacement = (rand() % (Int)(2 * offset * 100)) / 100.0f - offset;
        Float x = sin(angle) * radius + displacement;
        displacement = (rand() % (Int)(2 * offset * 100)) / 100.0f - offset;
        Float y = -2.5f + displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (Int)(2 * offset * 100)) / 100.0f - offset;
        Float z = cos(angle) * radius + displacement;
        model = glm::translate(model, {x, y, z});
        // 2. Scale: Scale between 0.05 and 0.25f
        Float scale = (rand() % 20) / 100.0f + 0.05;
        model = glm::scale(model, Vec3(scale));
        // 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
        Float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, {0.4f, 0.6f, 0.8f});
    }

    std::vector<std::shared_ptr<ArrayBuffer>> pVBOs;

    rock.setupVAO([&](const VertexArray& VAO) {
        auto pVBO = std::make_shared<ArrayBuffer>();
        pVBOs.push_back(pVBO);
        VAO.buffer(*pVBO).data(&modelMatrices[0], TOTAL_AMOUNT * sizeof(Mat4));
        VAO.attrib(3).divisor(1).has<Float>(4).stride(sizeof(Mat4)).offset(0);
        VAO.attrib(4).divisor(1).has<Float>(4).stride(sizeof(Mat4)).offset(SizeOf<1, Vec4>);
        VAO.attrib(5).divisor(1).has<Float>(4).stride(sizeof(Mat4)).offset(SizeOf<2, Vec4>);
        VAO.attrib(6).divisor(1).has<Float>(4).stride(sizeof(Mat4)).offset(SizeOf<3, Vec4>);
    });

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
        camera.setVelocity(10.f * vel);

        double yaw = mouseman.getDeltaX();
        double pitch = -mouseman.getDeltaY();
        double roll = mouseman.getScrollY() * 20;
        camera.setRotation(0.1f * Vec3{yaw, pitch, roll});

        camera.update(dt);

        auto projection = glm::infinitePerspective(45.0f, window.getAspect(), 0.1f);
        auto view = camera.getMatrix();

        planetShader.use();
        planetShader.uniform("projection", projection);
        planetShader.uniform("view", view);
        Mat4 model;
        model = glm::translate(model, {0.0f, -5.0f, 0.0f});
        model = glm::scale(model, {4.0f, 4.0f, 4.0f});
        planetShader.uniform("model", model);
        planet.draw(planetShader);

        instanceShader.use();
        instanceShader.uniform("projection", projection);
        planetShader.uniform("view", view);
        rock.draw(instanceShader, amount);

    });

    glfwTerminate();
    return 0;
}
