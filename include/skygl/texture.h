#pragma once

#include <skygl/common.h>
#include <skygl/types.h>
#include <skygl/gl.h>

#include <SOIL/SOIL.h>

NS_SKY_GL_BEG

class Image {
private:
    Int _width, _height;
    UBytePtr _data;
public:
    static Image fromFile(KStringRef path) {
        Image img;
        img._data = SOIL_load_image(path.c_str(), &img._width, &img._height, 0, SOIL_LOAD_RGB);
        return img;
    }
    ~Image() {
        SOIL_free_image_data(_data);
    }
    void use(Enum textureType) const {
        glTexImage2D(textureType, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
    }
private:
    Image() = default;
};

template <Enum TextureType = GL_TEXTURE_2D>
class Texture {
private:
    UInt _id;
    UInt _active;
public:
    Texture(UInt active = 0): _active(active) {
        glGenTextures(1, &_id);
    }
    ~Texture() {
        glDeleteTextures(1, &_id);
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
        img.use(TextureType);
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
