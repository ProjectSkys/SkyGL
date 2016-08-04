#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/error.h>
#include <skygl/utils.h>
#include <skygl/gl.h>
#include <skygl/math.h>

#include <string>
#include <iostream>

NS_SKY_GL_BEG

class Shader {
private:
    UInt _program;
public:
    Shader(KStringRef vertexPath, KStringRef fragmentPath, KStringRef geometryPath = "") {
        _compile(vertexPath, fragmentPath, geometryPath);
    }
    UInt getID() const {
        return _program;
    }
    const Shader& use() const {
        glUseProgram(_program);
        return *this;
    }
    const Shader& uniform(KStringRef name, Int value) const {
        UInt loc = glGetUniformLocation(_program, name.c_str());
        glUniform1i(loc, value);
        return *this;
    }
    const Shader& uniform(KStringRef name, const Mat4& value) const {
        UInt loc = glGetUniformLocation(_program, name.c_str());
        glUniformMatrix4fv(loc, 1, False, glm::value_ptr(value));
        return *this;
    }
private:
    void _compile(KStringRef vertexPath, KStringRef fragmentPath, KStringRef geometryPath = "") {
        // 1. Retrieve the vertex/fragment source code from filePath
        String vertexCode, fragmentCode, geometryCode;
        vertexCode = readFileFromPath(vertexPath);
        fragmentCode = readFileFromPath(fragmentPath);
        if (!geometryPath.empty()) {
            geometryCode = readFileFromPath(geometryPath);
        }
        // 2. Compile shaders
        UInt vertex, fragment, geometry;
        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        KCharPtr vShaderCode = vertexCode.c_str();
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        _checkCompileErrors(vertex, "vertex");
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        KCharPtr fShaderCode = fragmentCode.c_str();
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        _checkCompileErrors(fragment, "fragment");
        // If geometry shader is given, compile geometry shader
        if (!geometryPath.empty()) {
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            KCharPtr gShaderCode = geometryCode.c_str();
            glShaderSource(geometry, 1, &gShaderCode, nullptr);
            glCompileShader(geometry);
            _checkCompileErrors(geometry, "geometry");
        }
        // Shader Program
        _program = glCreateProgram();
        glAttachShader(_program, vertex);
        glAttachShader(_program, fragment);
        if (!geometryPath.empty()) {
            glAttachShader(_program, geometry);
        }
        glLinkProgram(_program);
        _checkCompileErrors(_program, "program");
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (!geometryPath.empty()) {
            glDeleteShader(geometry);
        }
    }
    void _checkCompileErrors(UInt shader, KStringRef type) const {
        Int success;
        Char infoLog[1024];
        if (type != "program") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                throw GLException(type, infoLog);
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                throw GLException(type, infoLog);
            }
        }
    }
};

NS_SKY_GL_END
