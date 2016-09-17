#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/gl/gl.h>
#include <skygl/gl/texture.h>

#include <boost/noncopyable.hpp>

NS_SKY_GL_BEG

template <Enum BufferType>
class BaseBuffer: private boost::noncopyable {
protected:
    UInt _id;
public:
    BaseBuffer() {
        glGenBuffers(1, &_id);
    }
    ~BaseBuffer() {
        if (_id) glDeleteBuffers(1, &_id);
    }
    BaseBuffer(BaseBuffer&& buf) {
        _id = buf._id;
        buf._id = 0;
    }
    BaseBuffer& operator = (BaseBuffer&& buf) {
        if (this == &buf) return *this;
        _id = buf._id;
        buf._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    const BaseBuffer& bind() const {
        glBindBuffer(BufferType, _id);
        return *this;
    }
    const BaseBuffer& unbind() const {
        glBindBuffer(BufferType, 0);
        return *this;
    }
    const BaseBuffer& data(KVoidPtr dat, Sizeptr size, Enum usage = GL_STATIC_DRAW) const {
        glBufferData(BufferType, size, dat, usage);
        return *this;
    }
    template <typename T, SizeT N>
    const BaseBuffer& data(T (&dat)[N], Enum usage = GL_STATIC_DRAW) const {
        return data(static_cast<KVoidPtr>(&dat[0]), N * sizeof(T), usage);
    }
    template <typename T>
    const BaseBuffer& data(const std::vector<T>& dat, Enum usage = GL_STATIC_DRAW) const {
        return data(static_cast<KVoidPtr>(&dat[0]), dat.size() * sizeof(T), usage);
    }
    const BaseBuffer& sub(KVoidPtr dat, Sizeptr size, Intptr offset = 0) const {
        glBufferSubData(BufferType, offset, size, dat);
        return *this;
    }
    template <typename T>
    const BaseBuffer& sub(const std::vector<T>& v, Intptr offset = 0) const {
        sub(BufferType, static_cast<KVoidPtr>(&v[0]), v.size() * sizeof(T), offset);
        return *this;
    }
    const BaseBuffer& empty(UInt size) const {
        data(nullptr, size);
        return *this;
    }
    const BaseBuffer& binding(UInt point) const {
        glBindBufferBase(BufferType, point, _id);
        return *this;
    }
    const BaseBuffer& binding(UInt point, Sizeptr size, Intptr offset = 0) const {
        glBindBufferRange(BufferType, point, _id, offset, size);
        return *this;
    }
};

using ArrayBuffer = BaseBuffer<GL_ARRAY_BUFFER>;
using ElementBuffer = BaseBuffer<GL_ELEMENT_ARRAY_BUFFER>;
using UniformBuffer = BaseBuffer<GL_UNIFORM_BUFFER>;

class Attrib {
private:
    UInt _idx;
    Int _size = 0;
    Enum _type = TypeToEnum<Float>;
    Bool _normalized = False;
    Size _stride = 0;
    KVoidPtr _pointer = nullptr;
    UInt _divisor = 0;
public:
    explicit Attrib(UInt idx)
        : _idx(idx) {}
    ~Attrib() {
        glEnableVertexAttribArray(_idx);
        glVertexAttribPointer(_idx, _size, _type, _normalized, _stride, _pointer);
        glVertexAttribDivisor(_idx, _divisor);
    }
    template <class T>
    Attrib& has(Int size) {
        _size = size;
        _type = TypeToEnum<T>;
        return *this;
    }
    Attrib& normalized(Bool normalized) {
        _normalized = normalized;
        return *this;
    }
    Attrib& stride(Size stride) {
        _stride = stride;
        return *this;
    }
    Attrib& offset(Sizeptr offset) {
        _pointer = reinterpret_cast<VoidPtr>(offset);
        return *this;
    }
    Attrib& pointer(KVoidPtr pointer) {
        _pointer = pointer;
        return *this;
    }
    Attrib& divisor(UInt div) {
        _divisor = div;
        return *this;
    }
};

class VertexArray: private boost::noncopyable {
private:
    UInt _id;
public:
    VertexArray() {
        glGenVertexArrays(1, &_id);
    }
    ~VertexArray() {
        if (_id) glDeleteVertexArrays(1, &_id);
    }
    VertexArray(VertexArray&& va) {
        _id = va._id;
        va._id = 0;
    }
    VertexArray& operator = (VertexArray&& va) {
        if (this == &va) return *this;
        _id = va._id;
        va._id = 0;
        return *this;
    }
    const VertexArray& bind() const {
        glBindVertexArray(_id);
        return *this;
    }
    const VertexArray& unbind() const {
        glBindVertexArray(0);
        return *this;
    }
    template <Enum Type>
    const BaseBuffer<Type>& buffer(const BaseBuffer<Type>& buf) const {
        buf.bind();
        return buf;
    }
    Attrib attrib(UInt idx) const {
        return Attrib(idx);
    }
};

template <Enum BufferType>
class BaseRenderBuffer: private boost::noncopyable {
protected:
    UInt _id;
public:
    BaseRenderBuffer() {
        glGenRenderbuffers(1, &_id);
    }
    ~BaseRenderBuffer() {
        if (_id) glDeleteRenderbuffers(1, &_id);
    }
    BaseRenderBuffer(BaseRenderBuffer&& buf) {
        _id = buf._id;
        buf._id = 0;
    }
    BaseRenderBuffer& operator = (BaseRenderBuffer&& buf) {
        if (this == &buf) return *this;
        _id = buf._id;
        buf._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    const BaseRenderBuffer& bind() const {
        glBindRenderbuffer(BufferType, _id);
        return *this;
    }
    const BaseRenderBuffer& unbind() const {
        glBindRenderbuffer(BufferType, 0);
        return *this;
    }
    const BaseRenderBuffer& storage(UInt width, UInt height, Enum format) const {
        glRenderbufferStorage(BufferType, format, width, height);
        return *this;
    }
    const BaseRenderBuffer& storage(UInt width, UInt height, Enum format, UInt samples) const {
        glRenderbufferStorageMultisample(BufferType, samples, format, width, height);
        return *this;
    }
};

using RenderBuffer = BaseRenderBuffer<GL_RENDERBUFFER>;

template <Enum BufferType>
class BaseFrameBuffer: private boost::noncopyable {
protected:
    UInt _id;
public:
    BaseFrameBuffer() {
        glGenFramebuffers(1, &_id);
    }
    ~BaseFrameBuffer() {
        if (_id) glDeleteFramebuffers(1, &_id);
    }
    BaseFrameBuffer(BaseFrameBuffer&& buf) {
        _id = buf._id;
        buf._id = 0;
    }
    BaseFrameBuffer& operator = (BaseFrameBuffer&& buf) {
        if (this == &buf) return *this;
        _id = buf._id;
        buf._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    const BaseFrameBuffer& bind() const {
        glBindFramebuffer(BufferType, _id);
        return *this;
    }
    const BaseFrameBuffer& unbind() const {
        glBindFramebuffer(BufferType, 0);
        return *this;
    }
    template <Enum Type>
    const BaseFrameBuffer& attach(const Texture<Type>& t, Enum point) const {
        glFramebufferTexture(BufferType, point, t.getId(), 0);
        return *this;
    }
    template <Enum Type>
    const BaseFrameBuffer& attach(const BaseRenderBuffer<Type>& buf, Enum point) const {
        glFramebufferRenderbuffer(BufferType, point, Type, buf.getId());
        return *this;
    }
    Enum status() const {
        return glCheckFramebufferStatus(BufferType);
    }
};

using FrameBuffer = BaseFrameBuffer<GL_FRAMEBUFFER>;

NS_SKY_GL_END
