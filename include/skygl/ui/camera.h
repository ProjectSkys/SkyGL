#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/calc/math.h>

#include <functional>

NS_SKY_GL_BEG

enum class Diretion {
    F, B, L, R, U, D
};

class Camera {
public:
    virtual ~Camera() {};
    virtual void update(double dt) = 0;
    virtual Mat4 getMatrix() = 0;
};

class FreeCamera: public Camera {
public:
    SKY_PROPERTY(Vec3, Eye)
    SKY_PROPERTY(Vec3, Look)
    SKY_PROPERTY(Vec3, Up)
    SKY_PROPERTY(Vec3, Velocity) // Forward, Left, Up
    SKY_PROPERTY(Vec3, Rotation) // Yaw, Pitch, Roll
public:
    FreeCamera()
        : Eye(0, 0, 0), Look(0, 0, -1), Up(0, 1, 0)
        , Velocity(0, 0, 0), Rotation(0, 0, 0) {}
    Vec3 getLeft() const {
        return glm::normalize(glm::cross(Up, Look));
    }
    void update(double dt) {
        float delta = static_cast<float>(dt);
        Vec3 vel = Velocity * delta;
        Vec3 rot = Rotation * delta;
        Eye += Look * vel.x;
        Eye += getLeft() * vel.y;
        Eye += Up * vel.z;
        Look = glm::rotate(Look, -rot.x, Up);
        Look = glm::rotate(Look, -rot.y, getLeft());
        Up = glm::normalize(glm::cross(Look, getLeft()));
        Up = glm::rotate(Up, -rot.z, Look);
    }
    Mat4 getMatrix() {
        return glm::lookAt(Eye, Eye + Look, Up);
    }
};
NS_SKY_GL_END
