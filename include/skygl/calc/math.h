#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>

NS_SKY_GL_BEG

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;

using Mat3 = glm::mat3;
using Mat4 = glm::mat4;

using KVec2Ref = const Vec2&;
using KVec3Ref = const Vec3&;
using KVec4Ref = const Vec4&;

using KMat3Ref = const Mat3&;
using KMat4Ref = const Mat4&;

NS_SKY_GL_END
