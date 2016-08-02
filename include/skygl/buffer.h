#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/gl.h>

NS_SKY_GL_BEG

class Buffer {
protected:
    UInt _id;
public:
    Buffer() {
        glGenBuffers(1, &_id);
    }
    ~Buffer() {
        glDeleteBuffers(1, &_id);
    }
    UInt getID() const {
        return _id;
    }
};

class ArrayBuffer: public Buffer {
public:
    ArrayBuffer() {}
    const ArrayBuffer& data(VoidPtr dat, UInt size) const {
        glBufferData(GL_ARRAY_BUFFER, size, dat, GL_STATIC_DRAW);
        return *this;
    }
};

class ElementArrayBuffer: public Buffer {
public:
    ElementArrayBuffer() {}
    const ElementArrayBuffer& data(VoidPtr dat, UInt size) const {
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
        _pointer = (Void*)offset;
        return *this;
    }
    Attrib& pointer(Void* pointer) {
        _pointer = pointer;
        return *this;
    }
};

class VertexArray {
private:
    UInt _id;
public:
    VertexArray() {
        glGenVertexArrays(1, &_id);
    }
    ~VertexArray() {
        glDeleteVertexArrays(1, &_id);
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
        glBindBuffer(GL_ARRAY_BUFFER, abuf.getID());
        return abuf;
    }
    const ElementArrayBuffer& buffer(const ElementArrayBuffer& ebuf) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuf.getID());
        return ebuf;
    }
    Attrib attrib(UInt idx) const {
        return Attrib(idx);
    }
};

NS_SKY_GL_END
