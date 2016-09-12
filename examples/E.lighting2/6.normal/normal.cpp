#include <iostream>
#include <vector>

#include "skygl.h"

using namespace sky::gl;

const String UNIT = "lighting2";
const String NAME = "normal";
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

    VertexArray cube;
    ArrayBuffer cVBO;
    SKY_BIND(cube) {
        _.buffer(cVBO).data(cubeVertices);
        _.attrib(0).has<Float>(3).stride(SizeOf<8, Float>).offset(0);
        _.attrib(1).has<Float>(3).stride(SizeOf<8, Float>).offset(SizeOf<3, Float>);
        _.attrib(2).has<Float>(2).stride(SizeOf<8, Float>).offset(SizeOf<6, Float>);
    }

    Vec3 pos1(-1.0, 1.0, 0.0);
    Vec3 pos2(-1.0, -1.0, 0.0);
    Vec3 pos3(1.0, -1.0, 0.0);
    Vec3 pos4(1.0, 1.0, 0.0);
    // texture coordinates
    Vec2 uv1(0.0, 1.0);
    Vec2 uv2(0.0, 0.0);
    Vec2 uv3(1.0, 0.0);
    Vec2 uv4(1.0, 1.0);
    // normal vector
    Vec3 nm(0.0, 0.0, 1.0);

    // calculate tangent/bitangent vectors of both triangles
    Vec3 tangent1, bitangent1;
    Vec3 tangent2, bitangent2;
    // - triangle 1
    Vec3 edge1 = pos2 - pos1;
    Vec3 edge2 = pos3 - pos1;
    Vec2 deltaUV1 = uv2 - uv1;
    Vec2 deltaUV2 = uv3 - uv1;

    Float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // - triangle 2
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);

    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);

    Vertex quadVertices[] {
        { pos1, nm, uv1, tangent1, bitangent1 },
        { pos2, nm, uv2, tangent1, bitangent1 },
        { pos3, nm, uv3, tangent1, bitangent1 },
        { pos1, nm, uv1, tangent2, bitangent2 },
        { pos3, nm, uv3, tangent2, bitangent2 },
        { pos4, nm, uv4, tangent2, bitangent2 },
    };

    VertexArray quad;
    ArrayBuffer qVBO;
    SKY_BIND(quad) {
        _.buffer(qVBO).data(quadVertices);
        SizeT total = sizeof(Vertex);
        _.attrib(0).has<Float>(3).stride(total).offset(offsetof(Vertex, position));
        _.attrib(1).has<Float>(3).stride(total).offset(offsetof(Vertex, normal));
        _.attrib(2).has<Float>(2).stride(total).offset(offsetof(Vertex, texCoords));
        _.attrib(3).has<Float>(3).stride(total).offset(offsetof(Vertex, tangent));
        _.attrib(4).has<Float>(3).stride(total).offset(offsetof(Vertex, bitangent));
    }

    Program shader(NAME + ".vs", NAME + ".frag");
    Program lamp("lamp.vs", "lamp.frag");

    std::vector<String> images {
        "res/textures/brickwall.jpg",
        "res/textures/brickwall_normal.jpg",
    };
    std::vector<Texture2D> textures(images.size());
    for (SizeT i = 0; i < textures.size(); ++i) {
        textures[i].bind()
           .param(GL_TEXTURE_WRAP_S, GL_REPEAT)
           .param(GL_TEXTURE_WRAP_T, GL_REPEAT)
           .param(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
           .param(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
           .load(Image(images[i]))
           .genMipmap()
       .unbind();
    }

    std::vector<String> objs {
        "res/objects/nanosuit/nanosuit.obj",
        "res/objects/cyborg/cyborg.obj",
    };
    std::vector<Model> models(objs.size());
    for (SizeT i = 0; i < models.size(); ++i) {
        models[i].load(objs[i]);
    }

    std::vector<std::pair<Vec3, Vec3>> trans {
        {{0, -1.5, 0}, {0.2, 0.2, 0.2}},
        {{0, -1.2, 0}, {0.7, 0.7, 0.7}},
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

        static Vec3 lightPos {2, 1, 0};
        static Vec3 lightColor {1, 1, 1};
        if (!keyman.toggled[GLFW_KEY_M]) lightPos = glm::rotateY(lightPos, 0.02f);

        auto projection = glm::perspective(45.0f, window.getAspect(), 0.1f, 100.0f);
        auto view = camera.getMatrix();

        static Mat4 model;
        if (keyman.toggled[GLFW_KEY_R]) model = Mat4();
        if (keyman.toggled[GLFW_KEY_X]) model = glm::rotate(model, 0.01f, {1, 0, 0});
        if (keyman.toggled[GLFW_KEY_Y]) model = glm::rotate(model, 0.01f, {0, 1, 0});
        if (keyman.toggled[GLFW_KEY_Z]) model = glm::rotate(model, 0.01f, {0, 0, 0});

        shader.use();
        shader.uniform("projection", projection);
        shader.uniform("view", view);
        shader.uniform("model", model);
        shader.uniform("lightPos", lightPos);
        shader.uniform("viewPos", camera.getEye());
        shader.uniform("normalMapping", !keyman.toggled[GLFW_KEY_P]);

        int idx = keyman.count[GLFW_KEY_SPACE] % (models.size() + 1);
        if (idx == 0) {
            shader.uniform("textures[0].diffuse", 0);
            shader.uniform("textures[0].height", 1);
            textures[0].active(0);
            textures[1].active(1);
            SKY_BIND(quad) {
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        } else {
            shader.uniform("model", fixes[idx - 1] * model);
            models[idx - 1].draw(shader);
        }

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
