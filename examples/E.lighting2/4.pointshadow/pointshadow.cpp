#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "lighting2";
const String NAME = "pointshadow";
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

Float icubeVertices[] {
    // Positions          // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f
};

std::vector<Vec3> cubePositions {
    { 4.0f, -3.5f,  0.0},
    { 2.0f,  3.0f,  1.0},
    {-3.0f, -1.0f,  0.0},
    {-1.5f,  1.0f,  1.5},
    {-1.5f,  2.0f, -3.0},
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

    VertexArray cube;
    ArrayBuffer cVBO;
    SKY_BIND(cube) {
        _.buffer(cVBO).data(cubeVertices);
        _.attrib(0).has<Float>(3).stride(SizeOf<8, Float>).offset(0);
        _.attrib(1).has<Float>(3).stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        _.attrib(2).has<Float>(2).stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    }

    VertexArray icube;
    ArrayBuffer iVBO;
    SKY_BIND(icube) {
        _.buffer(iVBO).data(icubeVertices);
        _.attrib(0).has<Float>(3).stride(SizeOf<8, Float>).offset(0);
        _.attrib(1).has<Float>(3).stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        _.attrib(2).has<Float>(2).stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    }

    const UInt SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    Float borderColor[] {1.0f, 1.0f, 1.0f, 1.0f};
    FrameBuffer FBO;
    TextureCubeMap depthMap;
    SKY_BIND(depthMap) {
        _.param(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
         .param(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
         .param(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
         .param(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
         .param(GL_TEXTURE_BORDER_COLOR, borderColor);
        for (UInt i = 0; i < 6; ++i) {
            Enum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
            _.empty(SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, target);
        }
    }
    SKY_BIND(FBO) {
        _.attach(depthMap, GL_DEPTH_ATTACHMENT);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        if (FBO.status() != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "Framebuffer not complete!" << std::endl;
        }
    }

    std::vector<std::tuple<String, bool, bool>> images {
        std::make_tuple("res/textures/container2.png",          false, false),
        std::make_tuple("res/textures/container2_specular.png", false, false),
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

    Program scene(NAME + ".vs", NAME + ".frag");
    Program lamp("lamp.vs", "lamp.frag");
    Program depth("pdepth.vs", "pdepth.frag", "pdepth.gs");

    Vec3 lightPos {0, 0, 0};
    Vec3 lightColor {1, 1, 1};
    Vec3 diffuseColor = lightColor * Vec3(0.5f);
    Vec3 ambientColor = diffuseColor * Vec3(0.3f);

    auto drawScene = [&](const Program& scene) {
        textures[0].active(0);
        textures[1].active(1);
        SKY_BIND(icube) {
            Mat4 model = glm::scale(Mat4(), Vec3(10.0));
            scene.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        SKY_BIND(cube) {
            for (SizeT i = 0; i < cubePositions.size(); i++) {
                Float angle = 20.0f * i;
                Mat4 model;
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, angle, {1.0f, 0.3f, 0.5f});
                scene.uniform("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    };

    glClearColor(0, 0, 0, 1);

    window.loop([&]() {
        glfwPollEvents();

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

        // if (keyman.toggled[GLFW_KEY_M]) {
        //     lightPos = glm::rotateY(lightPos, 0.02f);
        // }

        Float aspect = (Float)SHADOW_WIDTH / SHADOW_HEIGHT;
        Float near = 1.0f, far = 25.0f;
        auto shadowProj = glm::perspective(90.0f, aspect, near, far);
        auto M = [&](KVec3Ref dir, KVec3Ref up) {
            return shadowProj * glm::lookAt(lightPos, lightPos + dir, up);
        };
        std::vector<Mat4> shadowTransforms {
            M({ 1.0,  0.0,  0.0}, {0.0, -1.0,  0.0}),
            M({-1.0,  0.0,  0.0}, {0.0, -1.0,  0.0}),
            M({ 0.0,  1.0,  0.0}, {0.0,  0.0,  1.0}),
            M({ 0.0, -1.0,  0.0}, {0.0,  0.0, -1.0}),
            M({ 0.0,  0.0,  1.0}, {0.0, -1.0,  0.0}),
            M({ 0.0,  0.0, -1.0}, {0.0, -1.0,  0.0}),
        };

        SKY_BIND(FBO) {
            depth.use();
            depth.uniform("shadowTransforms", shadowTransforms);
            depth.uniform("lightPos", lightPos);
            depth.uniform("far_plane", far);

            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glClear(GL_DEPTH_BUFFER_BIT);
            drawScene(depth);
        }

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = camera.getMatrix();

        scene.use();
        scene.uniform("projection", projection);
        scene.uniform("view", view);

        scene.uniform("light.ambient", ambientColor);
        scene.uniform("light.diffuse", diffuseColor);
        scene.uniform("light.specular", {1, 1, 1});
        scene.uniform("light.position", lightPos);
        scene.uniform("material.ambient", 0);
        scene.uniform("material.diffuse", 0);
        scene.uniform("material.specular", 1);
        scene.uniform("material.shininess", 16.0f);

        scene.uniform("depthMap", 2);
        scene.uniform("viewPos", camera.getEye());
        scene.uniform("far_plane", far);
        scene.uniform("shadows", !keyman.toggled[GLFW_KEY_O]);
        scene.uniform("debug", keyman.toggled[GLFW_KEY_B]);

        glViewport(0, 0, window.getWidth(), window.getHeight());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        depthMap.active(2);
        drawScene(scene);

        lamp.use();
        lamp.uniform("projection", projection);
        lamp.uniform("view", view);
        lamp.uniform("lightColor", lightColor);
        lamp.use();
        SKY_BIND(cube) {
            Mat4 model;
            model = glm::translate(model, lightPos);
            model = glm::scale(model, {0.05, 0.05, 0.05});
            lamp.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    });

    glfwTerminate();
    return 0;
}

