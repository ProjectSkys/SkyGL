#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/gl/gl.h>

#include <boost/noncopyable.hpp>

NS_SKY_GL_BEG

class Buffer: private boost::noncopyable {
protected:
    UInt _id;
public:
    Buffer() {
        glGenBuffers(1, &_id);
    }
    ~Buffer() {
        if (_id) glDeleteBuffers(1, &_id);
    }
    Buffer(Buffer&& buf) {
        _id = buf._id;
        buf._id = 0;
    }
    Buffer& operator = (Buffer&& buf) {
        if (this == &buf) return *this;
        _id = buf._id;
        buf._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
};

class ArrayBuffer: public Buffer {
public:
    const ArrayBuffer& data(VoidPtr dat, UInt size) const {
        glBufferData(GL_ARRAY_BUFFER, size, dat, GL_STATIC_DRAW);
        return *this;
    }
};

class ElementBuffer: public Buffer {
public:
    const ElementBuffer& data(VoidPtr dat, UInt size) const {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, dat, GL_STATIC_DRAW);
        return *this;
    }
};

class Attrib {
private:
    UInt _idx;
    Int _size;
    Enum _type;
    Bool _normalized;
    Size _stride;
    VoidPtr _pointer;
public:
    Attrib(UInt idx): _idx(idx), _normalized(False) {}
    ~Attrib() {
        glVertexAttribPointer(_idx, _size, _type, _normalized, _stride, _pointer);
        glEnableVertexAttribArray(_idx);
    }
    template <class T>
    Attrib& has(UInt size) {
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
    Attrib& offset(SizeT offset) {
        _pointer = reinterpret_cast<VoidPtr>(offset);
        return *this;
    }
    Attrib& pointer(VoidPtr pointer) {
        _pointer = pointer;
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
    const ArrayBuffer& buffer(const ArrayBuffer& abuf) const {
        glBindBuffer(GL_ARRAY_BUFFER, abuf.getId());
        return abuf;
    }
    const ElementBuffer& buffer(const ElementBuffer& ebuf) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuf.getId());
        return ebuf;
    }
    Attrib attrib(UInt idx) const {
        return Attrib(idx);
    }
};

NS_SKY_GL_END
