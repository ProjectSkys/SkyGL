#pragma once

#include "skygl/basic/common.h"
#include "skygl/basic/types.h"
#include "skygl/basic/error.h"
#include "skygl/basic/utils.h"
#include "skygl/calc/math.h"
#include "skygl/gl/gl.h"

#include <string>
#include <iostream>

#include <boost/noncopyable.hpp>

NS_SKY_GL_BEG

class Program;

template <Enum ShaderType>
class Shader: private boost::noncopyable {
private:
    UInt _id;
    Bool _compiled;
public:
    Shader(): _compiled(False) {
        _id = glCreateShader(ShaderType);
    }
    Shader(KStringRef path): Shader() {
        source(readFileFromPath(path));
        compile();
    }
    ~Shader() {
        if (_id) glDeleteShader(_id);
    }
    Shader(Shader&& shader) {
        _id = shader._id;
        _compiled = shader._compiled;
        shader._id = 0;
    }
    Shader& operator = (Shader&& shader) {
        if (this == &shader) return *this;
        _id = shader._id;
        _compiled = shader._compiled;
        shader._id = 0;
        return *this;
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

class Program: private boost::noncopyable {
private:
    UInt _id;
    Bool _linked;
public:
    Program(): _linked(False) {
        _id = glCreateProgram();
    }
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
    ~Program() {
        if (_id) glDeleteProgram(_id);
    }
    Program(Program&& prog) {
        _id = prog._id;
        _linked = prog._linked;
        prog._id = 0;
    }
    Program& operator = (Program&& prog) {
        if (this == &prog) return *this;
        _id = prog._id;
        _linked = prog._linked;
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
        glAttachShader(_id, shader.getId());
        return *this;
    }
    template <Enum T>
    Program& detach(const Shader<T>& shader) {
        glDetachShader(_id, shader.getId());
        return *this;
    }
    void link() {
        glLinkProgram(_id);
        _checkLinkErrors();
        _linked = True;
    }
    UInt getUniformLocation(KStringRef name) const {
        return glGetUniformLocation(_id, name.c_str());
    }
    const Program& uniform(KStringRef name, Int value) const {
        UInt loc = getUniformLocation(name);
        glUniform1i(loc, value);
        return *this;
    }
    const Program& uniform(KStringRef name, UInt value) const {
        UInt loc = getUniformLocation(name);
        glUniform1ui(loc, value);
        return *this;
    }
    const Program& uniform(KStringRef name, SizeT value) const {
        UInt loc = getUniformLocation(name);
        glUniform1i(loc, value);
        return *this;
    }
    const Program& uniform(KStringRef name, Float value) const {
        UInt loc = getUniformLocation(name);
        glUniform1f(loc, value);
        return *this;
    }
    const Program& uniform(KStringRef name, KVec3Ref value) const {
        UInt loc = getUniformLocation(name);
        glUniform3f(loc, value.x, value.y, value.z);
        return *this;
    }
    const Program& uniform(KStringRef name, KMat3Ref value) const {
        UInt loc = getUniformLocation(name);
        glUniformMatrix3fv(loc, 1, False, glm::value_ptr(value));
        return *this;
    }
    const Program& uniform(KStringRef name, KMat4Ref value) const {
        UInt loc = getUniformLocation(name);
        glUniformMatrix4fv(loc, 1, False, glm::value_ptr(value));
        return *this;
    }
    template <typename T>
    const Program& uniform(KStringRef name, T* objs, UInt size) const {
        for (UInt i = 0; i < size; ++i) {
            uniform(name + "[" + std::to_string(i) + "]", objs[i]);
        }
        return *this;
    }
    template <typename T, size_t N>
    const Program& uniform(KStringRef name, T objs[N]) const {
        return uniform(name, objs, N);
    }
    template <typename T>
    const Program& uniform(KStringRef name, const std::vector<T>& objs) const {
        return uniform(name, &objs[0], objs.size());
    }
    UInt getBlockIndex(KStringRef name) const {
        return glGetUniformBlockIndex(_id, name.c_str());
    }
    const Program& binding(KStringRef name, UInt point) const {
        UInt index = getBlockIndex(name);
        glUniformBlockBinding(_id, index, point);
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

using KProgramRef = const Program&;

NS_SKY_GL_END
