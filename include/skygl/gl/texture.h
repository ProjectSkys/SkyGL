#pragma once

#include <skygl/basic/common.h>
#include <skygl/basic/types.h>
#include <skygl/basic/error.h>
#include <skygl/gl/gl.h>

#include <boost/noncopyable.hpp>

#include <SOIL/SOIL.h>

NS_SKY_GL_BEG

class Image: boost::noncopyable {
private:
    UBytePtr _data;
    Int _width, _height;
public:
    Image(KStringRef path) {
        _data = SOIL_load_image(path.c_str(), &_width, &_height, 0, SOIL_LOAD_RGB);
        if (_data == nullptr) {
            throw GLException("Image::Image(path)", "Can not load " + path);
        }
    }
    ~Image() {
        if (_data) SOIL_free_image_data(_data);
    }
    Image(Image&& img) {
        _data = img._data;
        _width = img._width;
        _height = img._height;
        img._data = 0;
    }
    Image& operator = (Image&& img) {
        if (this == &img) return *this;
        _data = img._data;
        _width = img._width;
        _height = img._height;
        img._data = 0;
        return *this;
    }
    void toTexture(Enum textureType) const {
        glTexImage2D(textureType, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
    }
};

template <Enum TextureType = GL_TEXTURE_2D>
class Texture: public boost::noncopyable {
private:
    UInt _id;
    UInt _active;
public:
    Texture(UInt active = 0): _active(active) {
        glGenTextures(1, &_id);
    }
    ~Texture() {
        if (_id) glDeleteTextures(1, &_id);
    }
    Texture(Texture&& tex) {
        _id = tex._id;
        _active = tex._active;
        tex._id = 0;
    }
    Texture& operator = (Texture&& tex) {
        if (this == &tex) return *this;
        _id = tex._id;
        _active = tex._active;
        tex._id = 0;
        return *this;
    }
    UInt getId() const {
        return _id;
    }
    Texture& attach(UInt active) {
        _active = active + 1;
        return *this;
    }
    const Texture& bind() const {
        if (_active != 0) {
            glActiveTexture(GL_TEXTURE0 + _active - 1);
        }
        glBindTexture(TextureType, _id);
        return *this;
    }
    const Texture& unbind() const {
        if (_active != 0) {
            glActiveTexture(GL_TEXTURE0 + _active - 1);
        }
        glBindTexture(TextureType, 0);
        return *this;
    }
    const Texture& param(Enum key, Int value) const {
        glTexParameteri(TextureType, key, value);
        return *this;
    }
    const Texture& load(const Image& img) const {
        img.toTexture(TextureType);
        return *this;
    }
    const Texture& genMipmap() const {
        glGenerateMipmap(TextureType);
        return *this;
    }
};

using Texture2D = Texture<GL_TEXTURE_2D>;
using Texture3D = Texture<GL_TEXTURE_3D>;

NS_SKY_GL_END
