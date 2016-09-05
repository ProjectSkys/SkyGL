#pragma once

#include "skygl/basic/common.h"
#include "skygl/basic/types.h"
#include "skygl/basic/error.h"
#include "skygl/gl/gl.h"
#include "skygl/load/image.h"

#include <memory>

#include <boost/noncopyable.hpp>

NS_SKY_GL_BEG

template <Enum TextureType = GL_TEXTURE_2D>
class Texture: private boost::noncopyable {
public:
    using Ptr = std::shared_ptr<Texture<TextureType>>;
private:
    UInt _id;
    UInt _active;
public:
    Texture(UInt active = 0): _id(0), _active(active) {
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
    UInt getActive(UInt active) const {
        return _active;
    }
    void setActive(UInt active) {
        _active = active;
    }
    const Texture& bind() const {
        glActiveTexture(GL_TEXTURE0 + _active);
        glBindTexture(TextureType, _id);
        return *this;
    }
    const Texture& unbind() const {
        glActiveTexture(GL_TEXTURE0 + _active);
        glBindTexture(TextureType, 0);
        return *this;
    }
    Texture& active(UInt active) {
        setActive(active);
        bind();
        return *this;
    }
    const Texture& param(Enum key, Int value) const {
        glTexParameteri(TextureType, key, value);
        return *this;
    }
    const Texture& load(const Image& img, Enum target = TextureType) const {
        glTexImage2D(target, 0, img.colorType, img.width, img.height, 0, img.colorType, GL_UNSIGNED_BYTE, img.data);
        return *this;
    }
    const Texture& empty(Int width, Int height, Enum format, Enum target = TextureType) const {
        glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
        return *this;
    }
    const Texture& genMipmap() const {
        glGenerateMipmap(TextureType);
        return *this;
    }
};

#define USING_TEXTURE(postfix, type) \
    using Texture##postfix = Texture<GL_TEXTURE_##type>; \
    using Texture##postfix##Ptr = Texture##postfix::Ptr;
USING_TEXTURE(2D, 2D)
USING_TEXTURE(3D, 3D)
USING_TEXTURE(CubeMap, CUBE_MAP)
#undef USING_TEXTURE

NS_SKY_GL_END
