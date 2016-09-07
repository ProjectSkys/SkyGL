#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "lighting2";
const String NAME = "shadowmap";
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

Float quadVertices[] {
    // Positions        // Texture Coords
    -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
     1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
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

    VertexArray plane;
    ArrayBuffer pVBO;
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

    VertexArray quad;
    ArrayBuffer qVBO;
    quad.bind();
        quad.buffer(qVBO).data(quadVertices, sizeof(quadVertices));
        quad.attrib(0).has<Float>(3).stride(SizeOf<5, Float>).offset(0);
        quad.attrib(1).has<Float>(2).stride(SizeOf<5, Float>).offset(SizeOf<3, Float>);
    quad.unbind();

    const UInt SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    Float borderColor[] {1.0f, 1.0f, 1.0f, 1.0f};
    FrameBuffer FBO;
    Texture2D depthMap;
    depthMap.bind()
       .param(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER)
       .param(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER)
       .param(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
       .param(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
       .param(GL_TEXTURE_BORDER_COLOR, borderColor)
       .empty(SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_FLOAT)
    .unbind();
    FBO.bind();
        FBO.attach(depthMap, GL_DEPTH_ATTACHMENT);
    FBO.unbind();

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

    Program scene(NAME + ".vs", NAME + ".frag");
    Program lamp("lamp.vs", "lamp.frag");
    Program depth("depth.vs", "depth.frag");
    Program debug("debug.vs", "debug.frag");

    Vec3 lightPos {-2, 4, -1};
    Vec3 lightColor {1, 1, 1};
    Vec3 diffuseColor = lightColor * Vec3(0.5f);
    Vec3 ambientColor = diffuseColor * Vec3(0.3f);

    auto drawScene = [&](const Program& scene) {
        scene.use();
        textures[0].active(0);
        textures[1].active(1);
        plane.bind();
            scene.uniform("model", Mat4());
            glDrawArrays(GL_TRIANGLES, 0, 6);
        plane.unbind();
        if (!keyman.toggled[GLFW_KEY_SPACE]) {
            textures[2].active(0);
            textures[3].active(1);
            cube.bind();
            for (int i = 0; i < 10; i++) {
                Float angle = 20.0f * i;
                Mat4 model;
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, angle, {1.0f, 0.3f, 0.5f});
                scene.uniform("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            cube.unbind();
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

        if (keyman.toggled[GLFW_KEY_M]) {
            lightPos = glm::rotateY(lightPos, 0.02f);
        }

        Float near_plane = 0.1f, far_plane = 10.5f;
        auto lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        // lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / SHADOW_HEIGHT, near_plane, far_plane);
        // Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
        auto lightView = glm::lookAt(lightPos, {0, 0, 0}, {0.0, 1.0, 0.0});
        auto lightSpaceMatrix = lightProjection * lightView;

        depth.use();
        depth.uniform("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        FBO.bind();
            glClear(GL_DEPTH_BUFFER_BIT);
            drawScene(depth);
        FBO.unbind();

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = camera.getMatrix();

        scene.use();
        scene.uniform("projection", projection);
        scene.uniform("view", view);
        scene.uniform("lightSpaceMatrix", lightSpaceMatrix);

        scene.uniform("light.ambient", ambientColor);
        scene.uniform("light.diffuse", diffuseColor);
        scene.uniform("light.specular", {1, 1, 1});
        scene.uniform("light.position", lightPos);
        scene.uniform("material.ambient", 0);
        scene.uniform("material.diffuse", 0);
        scene.uniform("material.specular", 1);
        scene.uniform("material.shininess", 16.0f);

        scene.uniform("shadowMap", 2);
        scene.uniform("viewPos", camera.getEye());
        scene.uniform("blinn", !keyman.toggled[GLFW_KEY_B]);
        scene.uniform("gamma", !keyman.toggled[GLFW_KEY_G]);
        scene.uniform("shadows", !keyman.toggled[GLFW_KEY_O]);

        glViewport(0, 0, window.getWidth(), window.getHeight());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        depthMap.active(2);
        drawScene(scene);

        lamp.use();
        lamp.uniform("projection", projection);
        lamp.uniform("view", view);
        lamp.uniform("lightColor", lightColor);
        lamp.use();
        cube.bind();
            Mat4 model;
            model = glm::translate(model, lightPos);
            model = glm::scale(model, {0.2, 0.2, 0.2});
            lamp.uniform("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        cube.unbind();

        if (keyman.toggled[GLFW_KEY_B]) {
            debug.use();
            debug.uniform("depthMap", 0);
            debug.uniform("near_plane", near_plane);
            debug.uniform("far_plane", far_plane);
            depthMap.active(0);
            quad.bind();
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            quad.unbind();
        }
    });

    glfwTerminate();
    return 0;
}

