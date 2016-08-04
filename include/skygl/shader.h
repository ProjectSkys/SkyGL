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

class Program;

template <Enum ShaderType>
class Shader {
private:
    UInt _id;
    Bool _compiled;
public:
    Shader()
        : _id(glCreateShader(ShaderType))
        , _compiled(False) {}
    Shader(KStringRef path): Shader() {
        source(readFileFromPath(path));
        compile();
    }
    ~Shader() {
        glDeleteShader(_id);
    }
    UInt getId() const {
        return _id;
    }
    Bool compiled() const {
        return _compiled;
    }
    Shader& source(String code) {
        KCharPtr source = code.c_str();
        glShaderSource(_id, 1, &source, nullptr);
        return *this;
    }
    void compile() {
        glCompileShader(_id);
        _checkCompileErrors();
        _compiled = True;
    }
private:
    void _checkCompileErrors() {
        Int success;
        Char infoLog[1024];
        glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(_id, 1024, nullptr, infoLog);
            throw GLException(std::to_string(ShaderType), infoLog);
        }
    }
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
using GeometryShader = Shader<GL_GEOMETRY_SHADER>;

class Program: boost::noncopyable {
private:
    UInt _id;
    Bool _linked;
public:
    Program()
        : _id(glCreateProgram())
        , _linked(False) {}
    Program(KStringRef vertexPath, KStringRef fragmentPath): Program() {
        VertexShader vertex(vertexPath);
        FragmentShader fragment(fragmentPath);
        attach(vertex);
        attach(fragment);
        link();
    }
    Program(KStringRef vertexPath, KStringRef fragmentPath, KStringRef geometryPath): Program() {
        VertexShader vertex(vertexPath);
        FragmentShader fragment(fragmentPath);
        GeometryShader geometry(geometryPath);
        attach(vertex);
        attach(fragment);
        attach(geometry);
        link();
    }
    Program(Program&& prog) {
        _id = prog._id;
        prog._id = 0;
    }
    ~Program() {
    }
    Program& operator = (Program&& prog) {
        _id = prog._id;
        prog._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    Bool linked() const {
        return _linked;
    }
    template <Enum T>
    Program& attach(const Shader<T>& shader) {
        if (shader.compiled()) {
            glAttachShader(_id, shader.getId());
        }
        return *this;
    }
    void link() {
        glLinkProgram(_id);
        _checkLinkErrors();
        _linked = True;
    }
    const Program& uniform(KStringRef name, Int value) const {
        UInt loc = glGetUniformLocation(_id, name.c_str());
        glUniform1i(loc, value);
        return *this;
    }
    const Program& uniform(KStringRef name, const Mat4& value) const {
        UInt loc = glGetUniformLocation(_id, name.c_str());
        glUniformMatrix4fv(loc, 1, False, glm::value_ptr(value));
        return *this;
    }
    const Program& use() const {
        glUseProgram(_id);
        return *this;
    }
private:
    void _checkLinkErrors() const {
        Int success;
        Char infoLog[1024];
        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(_id, 1024, nullptr, infoLog);
            throw GLException("Program::link", infoLog);
        }
    }
};

NS_SKY_GL_END
